#!/bin/bash

# Compile the C++ program
make

run_graph_1() {
    local commands=$1
    ./graph -v 5 -e 6 -s 42 << EOL
$commands
EOL
}

run_graph_2() {
    local commands=$1
    ./graph -v 5 -e 6 -s 30 << EOL
$commands
EOL
}

run_graph_3() {
    local commands=$1
    ./graph -v 3 -e 3 -s 4 << EOL
$commands
EOL
}

# Run
echo "Running graph with parameters -v 5 -e 6 -s 42 ..."
run_graph_1 

# Run
echo "Running graph with parameters -v 5 -e 6 -s 30 ..."
run_graph_2 

# Run
echo "Running graph with parameters -v 3 -e 3 -s 4 ..."
run_graph_3
