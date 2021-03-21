#!/bin/bash

g_pathExe=""
g_md5sumExe=""
g_componentName=""
g_componentPath=""
g_componentEnableFlag=""
g_componentDownloadAddr=""
g_patchFile="origin.patch"
g_downloadTimeout=120

Md5sumCheck()
{
    local count=0
    local ret=0;

    while read line
    do
        let count++
        if [ "$line" ]; then
            oldMd5sum="`echo "$line" | awk -F ' ' '{print $1}'`"
            fileString="`echo "$line" | awk -F ' ' '{print $2}'`"

            md5sum="`${g_md5sumExe} ${fileString}`"
            if [ $? -ne 0 ]; then
                let ret++
            fi
            newMd5sum="`echo "${md5sum}" | awk -F ' ' '{print $1}'`"
            #echo "[Info]: ${oldMd5sum} ${fileString} ${newMd5sum}"
            if [ "${oldMd5sum}" != "${newMd5sum}" ]; then
                echo "[Error]: ${fileString} md5 check failed!"
            fi
        fi
    done < md5.txt
    return $ret
}

ApplyPatch()
{
    cd ${g_componentPath}
    patchFile="${g_patchFile}"
    rm -rf patch
    if [ -e ${patchFile} ]; then
       echo "[Info]: Apply patch."
       "${g_pathExe}" -p1 -N < ${patchFile}
        if [ $? -ne 0 ]; then
            echo "[Error]: Apply patch failed!"
        fi
    else
       echo "[Info]: ${patchFile} not exist."
    fi
    cd -
    return 0
}

DownloadPatch()
{
    cd ${g_componentPath}
    patchFile="${g_patchFile}"
    patchFilePath="${g_componentPath}/${patchFile}"

    if [ -e "patch" ]; then
        rm -rf patch
    fi
    mkdir patch
    cd -
    cd ${g_componentPath}/patch

    git init
    git config core.sparseCheckout true
    echo ${patchFilePath} >> .git/info/sparse-checkout
    echo "[Info]: Start download ${g_componentName} patch."
    git remote add origin http://gitee.com/LiteOS/LiteOS_Components.git
    timeout ${g_downloadTimeout} git pull origin master
    if [ $? -ne 0 ]; then
        echo "[Error]: Download ${g_componentName} patch failed!"
        cd -
        return 1
    fi

    if [ ! -e ${patchFilePath} ]; then
       echo "[Error]: ${patchFilePath} does not exist on the website."
    else
        cp ${patchFilePath} ../
    fi
    git config core.sparseCheckout false

    cd -
    ApplyPatch

    return 0
}

DownloadSource()
{
    local iNum=3
    local md5Ret=0
    cd ${g_componentPath}

    echo "[Info]: Start download ${g_componentName} source code."
    while [ ${iNum} -gt 0 ]
    do
        if [ -e ${g_componentName} ]; then
            rm -rf ${g_componentName}
        fi

        timeout ${g_downloadTimeout} ${g_componentDownloadAddr}
        if [ $? -ne 0 ]; then
            let iNum--
        else
            #Md5sumCheck
            #md5Ret=$?
            if [ $md5Ret -ne 0 ]; then
                echo "[Error]: md5sum check fails for ${md5Ret} files in ${g_componentName}!"
                let iNum--
            else
                break
            fi
        fi
    done

    if [ $iNum -le 0 ]; then
        echo "[Error]: Download ${g_componentName} source code failed!"
        if [ -e ${g_componentName} ]; then
            rm -rf ${g_componentName}
        fi
        cd -
        return 1
    fi

    cd -
    DownloadPatch
    return 0
}

ComponentsIfEnable()
{
    isEnable="NotEnable`cat .config | grep -w "${g_componentEnableFlag}"`"
    fileIsExist="${g_componentPath}/${g_componentName}"

    if [ ${isEnable} != "NotEnable" ]; then
        if [ ! -e ${fileIsExist} ]; then
            DownloadSource ${g_componentName}
        else
            echo "[Info]: ${fileIsExist} is exist."
        fi
    fi
    return 0
}

ParseComponentsInfo()
{
    g_componentName=`echo $1 | awk -F '&#&' '{print $1}' | sed -e 's/^[ \t]*//g' -e 's/[ \t]*$//g'`
    g_componentPath=`echo $1 | awk -F '&#&' '{print $2}' | sed -e 's/^[ \t]*//g' -e 's/[ \t]*$//g'`
    g_componentEnableFlag=`echo $1 | awk -F '&#&' '{print $3}' | sed -e 's/^[ \t]*//g' -e 's/[ \t]*$//g'`
    g_componentDownloadAddr=`echo $1 | awk -F '&#&' '{print $4}' | sed -e 's/^[ \t]*//g' -e 's/[ \t]*$//g' | tr -d "\n" | tr -d "\r"`

    if [ ! -e ${g_componentPath} ]; then
        echo "[Info]: ${g_componentPath} not exist."
        return 1
    fi

    #echo "[Info]: ${g_componentName} ${g_componentPath} ${g_componentEnableFlag} ${g_componentDownloadAddr}"
    ComponentsIfEnable ${g_componentName} ${g_componentPath} ${g_componentEnableFlag} ${g_componentDownloadAddr}
    return 0
}

ReadComponentsInfo()
{
    local count=0
    if [ ! -e $1 ]; then
        echo "[Error]: The $1 file does not exist or the path is incorrect!"
        return 1
    fi

    while read line
    do
        let count++
        if [ "$line" ]; then
            ParseComponentsInfo "$line"
        fi
    done < $1
    return 0
}

Main()
{
    local OS=`uname -s`
    if [ $OS = "Linux" ]; then
        g_pathExe=`which patch`
        g_md5sumExe=`which md5sum`
    else
        g_pathExe="$1"
        g_md5sumExe="$2"
    fi

    ReadComponentsInfo "components/online_components"
}
Main "$1"

