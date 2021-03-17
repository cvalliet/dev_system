#!/bin/sh

if [ ! -d "./archives" ]
then
    mkdir ./archives
fi

name=$(date '+%Y%m%d_%H%M%S')
tar --exclude='./build' --exclude='./archives' -czvf ./archives/"${name}_dev_system.tgz" .
