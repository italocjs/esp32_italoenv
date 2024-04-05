#!/bin/bash

# Check Python version
python_version=$(python --version 2>&1)
if [ $? -eq 0 ]; then
    echo "Python version: $python_version"
else
    echo "Python is not installed or not in PATH"
fi

# Check PIO version
pio_version=$(pio --version 2>&1)
if [ $? -eq 0 ]; then
    echo "PIO version: $pio_version"
else
    echo "PIO is not installed or not in PATH"
fi