# How to setup a raspberry pi as a remote agent for platformio

This guide will show you how to setup a raspberry pi as a remote agent for platformio, it contains parts that are run under the local cpu and raspberry, Used with raspberry pi 3b+

## Step 1 - prepare the raspberry pi base image
- Downloaded ans install the raspberry image installer https://www.raspberrypi.com/software/  (raspberryos)
- run the raspberry image installer, it is recommended to click on "edit settings" and fill in your wireless settings, timezone and keyboard, under services ENABLE SSH!
- flash the image to the SDCARD
- turn OFF the raspberry, place the SDCARD into it and turn it on, 
- the raspberry will turn on and off a few times while doing setup. you can see the GUI if you use HDMI
- After the system stabilizes in ~5 - 10min, you can login into SSH (or over hdmi use the terminal) to install the required tools,
    ```bash
    ssh pi@raspberrypi.local
    #ssh username@ip_address also works, e.g. ssh pi@192.168.1.100
    #default username is pi and password is raspberry, but you should change the default password as soon as possible
    ```

## Step 2 - Installing PIO Remote and udev rules on raspberry pi (or linux)
To install platformio, run these commands in your terminal/ssh

```bash
sudo apt update
sudo apt upgrade -y
sudo apt install python3-pip libffi-dev libssl-dev
sudo pip3 install platformio
pio remote agent
```

Linux users must install udev rules for PlatformIO supported boards/devices. The latest version of these rules can be found at [PlatformIO udev rules](https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules).

**Note:** Ensure that your board's PID and VID are listed in the rules. You can list connected devices and their PID/VID using the `pio device list` command.

To install the udev rules, execute the following command:

```bash
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
```

Restart “udev” management tool:

```bash
sudo service udev restart
# or
sudo udevadm control --reload-rules
sudo udevadm trigger
```

Ubuntu/Debian users may need to add their username to the "dialout" and "plugdev" groups if not operating as "root". This can be done with:

```bash
sudo usermod -a -G dialout $USER
sudo usermod -a -G plugdev $USER
```

**Note:** You will need to log out and then log back in (or reboot) for the user group changes to take effect.

After installing this file, physically unplug and reconnect your board to ensure the changes are applied.


## Step 3 - Authenticate the remote agent and create the autostart service
### Authenticate the remote agent
1. Open a terminal on the Raspberry Pi.
2. Login on the raspberry pi terminal using the following command ``` pio account login```
3. Obtain an Personal Authentication token by calling the command ```pio account token```
4. Create the service file using the following command

    ```bash
    sudo nano /etc/systemd/system/pio-remote.service
    ```

### Configuring the Service
Copy and paste the following content into the service file. Remember to replace `PLACE_YOUR_KEY_HERE` with your actual PlatformIO authentication token and adjust the `WorkingDirectory` and `ExecStart` parameters as needed. The `-s` option in `ExecStart` is used to share the device with another user via email, which is optional.

```bash
[Unit]
Description=PlatformIO Remote Agent
Requires=network-online.target
After=network-online.target

[Service]
Type=simple
Environment="PLATFORMIO_AUTH_TOKEN=PLACE_YOUR_KEY_HERE"
WorkingDirectory=/home/pi  # Adjust if necessary
ExecStart=/usr/local/bin/platformio remote agent start
#ExecStart=/usr/local/bin/platformio remote agent start -s sharing_with_someone_else@email.com
Restart=always
RestartSec=600  # Restart service after 10 minutes if it fails

[Install]
WantedBy=multi-user.target
```
Replace `sharing_with_someone_else@email.com` with the email of the user you want to share the device with. This approach simplifies device sharing among multiple developers without exposing the authentication token.

### Enabling the Service
After saving the file, enable the service to start on boot with the following command:

```bash
sudo systemctl enable pio-remote
```

Reboot the device to ensure the service starts on boot, if not, you can start the pio remote manually using ```pio remote agent start -s sharing_with_someone_else@email.com``` directly in your terminal and check for more information on what could have failed.


## Step 4 - Build and or run code on this remote device
Here are some of the commands to build, run and flash the code, for more info check https://docs.platformio.org/en/latest/core/userguide/remote/index.html

- build native code locally, then run it ```pio run -e native -t exec```
- build esp32dev code locally ```pio run -e esp32dev```
- flash esp32dev code to the device ```pio remote --agent raspberrypi run -e esp32dev -t upload```
- flash esp32dev code to the device using a specific port ```pio remote --agent raspberrypi run -e esp32dev -t upload --device /dev/ttyUSB0```
- open the serial port monitor at a given speed, using some useful decoding tools  ```pio remote --agent raspberrypi device monitor --baud 115200 --filter esp32_exception_decoder --filter send_on_enter```
- open the serial port monitor at a given speed, using some useful decoding tools, using a specific port ```pio remote --agent raspberrypi device monitor --baud 115200 --filter esp32_exception_decoder --filter send_on_enter --port /dev/ttyUSB0```




 