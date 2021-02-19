#!/bin/bash

g_pathExe=""
g_componentName=""
g_componentPath=""
g_componentEnableFlag=""
g_componentDownloadAddr=""
g_patchFile="origin.patch"
g_downloadTimeout=120


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

    mkdir patch
    cd -
    cd ${g_componentPath}/patch

    git init
    git config core.sparseCheckout true
    echo ${patchFilePath} >> .git/info/sparse-checkout
    echo "[Info]: Start download ${g_componentName} patch."
    timeout ${g_downloadTimeout} git remote add origin http://gitee.com/LiteOS/LiteOS_Components.git
    if [ $? -ne 0 ]; then
        echo "[Error]: Download ${g_componentName} patch failed!"
        cd -
        return 1
    fi
    git pull origin master
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
    cd ${g_componentPath}

    echo "[Info]: Start download ${g_componentName} source code."
    timeout ${g_downloadTimeout} ${g_componentDownloadAddr}
    if [ $? -ne 0 ]; then
        echo "[Error]: Download ${g_componentName} source code failed!"
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
    g_componentDownloadAddr=`echo $1 | awk -F '&#&' '{print $4}' | sed -e 's/^[ \t]*//g' -e 's/[ \t]*$//g'`

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
        echo "[Error]: The $1 file does noe exist or the path is incorrect!"
        return -1
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
    else
        g_pathExe="$1"
    fi

    ReadComponentsInfo "components/online_components"
}
Main "$1"
