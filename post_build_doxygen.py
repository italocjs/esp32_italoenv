import subprocess
import os
import sys

# Get the current working directory from the environment
current_directory = os.getenv("PWD")

# Define the relative path to the Doxyfile
doxyfile_rel_path = 'Doxyfile'

# Combine the current working directory and the relative path to obtain the absolute path to the Doxyfile
doxyfile_abs_path = os.path.join(current_directory, doxyfile_rel_path)

# Check if the Doxyfile exists
if not os.path.isfile(doxyfile_abs_path):
    print(f"Error: The Doxyfile was not found at {doxyfile_abs_path}")
    sys.exit(1)

# Command to execute Doxygen with the Doxyfile
command = ['doxygen', doxyfile_abs_path]

# Execute the command
try:
    subprocess.run(command, check=True)
    print("Doxygen documentation generated successfully.")
except subprocess.CalledProcessError as e:
    print("Failed to generate Doxygen documentation. Error:", e)
