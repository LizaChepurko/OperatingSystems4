#!/bin/bash

# Compile the C++ program
g++ -o guard MutexGuard.cpp -pthread

run() {
    local commands=$1
    ./guard << EOL
$commands
EOL
}

# Run
echo "Running MutexGuard.cpp..."
run


