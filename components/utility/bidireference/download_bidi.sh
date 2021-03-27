#!/bin/bash

g_downloadTimeout=120
g_file1="source/bidiref.c"
g_file2="source/bidirefp.h"
g_file3="source/brinput.c"
g_file4="source/brrule.c"
g_file5="source/brtable.c"
g_file6="source/brtest.c"
g_file7="source/brutils.c"
g_file8="include/bidiref.h"

DownloadFile()
{
    timeout ${g_downloadTimeout} wget http://unicode.org/Public/PROGRAMS/BidiReferenceC/8.0.0/$1 -O ./BidireferenceC-8.0.0/$1

    if [ $? -ne 0 ]; then
      rm -rf BidireferenceC-8.0.0
      echo "[Error]: download fail!"
      return 0
    fi
}

DownloadSource()
{
    i=1
    while [ $i -le 8 ]
    do
        file="g_file$i"
        fileName=`eval echo '$'${file}`
        let i++
        echo "[Info]: filename = ${fileName}"
        DownloadFile ${fileName}
    done
}

Download()
{
    mkdir BidireferenceC-8.0.0
    mkdir BidireferenceC-8.0.0/source
    mkdir BidireferenceC-8.0.0/include

    DownloadSource
}

Main()
{
    local OS=`uname -s`
    if [ $OS = "Linux" ]; then
        Download
    else
        echo "[Info]: only support Linux!"
        return 0
    fi
}

Main
