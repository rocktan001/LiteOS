/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2021. All rights reserved.
 * Description: Virtual Fs Implementation
 * Author: Huawei LiteOS Team
 * Create: 2013-01-01
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --------------------------------------------------------------------------- */

#include "fs/los_vfs.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "errno.h"
#include "fcntl.h"
#include "los_mux.h"
#include "limits.h"

#define LOS_FCNTL (O_NONBLOCK | O_NDELAY | O_APPEND | O_SYNC | FASYNC)

struct file g_files[LOS_MAX_FILES];
uint32_t g_fsMutex;
struct mount_point *g_mountPoints = NULL;
struct file_system *g_fileSystems = NULL;

static int file_2_fd(struct file *file)
{
    if (file == NULL) {
        return -1;
    }
    return file - g_files;
}

static struct file *fd_2_file(int fd)
{
    return &g_files[fd];
}

static struct file *los_file_get(void)
{
    int i;
    /* protected by g_fsMutex */
    for (i = 0; i < LOS_MAX_FILES; i++) {
        if (g_files[i].f_status == FILE_STATUS_NOT_USED) {
            g_files[i].f_status = FILE_STATUS_INITING;
            return &g_files[i];
        }
    }

    return NULL;
}

static struct file *los_file_get_new(int fd)
{
    if ((fd < 0) || (fd >= LOS_MAX_FILES)) {
        return NULL;
    }
    if (g_files[fd].f_status == FILE_STATUS_NOT_USED) {
        g_files[fd].f_status = FILE_STATUS_INITING;
        return &g_files[fd];
    }

    return NULL;
}

static void los_file_put(struct file *file)
{
    if (file == NULL) {
        return;
    }
    file->f_flags = 0;
    file->f_fops = NULL;
    file->f_data = NULL;
    file->f_mp = NULL;
    file->f_offset = 0;
    file->f_owner = (uint32_t)-1;
    file->f_status = FILE_STATUS_NOT_USED;
}

static struct mount_point *los_mp_find(const char *path, const char **path_in_mp)
{
    struct mount_point *mp = g_mountPoints;
    struct mount_point *best_mp = NULL;
    int best_matches = 0;
    if (path == NULL) {
        return NULL;
    }
    if (path_in_mp != NULL) {
        *path_in_mp = NULL;
    }
    while ((mp != NULL) && (mp->m_path != NULL)) {
        const char *m_path = mp->m_path;
        const char *i_path = path;
        const char *t = NULL;
        int matches = 0;
        do {
            while (*m_path == '/') {
                m_path++;
            }
            while (*i_path == '/') {
                i_path++;
            }

            t = strchr(m_path, '/');
            if (t == NULL) {
                t = strchr(m_path, '\0');
            }
            if ((t == m_path) || (t == NULL)) {
                break;
            }
            if (strncmp(m_path, i_path, (size_t)(t - m_path)) != 0) {
                goto next; /* this mount point do not match, check next */
            }

            i_path += (t - m_path);
            if ((*i_path != '\0') && (*i_path != '/')) {
                goto next;
            }

            matches += (t - m_path);
            m_path += (t - m_path);
        } while (*m_path != '\0');

        if (matches > best_matches) {
            best_matches = matches;
            best_mp = mp;

            while (*i_path == '/') {
                i_path++;
            }

            if (path_in_mp != NULL) {
                *path_in_mp = i_path;
            }
        }
    next:
        mp = mp->m_next;
    }
    return best_mp;
}

static int los_open(const char *path, int flags)
{
    struct file *file = NULL;
    int fd = -1;
    const char *path_in_mp = NULL;
    struct mount_point *mp = NULL;

    if ((path == NULL) || (path[strlen(path) - 1] == '/')) {
        return fd;
    }
    /* prevent fs/mp being removed while opening */
    if (LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER) != LOS_OK) {
        return fd;
    }

    file = los_file_get();
    mp = los_mp_find(path, &path_in_mp);

    (void)LOS_MuxPost(g_fsMutex);

    if ((file == NULL) || (mp == NULL) || (path_in_mp == NULL) || (*path_in_mp == '\0') ||
        (mp->m_fs->fs_fops == NULL) || (mp->m_fs->fs_fops->open == NULL)) {
        return fd;
    }

    if ((LOS_MuxPend(mp->m_mutex, LOS_WAIT_FOREVER) != LOS_OK)) {
        los_file_put(file);
        return fd;
    }

    file->f_flags = (uint32_t)flags;
    file->f_offset = 0;
    file->f_data = NULL;
    file->f_fops = mp->m_fs->fs_fops;
    file->f_mp = mp;
    file->f_owner = LOS_CurTaskIDGet();
    if (file->f_fops->open(file, path_in_mp, flags) == 0) {
        mp->m_refs++;
        fd = file_2_fd(file);
        file->f_status = FILE_STATUS_READY; /* file now ready to use */
    } else {
        los_file_put(file);
    }
    (void)LOS_MuxPost(mp->m_mutex);

    return fd;
}

/* attach to a file and then set new status */

static struct file *_los_attach_file(int fd, uint32_t status)
{
    struct file *file = NULL;

    if ((fd < 0) || (fd >= LOS_MAX_FILES)) {
        VFS_ERRNO_SET(EBADF);
        return file;
    }

    file = fd_2_file(fd);

    /*
     * Prevent file closed after the checking of:
     *
     * if (file->f_status == FILE_STATUS_READY)
     *
     * Because our g_files are not privated to one task, it may be operated
     * by every task.
     * So we should take the mutex of current mount point before operating it,
     * but for now we don't know if this file is valid (FILE_STATUS_READY), if
     * this file is not valid, the f_mp may be incorrect. so
     * we must check the status first, but this file may be closed/removed
     * after the checking if the senquence is not correct.
     *
     * Consider the following code:
     *
     * los_attach_file (...)
     * {
     * if (file->f_status == FILE_STATUS_READY)
     * {
     * while (LOS_MuxPend (file->f_mp->m_mutex, LOS_WAIT_FOREVER) != LOS_OK);
     *
     * return file;
     * }
     * }
     *
     * It is not safe:
     *
     * If current task is interrupted by an IRQ just after the checking and then
     * a new task is swapped in and the new task just closed this file.
     *
     * So <g_fsMutex> is acquire first and then check if it is valid: if not, just
     * return NULL (which means fail); If yes, the mutex for current mount point
     * is qcquired. And the close operation will also set task to
     * FILE_STATUS_CLOSING to prevent other tasks operate on this file (and also
     * prevent other tasks pend on the mutex of this mount point for this file).
     * At last <g_fsMutex> is released. And return the file handle (struct file *).
     *
     * As this logic used in almost all the operation routines, this routine is
     * made to reduce the redundant code.
     */

    while (LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER) != LOS_OK) {
    };

    if (file->f_status == FILE_STATUS_READY) {
        while (LOS_MuxPend(file->f_mp->m_mutex, LOS_WAIT_FOREVER) != LOS_OK) {
        };
        if (status != FILE_STATUS_READY) {
            file->f_status = status;
        }
    } else {
        VFS_ERRNO_SET(EBADF);
        file = NULL;
    }

    (void)LOS_MuxPost(g_fsMutex);

    return file;
}

static struct file *los_attach_file(int fd)
{
    return _los_attach_file(fd, FILE_STATUS_READY);
}

static struct file *los_attach_file_with_status(int fd, int status)
{
    return _los_attach_file(fd, (uint32_t)status);
}

static uint32_t los_detach_file(struct file *file)
{
    if ((file == NULL) || (file->f_mp == NULL)) {
        return (uint32_t)VFS_ERROR;
    }
    return LOS_MuxPost(file->f_mp->m_mutex);
}

static int los_close(int fd)
{
    struct file *file;
    int ret = -1;

    file = los_attach_file_with_status(fd, FILE_STATUS_CLOSING);
    if (file == NULL) {
        return ret;
    }

    if (file->f_fops->close != NULL) {
        ret = file->f_fops->close(file);
    } else {
        VFS_ERRNO_SET(ENOTSUP);
    }

    if (ret == 0) {
        file->f_mp->m_refs--;
    }

    (void)los_detach_file(file);

    los_file_put(file);

    return ret;
}

static ssize_t los_read(int fd, char *buff, size_t bytes)
{
    struct file *file = NULL;
    ssize_t ret = (ssize_t)-1;

    if ((buff == NULL) || (bytes == 0)) {
        VFS_ERRNO_SET(EINVAL);
        return ret;
    }

    file = los_attach_file(fd);
    if (file == NULL) {
        return ret;
    }

    if ((file->f_flags & O_ACCMODE) == O_WRONLY) {
        VFS_ERRNO_SET(EACCES);
    } else if (file->f_fops->read != NULL) {
        ret = file->f_fops->read(file, buff, bytes);
    } else {
        VFS_ERRNO_SET(ENOTSUP);
    }

    /* else ret will be -1 */

    (void)los_detach_file(file);

    return ret;
}

static ssize_t los_write(int fd, const void *buff, size_t bytes)
{
    struct file *file = NULL;
    ssize_t ret = -1;

    if ((buff == NULL) || (bytes == 0)) {
        VFS_ERRNO_SET(EINVAL);
        return ret;
    }

    file = los_attach_file(fd);
    if (file == NULL) {
        return ret;
    }

    if ((file->f_flags & O_ACCMODE) == O_RDONLY) {
        VFS_ERRNO_SET(EACCES);
    } else if (file->f_fops->write != NULL) {
        ret = file->f_fops->write(file, buff, bytes);
    } else {
        VFS_ERRNO_SET(ENOTSUP);
    }

    /* else ret will be -1 */
    (void)los_detach_file(file);

    return ret;
}

static off_t los_lseek(int fd, off_t off, int whence)
{
    struct file *file;
    off_t ret = -1;

    file = los_attach_file(fd);
    if (file == NULL) {
        return ret;
    }

    if (file->f_fops->lseek == NULL) {
        ret = file->f_offset;
    } else {
        ret = file->f_fops->lseek(file, off, whence);
    }

    (void)los_detach_file(file);

    return ret;
}

static off64_t los_lseek64(int fd, off64_t off, int whence)
{
    struct file *file;
    off64_t ret = -1;

    file = los_attach_file(fd);
    if ((file == NULL) || (file->f_fops == NULL)) {
        return ret;
    }
    if (file->f_fops->lseek64 == NULL) {
        ret = file->f_offset64;
    } else {
        ret = file->f_fops->lseek64(file, off, whence);
    }

    (void)los_detach_file(file);

    return ret;
}

static int los_stat(const char *path, struct stat *stat)
{
    struct mount_point *mp = NULL;
    const char *path_in_mp = NULL;
    int ret = -1;

    if ((path == NULL) || (stat == NULL)) {
        VFS_ERRNO_SET(EINVAL);
        return ret;
    }

    if (LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER) != LOS_OK) {
        VFS_ERRNO_SET(EAGAIN);
        return ret;
    }

    mp = los_mp_find(path, &path_in_mp);
    if ((mp == NULL) || (path_in_mp == NULL) || (*path_in_mp == '\0')) {
        VFS_ERRNO_SET(ENOENT);
        (void)LOS_MuxPost(g_fsMutex);
        return ret;
    }

    if (mp->m_fs->fs_fops->stat != NULL) {
        ret = mp->m_fs->fs_fops->stat(mp, path_in_mp, stat);
    } else {
        VFS_ERRNO_SET(ENOTSUP);
    }

    (void)LOS_MuxPost(g_fsMutex);

    return ret;
}

static int los_unlink(const char *path)
{
    struct mount_point *mp = NULL;
    const char *path_in_mp = NULL;
    int ret = -1;

    if (path == NULL) {
        VFS_ERRNO_SET(EINVAL);
        return ret;
    }

    (void)LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER); /* prevent the file open/rename */

    mp = los_mp_find(path, &path_in_mp);
    if ((mp == NULL) || (path_in_mp == NULL) || (*path_in_mp == '\0') || (mp->m_fs->fs_fops->unlink == NULL)) {
        VFS_ERRNO_SET(ENOENT);
        (void)LOS_MuxPost(g_fsMutex);
        return ret;
    }

    ret = mp->m_fs->fs_fops->unlink(mp, path_in_mp);

    (void)LOS_MuxPost(g_fsMutex);
    return ret;
}

static int los_rename(const char *old, const char *new)
{
    struct mount_point *mp_old = NULL;
    struct mount_point *mp_new = NULL;
    const char *path_in_mp_old = NULL;
    const char *path_in_mp_new = NULL;
    int ret = -1;

    if ((old == NULL) || (new == NULL)) {
        VFS_ERRNO_SET(EINVAL);
        return ret;
    }

    (void)LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER); /* prevent file open/unlink */

    mp_old = los_mp_find(old, &path_in_mp_old);

    if (path_in_mp_old == NULL) {
        VFS_ERRNO_SET(EINVAL);
        (void)LOS_MuxPost(g_fsMutex);
        return ret;
    }

    if ((mp_old == NULL) || (*path_in_mp_old == '\0') || (mp_old->m_fs->fs_fops->unlink == NULL)) {
        VFS_ERRNO_SET(EINVAL);
        (void)LOS_MuxPost(g_fsMutex);
        return ret;
    }

    mp_new = los_mp_find(new, &path_in_mp_new);
    if ((mp_new == NULL) || (path_in_mp_new == NULL) || (*path_in_mp_new == '\0') ||
        (mp_new->m_fs->fs_fops->unlink == NULL)) {
        VFS_ERRNO_SET(EINVAL);
        (void)LOS_MuxPost(g_fsMutex);
        return ret;
    }

    if (mp_old != mp_new) {
        VFS_ERRNO_SET(EXDEV);
        (void)LOS_MuxPost(g_fsMutex);
        return ret;
    }

    if (mp_old->m_fs->fs_fops->rename != NULL) {
        ret = mp_old->m_fs->fs_fops->rename(mp_old, path_in_mp_old, path_in_mp_new);
    } else {
        VFS_ERRNO_SET(ENOTSUP);
    }

    (void)LOS_MuxPost(g_fsMutex);
    return ret;
}

static int los_ioctl(int fd, int func, ...)
{
    va_list ap;
    unsigned long arg;
    struct file *file = NULL;
    int ret = -1;

    va_start(ap, func);
    arg = va_arg(ap, unsigned long);
    va_end(ap);

    file = los_attach_file(fd);
    if (file == NULL) {
        return ret;
    }

    if (file->f_fops->ioctl != NULL) {
        ret = file->f_fops->ioctl(file, func, arg);
    } else {
        VFS_ERRNO_SET(ENOTSUP);
    }

    (void)los_detach_file(file);

    return ret;
}

static int los_sync(int fd)
{
    struct file *file;
    int ret = -1;

    file = los_attach_file(fd);
    if (file == NULL) {
        return ret;
    }

    if (file->f_fops->sync != NULL) {
        ret = file->f_fops->sync(file);
    } else {
        VFS_ERRNO_SET(ENOTSUP);
    }

    (void)los_detach_file(file);

    return ret;
}

static struct dir *los_opendir(const char *path)
{
    struct mount_point *mp = NULL;
    const char *path_in_mp = NULL;
    struct dir *dir = NULL;
    uint32_t ret;

    if (path == NULL) {
        VFS_ERRNO_SET(EINVAL);
        return NULL;
    }

    dir = (struct dir *)malloc(sizeof(struct dir));
    if (dir == NULL) {
        PRINT_ERR("fail to malloc memory in VFS, <malloc.c> is needed,"
            "make sure it is added\n");
        VFS_ERRNO_SET(ENOMEM);
        return NULL;
    }

    if (LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER) != LOS_OK) {
        VFS_ERRNO_SET(EAGAIN);
        free(dir);
        return NULL;
    }

    mp = los_mp_find(path, &path_in_mp);
    if ((mp == NULL) || (path_in_mp == NULL)) {
        VFS_ERRNO_SET(ENOENT);
        (void)LOS_MuxPost(g_fsMutex);
        free(dir);
        return NULL;
    }

    ret = LOS_MuxPend(mp->m_mutex, LOS_WAIT_FOREVER);

    (void)LOS_MuxPost(g_fsMutex);

    if ((ret != LOS_OK) || (mp->m_fs->fs_fops->opendir == NULL)) {
        VFS_ERRNO_SET(ENOTSUP);
        (void)LOS_MuxPost(mp->m_mutex);
        free(dir);
        return NULL;
    }

    dir->d_mp = mp;
    dir->d_offset = 0;

    ret = (uint32_t)mp->m_fs->fs_fops->opendir(dir, path_in_mp);
    if (ret == 0) {
        mp->m_refs++;
    } else {
        free(dir);
        dir = NULL;
    }

    (void)LOS_MuxPost(mp->m_mutex);

    return dir;
}

static struct dirent *los_readdir(struct dir *dir)
{
    struct mount_point *mp = NULL;
    struct dirent *ret = NULL;

    if (dir == NULL) {
        VFS_ERRNO_SET(EINVAL);
        return NULL;
    }

    mp = dir->d_mp;

    if (LOS_MuxPend(mp->m_mutex, LOS_WAIT_FOREVER) != LOS_OK) {
        VFS_ERRNO_SET(EAGAIN);
        return NULL;
    }

    if (dir->d_mp->m_fs->fs_fops->readdir != NULL) {
        if (dir->d_mp->m_fs->fs_fops->readdir(dir, &dir->d_dent) == 0) {
            ret = &dir->d_dent;
        } else {
            VFS_ERRNO_SET(EBADF);
        }
    } else {
        VFS_ERRNO_SET(ENOTSUP);
    }

    (void)LOS_MuxPost(mp->m_mutex);

    return ret;
}

static int los_closedir(struct dir *dir)
{
    struct mount_point *mp = NULL;
    int ret = -1;

    if (dir == NULL) {
        VFS_ERRNO_SET(EBADF);
        return ret;
    }

    mp = dir->d_mp;

    if (LOS_MuxPend(mp->m_mutex, LOS_WAIT_FOREVER) != LOS_OK) {
        VFS_ERRNO_SET(EAGAIN);
        return ret;
    }

    if (dir->d_mp->m_fs->fs_fops->closedir != NULL) {
        ret = dir->d_mp->m_fs->fs_fops->closedir(dir);
    } else {
        VFS_ERRNO_SET(ENOTSUP);
    }

    if (ret == 0) {
        free(dir);
        mp->m_refs--;
    } else {
        VFS_ERRNO_SET(EBADF);
    }

    (void)LOS_MuxPost(mp->m_mutex);

    return ret;
}

static int los_mkdir(const char *path, int mode)
{
    struct mount_point *mp = NULL;
    const char *path_in_mp = NULL;
    int ret = -1;

    (void)mode;

    if (path == NULL) {
        VFS_ERRNO_SET(EINVAL);
        return ret;
    }

    if (LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER) != LOS_OK) {
        VFS_ERRNO_SET(EAGAIN);
        return ret;
    }

    mp = los_mp_find(path, &path_in_mp);
    if ((mp == NULL) || (path_in_mp == NULL) || (*path_in_mp == '\0')) {
        VFS_ERRNO_SET(ENOENT);
        (void)LOS_MuxPost(g_fsMutex);
        return ret;
    }

    ret = (int)LOS_MuxPend(mp->m_mutex, LOS_WAIT_FOREVER);

    (void)LOS_MuxPost(g_fsMutex);

    if (ret != LOS_OK) {
        VFS_ERRNO_SET(EAGAIN);
        return -1;
    }

    if (mp->m_fs->fs_fops->mkdir != NULL) {
        ret = mp->m_fs->fs_fops->mkdir(mp, path_in_mp);
    } else {
        VFS_ERRNO_SET(ENOTSUP);
        ret = -1;
    }

    (void)LOS_MuxPost(mp->m_mutex);

    return ret;
}

static int los_dup(int fd)
{
    struct file *file1 = NULL;
    struct file *file2 = NULL;
    const char *mpath = NULL;
    struct mount_point *mp = NULL;

    if ((fd < 0) || (fd > LOS_MAX_FILES)) {
        VFS_ERRNO_SET(EBADF);
        return LOS_NOK;
    }

    file1 = los_attach_file(fd);
    if (file1 == NULL) {
        return LOS_NOK;
    }

    file2 = los_file_get();
    if (file2 == NULL) {
        VFS_ERRNO_SET(ENFILE);
        return LOS_NOK;
    }

    file2->f_flags = file1->f_flags;
    file2->f_status = file1->f_status;
    file2->f_offset = file1->f_offset;
    file2->f_owner = file1->f_owner;
    file2->f_data = file1->f_data;
    file2->f_fops = file1->f_fops;
    file2->f_mp = file1->f_mp;

    if ((file1->f_mp == NULL) || (file1->f_mp->m_path == NULL)) {
        return LOS_NOK;
    }
    mp = los_mp_find(file1->f_mp->m_path, &mpath);
    if ((mp == NULL) || (file1->f_fops == NULL)) {
        return LOS_NOK;
    }
    return file1->f_fops->open(file2, mpath, file1->f_flags);
}

static int los_dup2(int oldFd, int newFd)
{
    struct file *file1 = NULL;
    struct file *file2 = NULL;
    const char *mpath = NULL;
    struct mount_point *mp = NULL;

    file1 = los_attach_file(oldFd);
    if (file1 == NULL) {
        return LOS_NOK;
    }

    file2 = los_attach_file(newFd);
    if (file2 != NULL) {
        (void)los_close(newFd);
        return LOS_NOK;
    }

    file2 = los_file_get_new(newFd);
    if (file2 == NULL) {
        VFS_ERRNO_SET(ENFILE);
        PRINT_ERR("files no free!\n");

        return LOS_NOK;
    }
    if (oldFd == newFd) {
        return oldFd;
    }

    file2->f_flags = file1->f_flags;
    file2->f_status = file1->f_status;
    file2->f_offset = file1->f_offset;
    file2->f_owner = file1->f_owner;
    file2->f_data = file1->f_data;
    file2->f_fops = file1->f_fops;
    file2->f_mp = file1->f_mp;

    if ((file1->f_mp == NULL) || (file1->f_mp->m_path == NULL)) {
        return LOS_NOK;
    }
    mp = los_mp_find(file1->f_mp->m_path, &mpath);
    if ((mp == NULL) || (file1->f_fops == NULL)) {
        return LOS_NOK;
    }
    file1->f_fops->open(file2, mpath, file1->f_flags);
    return newFd;
}

static int los_vfcntl(struct file *filep, int cmd, va_list ap)
{
    int ret;
    int fd;
    uint32_t flags;

    if ((filep == NULL) || (filep->f_fops == NULL)) {
        return -EBADF;
    }

    if (cmd == F_DUPFD) {
        fd = file_2_fd(filep);
        ret = los_dup(fd);
    } else if (cmd == F_GETFL) {
        ret = (int)(filep->f_flags);
    } else if (cmd == F_SETFL) {
        flags = (uint32_t)va_arg(ap, int);
        flags &= LOS_FCNTL;
        filep->f_flags &= ~LOS_FCNTL;
        filep->f_flags |= flags;
        ret = LOS_OK;
    } else {
        ret = -ENOSYS;
    }
    return ret;
}

static int los_fs_name_check(const char *name)
{
    char ch;
    int len = 0;

    do {
        ch = *(name++);

        if (ch == '\0') {
            break;
        }

        if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || ((ch >= '0') && (ch <= '9')) ||
            (ch == '_') || (ch == '-')) {
            len++;
            if (len == LOS_FS_MAX_NAME_LEN) {
                return LOS_NOK;
            }
            continue;
        }
    } while (1);

    return len == 0 ? LOS_NOK : LOS_OK;
}

static struct file_system *los_fs_find(const char *name)
{
    struct file_system *fs;

    for (fs = g_fileSystems; fs != NULL; fs = fs->fs_next) {
        if (strncmp(fs->fs_name, name, LOS_FS_MAX_NAME_LEN) == 0) {
            break;
        }
    }

    return fs;
}

int los_fs_register(struct file_system *fs)
{
    if ((fs == NULL) || (fs->fs_fops == NULL) || (fs->fs_fops->open == NULL)) {
        return LOS_NOK;
    }

    if (los_fs_name_check(fs->fs_name) != LOS_OK) {
        return LOS_NOK;
    }

    if (LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER) != LOS_OK) {
        return LOS_NOK;
    }

    if (los_fs_find(fs->fs_name) != NULL) {
        (void)LOS_MuxPost(g_fsMutex);
        return LOS_NOK;
    }

    fs->fs_next = g_fileSystems;
    g_fileSystems = fs;

    (void)LOS_MuxPost(g_fsMutex);

    return LOS_OK;
}

int los_fs_unregister(struct file_system *fs)
{
    struct file_system *prev = NULL;
    int ret = LOS_OK;

    if (fs == NULL) {
        return LOS_NOK;
    }

    if (LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER) != LOS_OK) {
        return LOS_NOK;
    }

    if (fs->fs_refs > 0) {
        (void)LOS_MuxPost(g_fsMutex);
        return ret;
    }

    if (g_fileSystems == fs) {
        g_fileSystems = fs->fs_next;
        (void)LOS_MuxPost(g_fsMutex);
        return ret;
    }

    prev = g_fileSystems;

    while (prev != NULL) {
        if (prev->fs_next == fs) {
            break;
        }

        prev = prev->fs_next;
    }

    if (prev == NULL) {
        ret = LOS_NOK;
    } else {
        prev->fs_next = fs->fs_next;
    }

    (void)LOS_MuxPost(g_fsMutex);
    return ret;
}

int los_fs_mount(const char *fsname, const char *path, void *data)
{
    struct file_system *fs = NULL;
    struct mount_point *mp = NULL;
    const char *tmp = NULL;
    int ret;
    if ((fsname == NULL) || (path == NULL) || (path[0] != '/')) {
        return LOS_NOK;
    }
    (void)LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER);

    fs = los_fs_find(fsname);
    if (fs == NULL) {
        (void)LOS_MuxPost(g_fsMutex);
        return LOS_NOK;
    }

    mp = los_mp_find(path, &tmp);
    if ((mp != NULL) && (tmp != NULL) && (*tmp == '\0')) {
        (void)LOS_MuxPost(g_fsMutex);
        return LOS_NOK;
    }

    mp = malloc(sizeof(struct mount_point));
    if (mp == NULL) {
        PRINT_ERR("fail to malloc memory in VFS, <malloc.c> is needed,"
            "make sure it is added\n");
        (void)LOS_MuxPost(g_fsMutex);
        return LOS_NOK;
    }

    ret = memset_s(mp, sizeof(struct mount_point), 0, sizeof(struct mount_point));
    if (ret != LOS_OK) {
        free(mp);
        (void)LOS_MuxPost(g_fsMutex);
        return LOS_NOK;
    }

    mp->m_fs = fs;
    mp->m_path = path;
    mp->m_data = data;
    mp->m_refs = 0;

    if (LOS_MuxCreate(&mp->m_mutex) != LOS_OK) {
        free(mp);
        (void)LOS_MuxPost(g_fsMutex);
        return LOS_NOK;
    }

    mp->m_next = g_mountPoints;
    g_mountPoints = mp;

    fs->fs_refs++;
    (void)LOS_MuxPost(g_fsMutex);

    return LOS_OK;
}

int los_fs_unmount(const char *path)
{
    struct mount_point *mp = NULL;
    struct mount_point *prev = NULL;
    const char *tmp = NULL;
    int ret = LOS_NOK;

    if (path == NULL) {
        return ret;
    }

    (void)LOS_MuxPend(g_fsMutex, LOS_WAIT_FOREVER);

    mp = los_mp_find(path, &tmp);
    if ((mp == NULL) || (tmp == NULL) || (*tmp != '\0') || (mp->m_refs != 0)) {
        (void)LOS_MuxPost(g_fsMutex);
        return ret;
    }

    if (g_mountPoints == mp) {
        g_mountPoints = mp->m_next;
    } else {
        for (prev = g_mountPoints; prev != NULL; prev = prev->m_next) {
            if (prev->m_next != mp) {
                continue;
            }

            prev->m_next = mp->m_next;
            break;
        }
    }

    (void)LOS_MuxDelete(mp->m_mutex);
    mp->m_fs->fs_refs--;
    free(mp);
    (void)LOS_MuxPost(g_fsMutex);
    return LOS_OK;
}

int los_vfs_init(void)
{
    if (LOS_MuxCreate(&g_fsMutex) == LOS_OK) {
        return LOS_OK;
    }

    PRINT_ERR("los_vfs_init fail!\n");

    return LOS_NOK;
}


static int MapToPosixRet(int ret)
{
    return ((ret) < 0 ? -1 : (ret));
}

int open(const char *path, int flags, ...)
{
    int ret = los_open(path, flags);
    return MapToPosixRet(ret);
}

int close(int fd)
{
    int ret = los_close(fd);
    return MapToPosixRet(ret);
}

ssize_t read(int fd, void *buff, size_t bytes)
{
    ssize_t ret = los_read(fd, buff, bytes);
    return MapToPosixRet(ret);
}

ssize_t write(int fd, const void *buff, size_t bytes)
{
    ssize_t ret = los_write(fd, buff, bytes);
    return MapToPosixRet(ret);
}

off_t lseek(int fd, off_t off, int whence)
{
    off_t ret = los_lseek(fd, off, whence);
    return ret;
}

off64_t lseek64(int fd, off64_t off, int whence)
{
    off64_t ret = los_lseek64(fd, off, whence);
    return ret;
}

int stat(const char *path, struct stat *stat)
{
    int ret = los_stat(path, stat);
    return MapToPosixRet(ret);
}

int unlink(const char *path)
{
    int ret = los_unlink(path);
    return MapToPosixRet(ret);
}

int rename(const char *oldpath, const char *newpath)
{
    int ret = los_rename(oldpath, newpath);
    return MapToPosixRet(ret);
}

int fsync(int fd)
{
    int ret = los_sync(fd);
    return MapToPosixRet(ret);
}

struct dir *opendir(const char *path)
{
    return los_opendir(path);
}

struct dirent *readdir(struct dir *dir)
{
    return los_readdir(dir);
}

int closedir(struct dir *dir)
{
    int ret = los_closedir(dir);
    return MapToPosixRet(ret);
}

int mkdir(const char *path, mode_t mode)
{
    int ret = los_mkdir(path, (int)mode);
    return MapToPosixRet(ret);
}

int rmdir(const char *path)
{
    int ret = los_unlink(path);
    return MapToPosixRet(ret);
}

int dup(int fd)
{
    int ret = los_dup(fd);
    return MapToPosixRet(ret);
}

int dup2(int oldFd, int newFd)
{
    int ret = los_dup2(oldFd, newFd);
    return MapToPosixRet(ret);
}

int lstat(const char *path, struct stat *buffer)
{
    return stat(path, buffer);
}

int fstat(int fd, struct stat *buf)
{
    struct file *filep;
    filep = los_attach_file(fd);
    if ((filep == NULL) || (filep->f_mp == NULL) || (filep->f_mp->m_path == NULL)) {
        return VFS_ERROR;
    }
    return stat(filep->f_mp->m_path, buf);
}

int fcntl(int fd, int cmd, ...)
{
    struct file *filep = NULL;
    va_list ap;
    int ret;
    va_start(ap, cmd);

    if ((uint32_t)fd < CONFIG_NFILE_DESCRIPTORS) {
        filep = los_attach_file(fd);
        ret = los_vfcntl(filep, cmd, ap);
    } else {
        ret = -EBADF;
    }

    va_end(ap);

    if (ret < 0) {
        set_errno(-ret);
        ret = VFS_ERROR;
    }
    return ret;
}

int ioctl(int fd, int func, ...)
{
    int ret;
    va_list ap;
    va_start(ap, func);
    ret = los_ioctl(fd, func, ap);
    va_end(ap);
    return ret;
}

ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
{
    int i;
    int ret;
    char *buf = NULL;
    char *curBuf = NULL;
    char *readBuf = NULL;
    size_t bufLen = 0;
    size_t bytesToRead;
    ssize_t totalBytesRead;
    size_t totalLen;

    if (iov == NULL) {
        return VFS_ERROR;
    }

    for (i = 0; i < iovcnt; ++i) {
        if ((SSIZE_MAX - bufLen) < iov[i].iov_len) {
            return VFS_ERROR;
        }
        bufLen += iov[i].iov_len;
    }
    if (bufLen == 0) {
        return VFS_ERROR;
    }
    totalLen = bufLen * sizeof(char);
    buf = (char *)malloc(totalLen);
    if (buf == NULL) {
        return VFS_ERROR;
    }

    totalBytesRead = read(fd, buf, bufLen);
    if ((size_t)totalBytesRead < totalLen) {
        totalLen = (size_t)totalBytesRead;
    }
    curBuf = buf;
    for (i = 0; i < iovcnt; ++i) {
        readBuf = (char *)iov[i].iov_base;
        bytesToRead = iov[i].iov_len;

        size_t lenToRead = totalLen < bytesToRead ? totalLen : bytesToRead;
        ret = memcpy_s(readBuf, bytesToRead, curBuf, lenToRead);
        if (ret != LOS_OK) {
            free(buf);
            return VFS_ERROR;
        }
        if (totalLen < (size_t)bytesToRead) {
            break;
        }
        curBuf += bytesToRead;
        totalLen -= bytesToRead;
    }
    free(buf);
    return totalBytesRead;
}

ssize_t writev(int fd, const struct iovec *iov, int iovcnt)
{
    int i;
    int ret;
    char *buf = NULL;
    char *curBuf = NULL;
    char *writeBuf = NULL;
    size_t bufLen = 0;
    size_t bytesToWrite;
    ssize_t totalBytesWritten;
    size_t totalLen;

    if (iov == NULL) {
        return VFS_ERROR;
    }

    for (i = 0; i < iovcnt; ++i) {
        if ((SSIZE_MAX - bufLen) < iov[i].iov_len) {
            set_errno(EINVAL);
            return VFS_ERROR;
        }
        bufLen += iov[i].iov_len;
    }
    if (bufLen == 0) {
        return VFS_ERROR;
    }
    totalLen = bufLen * sizeof(char);
    buf = (char *)malloc(totalLen);
    if (buf == NULL) {
        return VFS_ERROR;
    }
    curBuf = buf;
    for (i = 0; i < iovcnt; ++i) {
        writeBuf = (char *)iov[i].iov_base;
        bytesToWrite = iov[i].iov_len;
        if (((ssize_t)totalLen <= 0) || ((ssize_t)bytesToWrite <= 0)) {
            break;
        }
        ret = memcpy_s(curBuf, totalLen, writeBuf, bytesToWrite);
        if (ret != LOS_OK) {
            free(buf);
            return VFS_ERROR;
        }
        curBuf += bytesToWrite;
        totalLen -= bytesToWrite;
    }

    totalBytesWritten = write(fd, buf, bufLen);
    free(buf);

    return totalBytesWritten;
}
