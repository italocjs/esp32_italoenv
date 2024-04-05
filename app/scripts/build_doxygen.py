import subprocess
import os
import sys

# ANSI escape codes for colors
RED = '\033[91m'
GREEN = '\033[92m'
RESET = '\033[0m'

# Get the current working directory from the environment
current_directory = os.getenv("PWD")

# Define the relative path to the Doxyfile
doxyfile_rel_path = 'Doxyfile'

# Combine the current working directory and the relative path to obtain the absolute path to the Doxyfile
doxyfile_abs_path = os.path.join(current_directory, doxyfile_rel_path)

# Check if the Doxyfile exists
if not os.path.isfile(doxyfile_abs_path):
    print(f"{RED}Error: The Doxyfile was not found at {doxyfile_abs_path}{RESET}")
    sys.exit(1)

# Command to execute Doxygen with the Doxyfile
command = ['doxygen', doxyfile_abs_path]

try:
    result = subprocess.run(command, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print(f"{GREEN}Doxygen documentation generated successfully.{RESET}")
except subprocess.CalledProcessError as e:
    print(f"{RED}Failed to generate Doxygen documentation. Error: {e}{RESET}")
    print(f"{RED}Output: {e.stderr.decode()}{RESET}")  # Print the stderr if an error occurred