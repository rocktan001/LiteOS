/* ----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2019. All rights reserved.
 * Description: LiteOS Shell fs Command Implementation File
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

#include "unistd.h"
#include "stdio.h"
#include "securec.h"
#include "los_event.h"
#include "los_vfs.h"

#include "shcmd.h"
#include "shmsg.h"

#define DIR_PATH_LEN        256
#define DIR_CUR_PATH_LEN    128
typedef struct {
    int fd;
    int flags;
    uint32_t status;
    struct file *file;
    CHAR curPath[DIR_CUR_PATH_LEN];
    CHAR curFullPath[DIR_PATH_LEN];
} FsCB;

STATIC FsCB g_fsCmd =
{
    .curPath = "/",
    .curFullPath = "/"
};

// STATIC VOID PrintContent(VOID)
// {

// }

// STATIC VOID OsShellCmdDoFs(VOID *arg1)
// {

// }

// STATIC INT32 OsFsOptionParsed(UINT32 argc, UINT32 *argoff, const CHAR **argv, FsCB *fsItem)
// {

//     return 0;
// }

// STATIC INT32 OsFsCmdSplice(UINT32 argc, UINT32 argoff, const CHAR **argv, FsCB *fsItem)
// {
//     return 0;
// }

// STATIC UINT32 OsFsTaskCreate(FsCB *fsItem)
// {
//     return 0;
// }

UINT32 OsShellCmdMkdir(UINT32 argc, const CHAR **argv)
{
    int mode = 0;
    CHAR *bufMode = NULL;
    char tmp_buf[DIR_PATH_LEN] = {0};

    if (argc < 1) {
        PRINTK("One argument is required at least!");
        return LOS_NOK;
    }
    sprintf_s(tmp_buf, DIR_PATH_LEN, "%s%s/", g_fsCmd.curFullPath, argv[0]);
    if (argc == 1) {
       if (mkdir(tmp_buf, 0) == -1) {
           printf("mkdir fail.\n");
           return LOS_NOK;
       }
    }
    if (argc == 2) {
        mode = strtoul(argv[1], &bufMode, 0);
        if ((bufMode == NULL) || (*bufMode != 0)) {
            PRINTK("\nThe input mode is invalid. Please try again.\n");
            return LOS_NOK;
        }
       if (mkdir(tmp_buf, mode) == -1) {
           printf("mkdir fail.\n");
           return LOS_NOK;
       }
    }
    return LOS_OK;
}

UINT32 OsShellCmdList(UINT32 argc, const CHAR **argv)
{
    struct dirent *d_item = NULL;
    struct dir *target = NULL;
    char tmp_buf[DIR_PATH_LEN] = {0};

    if (argc > 1) {
        PRINTK("One argument is required!");
        return LOS_NOK;
    }

    sprintf_s(tmp_buf, DIR_PATH_LEN, "%s/", g_fsCmd.curFullPath);

    target = opendir(tmp_buf);
    if (target == NULL) {
        PRINTK("The command can be executed only in the directory below the fs root directory.");
        return LOS_NOK;
    }

    if (argc == 1) {
        PRINTK("Name        Type      Size\n");
    }
    do {
        d_item = readdir(target);
        if (d_item != NULL) {
            if (argc == 1) {
                if(strcmp(argv[0], "-l")) {
                    PRINTK("Argument error! Only support \"-l\"");
                    return LOS_NOK;
                }
                if (d_item->type == VFS_TYPE_DIR) {
                    PRINTK("%-10s  Dir       %-10u", d_item->name,  d_item->size);
                } else {
                    PRINTK("%-10s  File      %-10u", d_item->name,  d_item->size);
                }
                PRINTK("\n");
            } else {
                if (d_item->type == VFS_TYPE_DIR) {
                    PRINTK("%s/    ", d_item->name);
                } else {
                    PRINTK("%s    ", d_item->name);
                }
            }
        }
    } while(d_item != NULL);

    PRINTK("\n");
    closedir(target);
    return LOS_OK;
}

UINT32 OsShellCmdPwd(UINT32 argc, const CHAR **argv)
{
    PRINTK("%s\n", g_fsCmd.curFullPath);
    return LOS_OK;
}

UINT32 OsShellCmdCd(UINT32 argc, const CHAR **argv)
{
    char tmp_buf[DIR_PATH_LEN] = {0};
    struct dir *target = NULL;
    char *curPath = NULL;
    int pathLen = 0;

    if (argc != 1) {
        PRINTK("One argument is required !");
        return LOS_NOK;
    }

    if (argv[0][0] == '/') {
        curPath = strrchr(argv[0], '/');
        pathLen = strlen(curPath);

        target = opendir(argv[0]);
        if(target == NULL) {
            PRINTK("open dir failed.");
            return LOS_NOK;
        }

        memset_s(g_fsCmd.curFullPath, sizeof(g_fsCmd.curFullPath), 0, strlen(g_fsCmd.curFullPath));
        memcpy_s(g_fsCmd.curFullPath, sizeof(g_fsCmd.curFullPath), argv[0], strlen(argv[0]));
        memset_s(g_fsCmd.curPath, sizeof(g_fsCmd.curPath), 0, strlen(g_fsCmd.curPath));
        memcpy_s(g_fsCmd.curPath, sizeof(g_fsCmd.curPath), curPath, pathLen);
    } else if (!strcmp(argv[0], "..")) {
        g_fsCmd.curFullPath[strlen(g_fsCmd.curFullPath) - 1] = 0;
        curPath = strrchr(g_fsCmd.curFullPath, '/');
        pathLen = strlen(g_fsCmd.curFullPath) - strlen(curPath);

        memset_s(g_fsCmd.curFullPath + pathLen + 1, sizeof(g_fsCmd.curFullPath) - strlen(curPath) - 1, 0, pathLen - 1);

        target = opendir(g_fsCmd.curFullPath);

        if(target == NULL) {
            PRINTK("open dir failed.");
            return LOS_NOK;
        }

        memset_s(g_fsCmd.curPath, sizeof(g_fsCmd.curPath), 0, strlen(g_fsCmd.curPath));
        memcpy_s(g_fsCmd.curPath, sizeof(g_fsCmd.curPath), curPath, pathLen);
    } else {
        sprintf_s(tmp_buf, DIR_PATH_LEN, "%s%s/", g_fsCmd.curFullPath, argv[0]);
        target = opendir(tmp_buf);
        if(target == NULL) {
            PRINTK("open dir failed.");
            return LOS_NOK;
        }
        memcpy_s(g_fsCmd.curFullPath, sizeof(g_fsCmd.curFullPath), tmp_buf, strlen(tmp_buf));
        memset_s(g_fsCmd.curPath, sizeof(g_fsCmd.curPath), 0, strlen(g_fsCmd.curPath));
        memcpy_s(g_fsCmd.curPath, sizeof(g_fsCmd.curPath), argv[0], strlen(argv[0]));
    }
    closedir(target);
    return 0;
}

#if defined (LOSCFG_COMPONENTS_FS_VFS)
SHELLCMD_ENTRY(pwd_shellcmd, CMD_TYPE_EX, "pwd", XARGS, (CmdCallBackFunc)OsShellCmdPwd);

SHELLCMD_ENTRY(cd_shellcmd, CMD_TYPE_EX, "cd", XARGS, (CmdCallBackFunc)OsShellCmdCd);

SHELLCMD_ENTRY(mkdir_shellcmd, CMD_TYPE_EX, "mkdir", XARGS, (CmdCallBackFunc)OsShellCmdMkdir);

SHELLCMD_ENTRY(ls_shellcmd, CMD_TYPE_EX, "ls", XARGS, (CmdCallBackFunc)OsShellCmdList);
#endif