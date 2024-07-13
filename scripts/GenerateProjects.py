#!/usr/bin/env python3

# cmake -B build/ -S . -G Ninja
# cmake --build build/
# echo "Running your app"
# build/out/bin/Sandbox

import subprocess


def build() -> int:
    result = subprocess.run(
        ["cmake", "-B", "build/", "-S", ".", "-G", "Ninja"]).returncode
    result = subprocess.run(["cmake", "--build", "build/"]).returncode

    return result


def run():
    subprocess.run(["build/out/bin/Sandbox"])


if build() == 0:
    should_run = input("Run program? y/n ")

    if should_run == "y" or should_run == "Y":
        run()
