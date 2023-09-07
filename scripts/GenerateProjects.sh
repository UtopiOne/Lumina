gen() {
    cmake -B build/ -S .
}

run() {
    build/out/bin/Sandbox
}

create() {
    gen
    cmake --build build/
    echo "Running your app"
    echo
    run
}
