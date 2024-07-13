#!/bin/sh
set -e
cmake -B build/ -S . -G Ninja
cmake --build build/
echo "Running your app"
build/out/bin/Sandbox
