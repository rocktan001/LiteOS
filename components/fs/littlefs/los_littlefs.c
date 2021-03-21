/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: Little Fs Implementation
 * Author: Huawei LiteOS Team
 * Create: 2021-01-07
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

#include "lfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errno.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "fs/los_vfs.h"
#include "fs/los_littlefs.h"
#include "los_printf.h"
#include "los_hwi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef struct {
    lfs_t *lfs_fs;
    lfs_file_t *lfs_file;
} LFS_P;

LFS_P g_lfs_p;

static lfs_t *littlefs_ptr;

static int ret_to_errno(int result)
{
    int err = 0;
    switch (result) {
        case LFS_ERR_OK:
            return 0;
        case LFS_ERR_IO:
            err = EIO;
            break;
        case LFS_ERR_NOENT:
            err = ENOENT;
            break;
        case LFS_ERR_EXIST:
            err = EEXIST;
            break;
        case LFS_ERR_NOTDIR:
            err = ENOTDIR;
            break;
        case LFS_ERR_ISDIR:
            err = EISDIR;
            break;
        case LFS_ERR_NOTEMPTY:
            err = ENOTEMPTY;
            break;
        case LFS_ERR_BADF:
            err = EBADF;
            break;
        case LFS_ERR_INVAL:
            err = EINVAL;
            break;
        case LFS_ERR_NOSPC:
            err = ENOSPC;
            break;
        case LFS_ERR_NOMEM:
            err = ENOMEM;
            break;
        case LFS_ERR_CORRUPT:
            err = ELIBBAD;
            break;
        default:
            err = EIO;
            break;
    }
    VFS_ERRNO_SET(err);

    return err;
}

static int littlefs_flags_get(int oflags)
{
    int flags = 0;
    switch (oflags & O_ACCMODE) {
        case O_RDONLY:
            flags |= LFS_O_RDONLY;
            break;
        case O_WRONLY:
            flags |= LFS_O_WRONLY;
            break;
        case O_RDWR:
            flags |= LFS_O_RDWR;
            break;
        default:
            break;
    }

    if (oflags & O_CREAT) {
        flags |= LFS_O_CREAT;
    }

    if ((oflags & O_EXCL)) {
        flags |= LFS_O_EXCL;
    }

    if (oflags & O_TRUNC) {
        flags |= LFS_O_TRUNC;
    }

    if (oflags & O_APPEND) {
        flags |= LFS_O_APPEND;
    }

    return flags;
}

static int littlefs_op_open(struct file *file, const char *path_in_mp, int flags)
{
    LFS_P *p = (LFS_P *)file->f_mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    lfs_file_t *f = p->lfs_file;
    int ret = lfs_file_open(lfs, f, path_in_mp, littlefs_flags_get(flags));
    if (ret == LFS_ERR_OK) {
        file->f_data = (void *)&f;
    }
    return ret_to_errno(ret);
}

static int littlefs_op_close(struct file *file)
{
    LFS_P *p = (LFS_P *)file->f_mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    lfs_file_t *f = p->lfs_file;
    int ret = lfs_file_close(lfs, f);
    return ret_to_errno(ret);
}

static ssize_t littlefs_op_read(struct file *file, char *buff, size_t bytes)
{
    LFS_P *p = (LFS_P *)file->f_mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    lfs_file_t *f = p->lfs_file;
    lfs_ssize_t ret;
    ret = lfs_file_read(lfs, f, (void *)buff, (lfs_size_t)bytes);
    if (ret < 0) {
        PRINT_ERR("failed to read, read size=%d\n", (int)ret);
        return ret_to_errno((int)ret);
    }
    return (ssize_t)ret;
}

static ssize_t littlefs_op_write(struct file *file, const char *buff, size_t bytes)
{
    LFS_P *p = (LFS_P *)file->f_mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    lfs_file_t *f = p->lfs_file;
    lfs_ssize_t ret;
    if ((buff == NULL) || (bytes == 0) || (lfs == NULL) || (f == NULL)) {
        return -EINVAL;
    }

    ret = lfs_file_write(lfs, f, (const void *)buff, (lfs_size_t)bytes);
    if (ret < 0) {
        PRINT_ERR("failed to write, write size=%d\n", (int)ret);
        return ret_to_errno((int)ret);
    }
    return (ssize_t)ret;
}

static off_t littlefs_op_lseek(struct file *file, off_t off, int whence)
{
    LFS_P *p = (LFS_P *)file->f_mp->m_data;
    lfs_soff_t ret;
    lfs_t *lfs = p->lfs_fs;
    lfs_file_t *f = p->lfs_file;
    if (f == NULL) {
        return -EINVAL;
    }
    ret = lfs_file_seek(lfs, f, (lfs_soff_t)off, whence);
    if (ret == LFS_ERR_OK) {
        return (off_t)off;
    } else {
        return ret_to_errno(ret);
    }
}

static off64_t littlefs_op_lseek64(struct file *file, off64_t off, int whence)
{
    return (off64_t)littlefs_op_lseek(file, (off_t)off, whence);
}

int littlefs_op_stat(struct mount_point *mp, const char *path_in_mp, struct stat *stat)
{
    struct lfs_info info;
    (void)memset_s(stat, sizeof(struct stat), 0, sizeof(struct stat));
    LFS_P *p = (LFS_P *)mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    int ret;
    ret = lfs_stat(lfs, path_in_mp, &info);
    if (ret == LFS_ERR_OK) {
        stat->st_size = info.size;
        stat->st_mode = ((info.type == LFS_TYPE_DIR) ? S_IFDIR : S_IFREG);
    }
    return ret_to_errno(ret);
}

static int littlefs_op_unlink(struct mount_point *mp, const char *path_in_mp)
{
    LFS_P *p = (LFS_P *)mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    int ret = lfs_remove(lfs, path_in_mp);
    return ret_to_errno(ret);
}

static int littlefs_op_rename(struct mount_point *mp, const char *path_in_mp_old, const char *path_in_mp_new)
{
    LFS_P *p = (LFS_P *)mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    int ret = lfs_rename(lfs, path_in_mp_old, path_in_mp_new);
    return ret_to_errno(ret);
}

static int littlefs_op_sync(struct file *file)
{
    int ret;
    LFS_P *p = (LFS_P *)file->f_mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    lfs_file_t *f = p->lfs_file;
    if ((lfs == NULL) || (f == NULL)) {
        return -EINVAL;
    }

    ret = lfs_file_sync(lfs, f);
    return ret_to_errno(ret);
}

static int littlefs_op_opendir(struct dir *dir, const char *path)
{
    int ret;
    LFS_P *p = NULL;
    lfs_dir_t *lfs_dir = NULL;
    lfs_t *lfs = NULL;

    if (dir == NULL) {
        PRINT_ERR("dir is null, open failed.\n");
        return -ENOMEM;
    }

    lfs_dir = (lfs_dir_t *)malloc(sizeof(lfs_dir_t));
    (void)memset_s(lfs_dir, sizeof(lfs_dir_t), 0, sizeof(lfs_dir_t));
    p = (LFS_P *)dir->d_mp->m_data;
    lfs = p->lfs_fs;

    ret = lfs_dir_open(lfs, lfs_dir, path);
    if (ret != LFS_ERR_OK) {
        free(lfs_dir);
        return ret_to_errno(ret);
    }
    dir->d_data = (void *)lfs_dir;
    dir->d_offset = 0;
    return LFS_ERR_OK;
}

static int littlefs_op_readdir(struct dir *dir, struct dirent *dent)
{
    LFS_P *p = (LFS_P *)dir->d_mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    lfs_dir_t *lfs_dir = (lfs_dir_t *)dir->d_data;
    struct lfs_info info;
    int ret;
    (void)memset_s(&info, sizeof(struct lfs_info), 0, sizeof(struct lfs_info));
    if (lfs_dir == NULL) {
        return -EINVAL;
    }
    do {
        ret = lfs_dir_read(lfs, lfs_dir, &info);
    } while ((ret >= 0) && ((strcmp(info.name, ".") == 0) || (strcmp(info.name, "..") == 0)));
    if (ret < 0) {
        return ENOENT;
    } else {
        strncpy_s((char *)dent->name, LOS_MAX_DIR_NAME_LEN, (const char *)info.name, LOS_MAX_FILE_NAME_LEN - 1);
        dent->name[LOS_MAX_FILE_NAME_LEN - 1] = '\0';
        dent->size = info.size;
        if (info.type == LFS_TYPE_DIR) {
            dent->type = VFS_TYPE_DIR;
        } else {
            dent->type = VFS_TYPE_FILE;
        }
    }
    return LOS_OK;
}

static int littlefs_op_closedir(struct dir *dir)
{
    int ret;
    LFS_P *p = (LFS_P *)dir->d_mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    lfs_dir_t *lfs_dir = (lfs_dir_t *)dir->d_data;
    if (lfs_dir == NULL) {
        return -EINVAL;
    }
    ret = lfs_dir_close(lfs, lfs_dir);
    if (ret == LFS_ERR_OK) {
        free(lfs_dir);
    }
    return ret_to_errno(ret);
}

static int littlefs_op_mkdir(struct mount_point *mp, const char *path)
{
    LFS_P *p = (LFS_P *)mp->m_data;
    lfs_t *lfs = p->lfs_fs;
    int ret;

    ret = lfs_mkdir(lfs, path);
    if (ret == LFS_ERR_NOENT) {
        int err;
        VFS_ERRNO_SET(ENOENT);
        err = ENOENT;
        return err;
    }
    return ret_to_errno(ret);
}

static struct file_ops littlefs_ops = {
    littlefs_op_open,
    littlefs_op_close,
    littlefs_op_read,
    littlefs_op_write,
    littlefs_op_lseek,
    littlefs_op_lseek64,
    littlefs_op_stat,
    littlefs_op_unlink,
    littlefs_op_rename,
    NULL, /* ioctl not supported for now */
    littlefs_op_sync,
    littlefs_op_opendir,
    littlefs_op_readdir,
    littlefs_op_closedir,
    littlefs_op_mkdir
    };

static struct file_system littlefs_fs = { "littlefs", &littlefs_ops, NULL, 0 };

int littlefs_init(void)
{
    static int littlefs_inited = FALSE;
    if (littlefs_inited) {
        return LFS_ERR_OK;
    }
    if (los_vfs_init() != LFS_ERR_OK) {
        return LOS_NOK;
    }
    if (los_fs_register(&littlefs_fs) != LFS_ERR_OK) {
        PRINT_ERR("failed to register fs!\n");
        return LOS_NOK;
    }
    littlefs_inited = TRUE;
    PRINT_INFO("register littlefs done!\n");
    return LFS_ERR_OK;
}

int littlefs_mount(const char *path, const struct lfs_config *lfs_cfg)
{
    int ret = -1;
    int err;
    lfs_t *fs = NULL;

    fs = (lfs_t *)malloc(sizeof(lfs_t));
    lfs_file_t *f = (lfs_file_t *)malloc(sizeof(lfs_file_t));

    g_lfs_p.lfs_fs = fs;
    g_lfs_p.lfs_file = f;

    if (fs == NULL) {
        PRINT_ERR("malloc memory failed!\n");
        goto err_free;
    }

    (void)memset_s(fs, sizeof(lfs_t), 0, sizeof(lfs_t));
    err = lfs_mount(fs, lfs_cfg);
    if (err == LFS_ERR_CORRUPT) {
        lfs_format(fs, lfs_cfg);
        err = lfs_mount(fs, lfs_cfg);
    }
    if (err != LFS_ERR_OK) {
        PRINT_ERR("format fail!\n");
        goto err_unmount;
    }
    ret = los_fs_mount("littlefs", path, &g_lfs_p);
    if (ret == LFS_ERR_OK) {
        PRINT_INFO("littlefs mount at %s done!\n", path);
        littlefs_ptr = fs;
        return LFS_ERR_OK;
    }
    PRINT_ERR("failed to mount!\n");
err_unmount:
    lfs_unmount(fs);
err_free:
    if (fs != NULL) {
        free(fs);
    }
    return ret;
}

int littlefs_unmount(const char *path)
{
    int ret = LFS_ERR_OK;
    if (littlefs_ptr != NULL) {
        ret = lfs_unmount(littlefs_ptr);
        free(littlefs_ptr);
        littlefs_ptr = NULL;
    }
    los_fs_unmount(path);
    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
