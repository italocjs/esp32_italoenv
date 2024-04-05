# How to setup a raspberry pi as a remote agent for platformio

This guide will show you how to setup a raspberry pi as a remote agent for platformio, it contains parts that are run under the local cpu and raspberry, Used with raspberry pi 3b+

## Step 1 - prepare the raspberry pi base image
- Downloaded ans install the raspberry image installer https://www.raspberrypi.com/software/  (raspberryos)
- run the raspberry image installer, it is recommended to click on "edit settings" and fill in your wireless settings, timezone and keyboard, under services ENABLE SSH!
- flash the image to the SDCARD
- turn OFF the raspberry, place the SDCARD into it and turn it on, 
- the raspberry will turn on and off a few times while doing setup. you can see the GUI if you use HDMI (not required)
- After the system stabilizes, you can login into SSH (or over hdmi use the terminal) to install the required tools.

## Step 2 - install platformio on raspberry pi
To install platformio, run these commands in your RASPBERRY TERMINAL

```bash
sudo apt update
sudo apt upgrade -y
sudo apt install python3-pip libffi-dev libssl-dev
sudo pip3 install platformio
pio remote agent
sudo restart
```

- THIS IS IMPORTANT, follow this guide and reboot (sudo reboot) at end  >>>> https://docs.platformio.org/en/latest/core/installation/udev-rules.html


## Step 3 - Authenticate the remote agent
- Login on the raspberry pi terminal using the following command ``` pio account login```
- obtain an Personal Authentication token by calling the command ```pio account token```
- Now using ```sudo nano /etc/systemd/system/pio-remote.service```, lets write a new file, dont forget to replace the key: 
    ```bash
    [Unit]
    Description=pio remote agent
    Requires=network-online.target
    After=network-online.target

    [Service]
    Type=simple
    User=pi
    Group=pi
    Environment="PLATFORMIO_AUTH_TOKEN=<PLACE_YOUR_KEY_HERE>"
    WorkingDirectory=/home/pi
    ExecStart=/usr/local/bin/platformio remote agent start
    Restart=always

    [Install]
    WantedBy=multi-user.target
    ```


## Step 4 - Test the service communication
- Check if the USB port is visible, run the following command
    ```bash
    pio device list #use "pio remote device list" on the remote end
    ```
    Expected output:

    ```bash
    root@ede35371b0ab:/workspaces/simovatrack_hw13_fw4xx# pio device list
    =================
    /dev/ttyUSB0
    ------------
    Hardware ID: USB VID:PID=1A86:7523 LOCATION=1-1.5
    Description: USB Serial

    /dev/ttyAMA0
    ------------
    Hardware ID: 3f201000.serial
    Description: ttyAMA0
    ```
- Start the remote service:
    ```bash
    pio remote agent start
    ```
    Tip if you want to share the device with other users, use the following command 
    ```
    pio remote agent start -s email@email.com
    ```
    Expected output:
    ```bash
    italo@raspberrypi:~ $ pio remote agent start
    2024-03-28 12:23:04 [info] Name: raspberrypi
    2024-03-28 12:23:04 [info] Connecting to PlatformIO Remote Development Cloud
    2024-03-28 12:23:05 [info] Successfully connected
    2024-03-28 12:23:05 [info] Authenticating
    2024-03-28 12:23:07 [info] Successfully authorized
    ```


## Step 5 - Build and or run code on this device
Here are some of the commands to build, run and flash the code, for more info check https://docs.platformio.org/en/latest/core/userguide/remote/index.html

- build native code locally, then run it ```pio run -e native -t exec```
- build esp32dev code locally ```pio run -e esp32dev```
- flash esp32dev code to the device ```pio remote --agent raspberrypi run -e esp32dev -t upload```
- flash esp32dev code to the device using a specific port ```pio remote --agent raspberrypi run -e esp32dev -t upload --device /dev/ttyUSB0```
- open the serial port monitor at a given speed, using some useful decoding tools  ```pio remote --agent raspberrypi device monitor --baud 115200 --filter esp32_exception_decoder --filter send_on_enter```
- open the serial port monitor at a given speed, using some useful decoding tools, using a specific port ```pio remote --agent raspberrypi device monitor --baud 115200 --filter esp32_exception_decoder --filter send_on_enter --port /dev/ttyUSB0```