#!/bin/bash

#rm -rf Hagfish

#cp -r ../hagfish ./Hagfish

make -C BaseTools/

export EDK_TOOLS_PATH=$(pwd)/BaseTools

. ./edksetup.sh BaseTools

export CROSS_COMPILE=aarch64-linux-gnu-

if [ $1x == "Hagfish"x ]; then
    build -a AARCH64 -t ARMGCC -p Hagfish/Hagfish.dsc -m Hagfish/Application/Hagfish/Hagfish.inf -b DEBUG
elif [ $1x == "Shell"x ]; then
    build -a AARCH64 -t ARMGCC -p ShellPkg/ShellPkg.dsc -m ShellPkg/Application/Shell/Shell.inf -b DEBUG
elif [ $1x == "Hello"x ]; then
    build -a AARCH64 -t ARMGCC -p HelloFile/HelloFile.dsc -m HelloFile/Application/HelloFile/HelloFile.inf -b DEBUG
else
    echo "Usage: build.sh target"
    echo "       target can be Hagfish | Shell | Hello"
    exit -1
fi
