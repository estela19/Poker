#!/usr/bin/env bash

set -e

if [ $# -eq 0 ]
  then
    docker build -t e9857256/poker .
else
    docker build -f $1 -t e9857256/poker:$2 .
fi

docker run e9857256/poker
