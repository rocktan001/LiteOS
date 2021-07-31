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

    if (argc < 1) {
        PRINTK("One argument is required at least!");
        return LOS_NOK;
    }
    if (argc == 1) {
        mkdir(argv[0], 0);
    }
    if (argc == 2) {
        mode = strtoul(argv[1], &bufMode, 0);
        if ((bufMode == NULL) || (*bufMode != 0)) {
            PRINTK("\nThe input mode is invalid. Please try again.\n");
            return 0;
        }
        mkdir(argv[1], mode);
    }
    return 0;
}

UINT32 OsShellCmdPwd(UINT32 argc, const CHAR **argv)
{
    PRINTK("%s\n", g_fsCmd.curFullPath);
    return 0;
}

UINT32 OsShellCmdCd(UINT32 argc, const CHAR **argv)
{
    struct dir *target = NULL;
    if (argc != 1) {
        PRINTK("One argument is required !");
        return LOS_NOK;
    }
    if (argv[0][0] == '/') {
        if (strlen(g_fsCmd.curFullPath) != 1 && target != NULL) {
            closedir(target);
        }
        target = opendir(argv[0]);
    } else {
        sprintf_s(g_fsCmd.curFullPath, DIR_PATH_LEN, "%s%s/", g_fsCmd.curFullPath, argv[0]);
        target = opendir(g_fsCmd.curFullPath);
    }
    memcpy_s(g_fsCmd.curPath, sizeof(g_fsCmd.curPath), target->d_dent.name, strlen(target->d_dent.name));
    return 0;
}

SHELLCMD_ENTRY(pwd_shellcmd, CMD_TYPE_EX, "pwd", XARGS, (CmdCallBackFunc)OsShellCmdPwd);

SHELLCMD_ENTRY(cd_shellcmd, CMD_TYPE_EX, "cd", XARGS, (CmdCallBackFunc)OsShellCmdCd);

SHELLCMD_ENTRY(mkdir_shellcmd, CMD_TYPE_EX, "mkdir", XARGS, (CmdCallBackFunc)OsShellCmdMkdir);