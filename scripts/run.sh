#!/bin/bash

# Function: Check if a command exists
check_command() {
    command -v "$1" >/dev/null 2>&1
}

PYTHON=python
VISUALIZE=1

# Check if 'python' is available
if ! check_command $PYTHON; then
    PYTHON=python3
    # Check if 'python3' is available
    if ! check_command $PYTHON; then
        echo "Python environment could not be found for visualization."
        VISUALIZE=0
    fi
fi

DIR=$(dirname "$0")
DIR="$DIR/.."      
cd "$DIR/code" || { echo "Failed to change directory to $DIR/code"; exit 1; }

cmake CMakeLists.txt
if [ $? -ne 0 ]; then
    echo "CMake configuration failed."
    exit 1
fi

cmake --build . --config Release
if [ $? -ne 0 ]; then
    echo "Build process failed."
    exit 1
fi

# Execute the project with parameters
./elastic_deformation 1000 100000
if [ $? -ne 0 ]; then
    echo "Execution of the project failed."
    exit 1
fi

# If visualization is enabled, install Python dependencies and run the visualizer
if [ $VISUALIZE -eq 1 ]; then
    # Install dependencies for Python
    $PYTHON -m pip install -r requirements.txt
    if [ $? -ne 0 ]; then
        echo "Failed to install Python dependencies."
        exit 1
    fi

    # Run visualization
    $PYTHON visualizer.py true
    if [ $? -ne 0 ]; then
        echo "Visualization process failed."
        exit 1
    fi
fi
