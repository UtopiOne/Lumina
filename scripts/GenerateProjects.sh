gen() {
    vendor/premake/premake5 gmake2
}

run() {
    bin/Debug-linux-x86_64/Sandbox/Sandbox
}

create() {
    gen
    make
    echo "Running your app"
    echo
    run
}