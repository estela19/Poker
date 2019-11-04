#!/usr/bin/env bash

set -e

if [ $# -eq 0 ]
  then
    docker build -t jyp10987/aichu .
else
    docker build -f $1 -t jyp10987/aichu:$2 .
fi

docker run jyp10987/aichu
