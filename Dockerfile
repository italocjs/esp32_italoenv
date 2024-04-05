#remember to use -y to apt install stuff that asks for confirmation.

# FROM ubuntu:latest
FROM python:3.8-slim

RUN echo "Hello World, we are at $(pwd), with user $(whoami), and these are the folder list $(ls -la)"

RUN apt update
RUN apt upgrade -y
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install git -y

RUN apt-get install -y \
    python3-pip
    # python3 \

RUN apt install doxygen -y

RUN pip install platformio

RUN echo "apt updated, git installed, python installed, doxygen installed, platformio installed"

# Copy the content of /app on local to container, and cd to it
COPY app/ /app/
WORKDIR /app
RUN echo "Working directory set to /app, we are at $(pwd), with user $(whoami), and these are the folder list $(ls -la)"

RUN pio pkg install
RUN echo "All packages preinstalled in this cache layer"

RUN pio pkg install -g -t "tool-esptoolpy@1.40501.0"
RUN pio pkg install -g -t "tool-cmake@3.16.4"
RUN pio pkg install -g -t "tool-ninja@1.7.1"
RUN pio pkg install -g -t "tool-scons@4.40700.0"
RUN pio pkg install -g -l "googletest@1.12.1"
RUN echo "Extra packages preinstalled in this cache layer"

# Copy the platformio.ini file into the container at /app
RUN echo "You should now have a pre-downloaded image with all tools and packages installed"




CMD ["/bin/bash"]