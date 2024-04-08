# How to connect to an platformio remote agent (raspberry)

This guide will show you use an raspberry pi (or any other device) as a remote agent for platformio.

## Step 1 - Preparing platformio:
- Make sure you have plaftormio installed in your local machine
- Open terminal and login with your platformio account credentials
    ```bash
    pio account login
    ```
- Check if your remote agent is available using
    ```bash
    pio remote agent list
    ```

## Step 2 - build your sources and tests and run them
Here are some of the commands to build, run and flash the code, for more info check https://docs.platformio.org/en/latest/core/userguide/remote/index.html

- build native code locally, then run it ```pio run -e native -t exec```
- build esp32dev code locally ```pio run -e esp32dev```
- flash esp32dev code to the device ```pio remote --agent raspberrypi run -e esp32dev -t upload```
- flash esp32dev code to the device using a specific port ```pio remote --agent raspberrypi run -e esp32dev -t upload --upload-port /dev/ttyUSB0```
- open the serial port monitor at a given speed, using some useful decoding tools  ```pio remote --agent raspberrypi device monitor --baud 115200 --filter esp32_exception_decoder --filter send_on_enter```
- open the serial port monitor at a given speed, using some useful decoding tools, using a specific port ```pio remote --agent raspberrypi device monitor --baud 115200 --filter esp32_exception_decoder --filter send_on_enter --port /dev/ttyUSB0```


### Sample of working output
- pio run -e native -t exec
    ```bash
    root@ede35371b0ab:/workspaces/simovatrack_hw13_fw4xx# pio run -e native -t exec
    Processing native (platform: native)
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Verbose mode can be enabled via `-v, --verbose` option
    LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
    LDF Modes: Finder ~ deep+, Compatibility ~ soft
    Found 10 compatible libraries
    Scanning dependencies...
    Dependency Graph
    |-- googletest @ 1.12.1
    Building in release mode
    Executing .pio/build/native/program
    Hello World from PlatformIO!
    ===================================================================================== [SUCCESS] Took 24.52 seconds =====================================================================================

    Environment    Status    Duration
    -------------  --------  ------------
    native         SUCCESS   00:00:24.519
    ====================================================================================== 1 succeeded in 00:00:24.519 ======================================================================================
    root@ede35371b0ab:/workspaces/simovatrack_hw13_fw4xx# 
    ```

- pio run -e esp32dev
    ```bash
    root@ede35371b0ab:/workspaces/simovatrack_hw13_fw4xx# pio run -e esp32dev
    Processing esp32dev (platform: espressif32; board: simovatrack130; framework: arduino, espidf)
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Verbose mode can be enabled via `-v, --verbose` option
    CONFIGURATION: https://docs.platformio.org/page/boards/espressif32/simovatrack130.html
    PLATFORM: Espressif 32 (6.5.0) > Espressif ESP32 Dev Module
    HARDWARE: ESP32 240MHz, 320KB RAM, 16MB Flash
    DEBUG: Current (cmsis-dap) External (cmsis-dap, esp-bridge, esp-prog, iot-bus-jtag, jlink, minimodule, olimex-arm-usb-ocd, olimex-arm-usb-ocd-h, olimex-arm-usb-tiny-h, olimex-jtag-tiny, tumpa)
    PACKAGES: 
    - framework-arduinoespressif32 @ 2.0.14+sha.54096e1 
    - framework-espidf @ 3.40406.240122 (4.4.6) 
    - tool-cmake @ 3.16.4 
    - tool-esptoolpy @ 1.40501.0 (4.5.1) 
    - tool-ninja @ 1.7.1 
    - toolchain-esp32ulp @ 1.23500.220830 (2.35.0) 
    - toolchain-xtensa-esp32 @ 8.4.0+2021r2-patch5
    Warning! Arduino framework as an ESP-IDF component doesn't handle the `variant` field! The default `esp32` variant will be used.
    Reading CMake configuration...
    LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
    LDF Modes: Finder ~ chain, Compatibility ~ soft
    Found 55 compatible libraries
    Scanning dependencies...
    Dependency Graph
    |-- googletest @ 1.12.1
    |-- core_lib
    |-- port_log
    |-- SmartoneC
    Building in release mode
    Retrieving maximum program size .pio/build/esp32dev/firmware.elf
    Checking size .pio/build/esp32dev/firmware.elf
    Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
    RAM:   [==        ]  21.1% (used 68992 bytes from 327680 bytes)
    Flash: [====      ]  38.0% (used 1594145 bytes from 4194304 bytes)
    ===================================================================================== [SUCCESS] Took 106.71 seconds =====================================================================================

    Environment    Status    Duration
    -------------  --------  ------------
    esp32dev       SUCCESS   00:01:46.710
    ====================================================================================== 1 succeeded in 00:01:46.710 ======================================================================================
    root@ede35371b0ab:/workspaces/simovatrack_hw13_fw4xx# 
    ```

- pio remote --agent raspberrypi run -e esp32dev -t upload
- pio remote --agent raspberrypi run -e esp32dev -t upload --upload-port /dev/ttyUSB0

    ```bash
    root@ede35371b0ab:/workspaces/simovatrack_hw13_fw4xx# pio run -e esp32dev
    Processing esp32dev (platform: espressif32; board: simovatrack130; framework: arduino, espidf)
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Verbose mode can be enabled via `-v, --verbose` option
    CONFIGURATION: https://docs.platformio.org/page/boards/espressif32/simovatrack130.html
    PLATFORM: Espressif 32 (6.5.0) > Espressif ESP32 Dev Module
    HARDWARE: ESP32 240MHz, 320KB RAM, 16MB Flash
    DEBUG: Current (cmsis-dap) External (cmsis-dap, esp-bridge, esp-prog, iot-bus-jtag, jlink, minimodule, olimex-arm-usb-ocd, olimex-arm-usb-ocd-h, olimex-arm-usb-tiny-h, olimex-jtag-tiny, tumpa)
    PACKAGES: 
    - framework-arduinoespressif32 @ 2.0.14+sha.54096e1 
    - framework-espidf @ 3.40406.240122 (4.4.6) 
    - tool-cmake @ 3.16.4 
    - tool-esptoolpy @ 1.40501.0 (4.5.1) 
    - tool-ninja @ 1.7.1 
    - toolchain-esp32ulp @ 1.23500.220830 (2.35.0) 
    - toolchain-xtensa-esp32 @ 8.4.0+2021r2-patch5
    Warning! Arduino framework as an ESP-IDF component doesn't handle the `variant` field! The default `esp32` variant will be used.
    Reading CMake configuration...
    LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
    LDF Modes: Finder ~ chain, Compatibility ~ soft
    Found 55 compatible libraries
    Scanning dependencies...
    Dependency Graph
    |-- googletest @ 1.12.1
    |-- core_lib
    |-- port_log
    |-- SmartoneC
    Building in release mode
    Retrieving maximum program size .pio/build/esp32dev/firmware.elf
    Checking size .pio/build/esp32dev/firmware.elf
    Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
    RAM:   [==        ]  21.1% (used 68992 bytes from 327680 bytes)
    Flash: [====      ]  38.0% (used 1594145 bytes from 4194304 bytes)
    ===================================================================================== [SUCCESS] Took 106.71 seconds =====================================================================================

    Environment    Status    Duration
    -------------  --------  ------------
    esp32dev       SUCCESS   00:01:46.710
    ====================================================================================== 1 succeeded in 00:01:46.710 ======================================================================================
    root@ede35371b0ab:/workspaces/simovatrack_hw13_fw4xx# 
    ```