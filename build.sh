#!/bin/sh

mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE:STRING=Debug && make && cd .. && ls -l bin && ls -l lib
chmod -R 0755 bin
