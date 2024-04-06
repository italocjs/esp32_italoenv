<!-- [![Actions Status](https://github.com/{user}/{repo}/workflows/{action}/badge.svg)](https://github.com/{user}/{repo}/actions) -->
[![Build and testing](https://github.com/italocjs/esp32_italoenv/workflows/make_tests/badge.svg)](https://github.com/italocjs/make_tests/actions)
[![Documentation](https://github.com/italocjs/esp32_italoenv/workflows/make_doxygen/badge.svg)](https://github.com/italocjs/make_doxygen/actions)

# README
This is a sample of how to integrate CICD with esp32 development. This repository can be started as a docker container containing the required tools, or it can be used as a VSCode devcontainer (open VSCode in the folder, click on reopen as container) to automatically load the environment and install useful extensions for task buttons.

## Features:
- ESPIDF + Arduino frameworks
- Easy menuconfig access
- Example of how to use custom board (ex simovatrack130)
- Task buttons for easy access to common tasks (defined in `.vscode/settings.json`)
  - Build, run, and test native code
  - Build, flash, and test esp32dev code
  - Monitor serial port with decoding tools
  - Update documentation using Doxygen

### Currently working:
- Arduino framework functions
- esp-idf framework functions
- Build, run, and test native code
- Build, flash, and test esp32dev code
- Build doxygen documentation with prettyfied css layer

### Not working:
- Under docker, C++ extension for VSCode is unable to locate `arduino.h` but compiles just fine. *Help wanted here! i've been unable to setup this yet and is very useful*
- Under docker + Windows, USB ports are hard to access. You might want to install PlatformIO on the host and run VSCode directly on Windows to access the COM PORT for local build and testing.  to run PIO under the host, you can open the folder locally instead of as an container, install the extension platformio and let it automatically download all dependencies.   You shall then have access to the PIO tools directly under windows host.

## Setup

### Remote Testing
To set up remote testing, check:
- [`How to connect to remote device using pio remote`](docs\connecting_to_remote.md)
- [`How to setup remote server using pio remote and raspberry`](docs\how_to_setup_raspberry_remote.md)

Don't forget to set the `PLATFORMIO_AUTH_TOKEN` on GitHub Actions with your actual pio account token! Otherwise, the actions will not be able to log in to the remote device.
When running remote build on local pc, you must either login to you account or use a token too

### Updating the Base Image
If you need to update the base image (`italocjs/track_env:latest`), you can use the `build_image.py` script. This script automates the process of building and pushing Docker images, which is particularly useful for GitHub Actions as it allows for the creation of pre-built environments, significantly reducing setup times by pre-downloading all necessary requisites.

- [`How to build new image`](docs\building_new_image.md)

### Configuring the Doxygen
- Recommended to use the doxygen wizard
- Doxygen settings are located in the `app/Doxyfile`

# Final notes:
This base repository has been created to help me setup my development environment. Feel free to use it as a base for your own projects.
There is absolutely NO WARRANTY, use at your own risk. if you end up burning your computer, don't blame me, blame yourself.

This environment introduces a few new concepts for the new "arduino programmer" which is used to program in Arduino IDE:
- using vscode as editor and platformio as IDE
- using github to keep track of changes
- using github actions for CI/CD
- using docker to isolate the environment
- using unitary tests in both "fake" (native) and "real" (esp32) environments.

Author: Italo C J Soares (italocjs@live.com)


