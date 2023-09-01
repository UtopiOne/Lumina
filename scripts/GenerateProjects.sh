gen() {
    cmake -B build/ -S .
}

run() {
    build/Sandbox
}

create() {
    gen
    cmake --build build/
    echo "Running your app"
    echo
    run
}
