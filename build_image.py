import subprocess
import os
import platform

# Configuration Variables
DOCKERFILE_LOCATION = '.'  # Directory where the Dockerfile is located
REPOSITORY_NAME = 'italocjs/track_env'  # Docker repository name
VERSION = 'latest'  # Tag version

# ANSI color codes for terminal output
GREEN = '\033[0;32m'
RED = '\033[0;31m'
YELLOW = '\033[0;33m'
RESET = '\033[0m'  # Reset color

def is_docker_installed():
    """
    Checks if Docker is installed by attempting to run `docker --version`.
    Returns True if Docker is installed, False otherwise.
    """
    try:
        subprocess.run(['docker', '--version'], check=True)
        return True
    except (subprocess.CalledProcessError, FileNotFoundError):
        return False

def print_system_info():
    """
    Prints the current working directory, the username of the user running the script,
    the operating system, and detailed system information.
    """
    print("Current Location:", os.getcwd())
    print("User:", os.getlogin())
    print("System:", platform.system())
    print("System Information:", platform.platform())

def run_command(command):
    """
    Executes a shell command and returns True if the command was executed successfully,
    or False if the command failed. Also prints 'Success' in green for success,
    or 'Failure' in red for failure.
    """
    try:
        subprocess.run(command, shell=True, check=True, text=True)
        print(GREEN + 'Success' + RESET)
        return True
    except subprocess.CalledProcessError:
        print(RED + 'Failure' + RESET)
        return False


def main():
    """
    Main function to check Docker installation, print system info, build and push a Docker image
    only if the build is successful. The Dockerfile location, repository name, and version
    are configurable at the start of the script.
    """
    if not is_docker_installed():
        print(YELLOW + 'Docker is not installed. Please install Docker to proceed.' + RESET)
        return

    print_system_info()

    # Build the Docker image
    build_command = f'docker build -t {REPOSITORY_NAME}:{VERSION} {DOCKERFILE_LOCATION}'
    print("Building Docker image...")
    build_success = run_command(build_command)

    if build_success:
        # Push the Docker image only if build was successful
        push_command = f'docker push {REPOSITORY_NAME}:{VERSION}'
        print("Pushing Docker image...")
        run_command(push_command)
    else:
        print(RED + "Build failed, not pushing the image." + RESET)

if __name__ == '__main__':
    main()