gen() {
    cmake -B build/ -S . -G Ninja
}

build() {
    gen
    cmake --build build/
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
