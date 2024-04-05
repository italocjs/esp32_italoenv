# Executing the build_image.py Script for Docker Images

The script automates the process of building and pushing Docker images. This is particularly useful for GitHub Actions, as it allows for the creation of pre-built environments, significantly reducing setup times by pre-downloading all necessary requisites.

## Purpose

The script is designed to:
- Verify Docker installation.
- Display system information.
- Build a Docker image from a specified Dockerfile.
- Push the built image to a Docker repository.

This automation is crucial for maintaining consistent environments in CI/CD pipelines, especially in GitHub Actions.

## Requirements

- **Docker**: Needed for building and pushing images.
- **Python**: Required to run the script.

### Installation

#### Windows

- **Docker**: Install Docker Desktop from [Docker Hub](https://hub.docker.com/editions/community/docker-ce-desktop-windows).
- **Python**: Install Python from [python.org](https://www.python.org/downloads/windows/).

#### Linux

- **Docker**:
  ```bash
  sudo apt-get update
  sudo apt-get install docker-ce docker-ce-cli containerd.io
  ```
- **Python**:
  ```bash
  sudo apt-get update
  sudo apt-get install python3
  ```

### Note

The script is optimized for Linux, aligning with the typical GitHub Actions execution environment. This ensures compatibility and consistency.

## Execution

1. Ensure Docker and Python are installed and configured.
2. Open a terminal or command prompt.
3. Navigate to the directory containing `build_image.py`.
4. Execute the script:
   ```bash
   python3 build_image.py
   ```

The script will check for Docker, display system info, build the Docker image using the specified Dockerfile, and push it to the Docker repository.

## Configuration

Adjust the following variables in the script as needed:

- `DOCKERFILE_LOCATION`: Location of your Dockerfile.
- `REPOSITORY_NAME`: Your Docker repository name.
- `VERSION`: Tag version of your Docker image.

## Updating GitHub Actions Workflow

After pushing the new image, update your GitHub Actions workflow file to use the new image. This ensures your CI/CD pipeline uses the pre-built environment, enhancing efficiency.

## Conclusion

The `build_image.py` script streamlines the Docker image building and pushing process, making it an invaluable tool for developers aiming to automate their CI/CD pipelines. By utilizing pre-built Docker images, build setup times in GitHub Actions can be significantly reduced.