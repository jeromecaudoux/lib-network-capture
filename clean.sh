#!/bin/sh

git clean -f bin
git clean -f lib
git clean -f build

rm -rf build
rm -rf lib
rm -rf debian/usr/
