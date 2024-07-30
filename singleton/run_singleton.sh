#!/bin/bash

# Compile the C++ program
g++ -o singleton_threads Singleton.cpp -pthread

run() {
    local commands=$1
    ./singleton_threads << EOL
$commands
EOL
}

# Run
echo "Running Singleton.cpp..."
run


