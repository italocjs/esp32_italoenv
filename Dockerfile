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

RUN echo "apt updated, git installed, python installed, doxygen installed"

# Set the working directory in the container
WORKDIR /app
RUN echo "Working directory set to /app, we are at $(pwd), with user $(whoami), and these are the folder list $(ls -la)"

# Install platformio
RUN pip install platformio

# Copy the platformio.ini file into the container at /app
COPY platformio.ini /app/platformio.ini
COPY boards/ /app/boards/
RUN echo "Just copied platformio.ini and boards to /app, we are at $(pwd), with user $(whoami), and these are the folder list $(ls -la)"
RUN pio pkg install
RUN echo "will you wooooooooooooooork?"


# preinstall all project dependencies specified in platformio.ini


# # Add the script to check Python and PIO versions
# # COPY check_versions.sh /app/check_versions.sh
# RUN chmod +x ./check_versions.sh


CMD ["/bin/bash"]