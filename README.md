<!-- [![Actions Status](https://github.com/{user}/{repo}/workflows/{action}/badge.svg)](https://github.com/{user}/{repo}/actions) -->
[![Build and testing](https://github.com/italocjs/esp32_italoenv/workflows/make_tests/badge.svg)](https://github.com/italocjs/make_tests/actions)
[![Documentation](https://github.com/italocjs/esp32_italoenv/workflows/make_doxygen/badge.svg)](https://github.com/italocjs/make_doxygen/actions)

# ESP32 Development Environment Integration Guide

This is a sample development environment for ESP32 projects, leveraging a variety of tools to ensure a smooth and consistent development process over any platform (such as Windows, Linux, MacOS, Containers, github actions, etc) with automatic testing on remote devices and documentation generation.

## Features

- **VSCode**: Utilized as the primary code editor. Compatible with Windows, Linux, and even unconventional operating systems.
- **Docker**: Provides an isolated development environment to eliminate "it works on my machine" issues, ensuring consistency across development and testing stages.
- **PlatformIO CLI**: Serves as the Integrated Development Environment (IDE) for managing project dependencies, compilation, testing, and remote device communication.
- **GitHub Actions**: Automates Continuous Integration/Continuous Deployment (CI/CD) processes, enabling automatic test execution and documentation builds upon code commits.
- **GitHub Pages**: Automates updates to the project documentation, making it easier to maintain and share.
- **Doxygen**: Generates visually appealing HTML documentation for your project, facilitating easier code understanding and maintenance.
- **Unit Testing**: Supports both native and ESP32 environments, ensuring code reliability and functionality.
- **PIO Remote**: Guides on setting up remote testing on ESP32 devices using a Raspberry Pi 3B+ or any compatible device with PlatformIO installed.

### Currently working:
- write for esp-idf and Arduino frameworks
- Easy access to menuconfig, while maintaining easy access to all arduino libraries
- Example of how to use custom board (simovatrack130, which has some custom parameters such as more flash memory, custom partitions, etc)
- Task buttons for easy access to common tasks (defined in `.vscode/settings.json`)
  - Build, run, and test native code
  - Build, flash, and test esp32dev code both locally and remotely using pio remote
  - Monitor serial port with decoding tools
  - Update app documentation using doxygen (located at /app/doxygen-output/html/index.html)
- Publish the documentation to github pages, see [`Project Documentation`](https://italocjs.github.io/esp32_italoenv/)

### Not working:
- Under the container i was not able to make the C++ extension for VSCode correctly locate `arduino.h` but compiles just fine. *Help wanted here*
- Under Windows, USB ports are hard to access, so i did not.  only using the remote testing feature. but it is possble and i might take a look on it later


## Setup

### Remote Testing
To set up remote testing, check:
- [`How to connect to remote device using pio remote`](docs\connecting_to_remote.md)
- [`How to setup remote server using pio remote and raspberry`](docs\setup_raspberry_remote.md)

Don't forget to set the `PLATFORMIO_AUTH_TOKEN` on GitHub Actions with your actual pio account token! Otherwise, the actions will not be able to log in to the remote device.
When running remote build on local pc, you must either login to you account or use a token too

### Updating the Base Image
If you need to update the base image (`italocjs/track_env:latest`), you can use the `build_image.py` script. This script automates the process of building and pushing Docker images, creating a pre-built environments with your needs and dependencies in platformio.ini, This will significantly reduce setup times by pre-downloading all necessary requisites.
For information plase check: [`How to build new image`](docs\building_new_image.md)

### Configuring the Doxygen
- Recommended to use the doxygen wizard to manage settings
- Doxygen settings are located in the `app/Doxyfile`

## Using the repository locally:
Clone this repository, open VSCode in the folder, click on reopen as container, wait for the container to start, wait for the extensions to install, and you are ready to go!

## Using GitHub Actions:
You need to store your `PLATFORMIO_AUTH_TOKEN` as a secret on GitHub Actions. Otherwise, the actions will not be able to log in to the remote device. check [`How to setup pio remote`](docs\how_to_setup_pio_remote.md)

# Final notes:
This base repository has been created to help me setup my development environment for a product based on esp32. Feel free to use it as a base for your own projects.

This environment introduces a few new concepts for the new "arduino programmer" which is used to program in Arduino IDE:
- using vscode as editor and platformio as IDE
- using github to keep track of changes
- using github actions for CI/CD
- using docker to isolate the environment
- using unitary tests in both "fake" (native) and "real" (esp32) environments.

I plan on making a video / post blog about this later to share with my coworkers and the community, as i see that most firmware devs are missing out on ci/cd, docker, vscode and github.

Author: Italo C J Soares (italocjs@live.com)


