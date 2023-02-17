#!/bin/sh

cd ./cmake-build-debug
cp ./caesar-cipher ./caesar-cipher-optimized
strip ./caesar-cipher-optimized
upx ./caesar-cipher-optimized