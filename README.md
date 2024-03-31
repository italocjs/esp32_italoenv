# README
This is a sample of how to integrate CICD with esp32 development, this repository can be started as a docker container containing the required tools, or it can be used as an vscode devcontainer (open vscode in the folder, click on reopen as container) to automatically install an useful extension for task buttons.

## Features:
- ESPIDF + Arduino frameworks
- Easy menuconfig access
- Example of how to use custom board (ex simovatrack130)

### Currently working:
- arduino framework functions
- esp-idf framework functions
- build, run and test native code
- build, flash and test esp32dev code.

### Not working:
- under docker, c++ extension for vscode is unable to locate arduino.h but compiles ok
- under docker + windows, usb ports are hard to access, you might want to install platformio on the host an run vscode directly on windows, to access the COM PORT for local build and testing

## To setup the remote testing, check:
- how to connect to a remote device.md
- how_to_setup_raspberry_remote.md

## Dont forget to set the PLATFORMIO_AUTH_TOKEN on github actions with your actual key!
otherwise the actions will not be able to login to the remote device 

## Dependencies

This code uses italocjs/track_env:latest, which is built to speedup compilation process, but might be necessary to update it to your project.
```
# Use Python 3 as the base image
FROM python:3 as base

# Install PlatformIO
RUN pip install platformio

# Preinstall the 'native' platform
RUN platformio platform install native

# Preinstall the 'espressif32' platform and the specific Arduino framework version
RUN platformio platform install espressif32 --with-package framework-arduinoespressif32@https://github.com/italocjs/arduino-esp32.git#idf-release/v4.4
RUN pio platform install espressif32 --with-package=toolchain-xtensa-esp32 --with-package=toolchain-esp32ulp --with-package=framework-arduinoespressif32 --with-package=framework-espidf --with-package=tool-esptoolpy --with-package=tool-cmake --with-package=tool-ninja

# Preinstall the 'googletest' library
RUN platformio lib -g install googletest

# Copy a basic code so we can run the build
COPY minimal_source/ /workspace/
WORKDIR /workspace

# Run a PlatformIO build for each environment to download dependencies
# This step assumes your platformio.ini is configured for esp32dev and native environments

RUN platformio run -e native
RUN platformio run -e esp32dev

# This part of the process will NOT test agains any target, as this is meant to be an shared base image

# Clean up unnecessary files to keep the image size down
RUN rm -rf /workspace
```