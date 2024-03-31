/**
 * @file main.cpp
 * @brief Main entry point for the ESP32 application.
 * 
 * This file contains the main setup and loop functions for both an NATIVE and ESP32 application build.
 * It demonstrates conditional compilation for different environments
 * @version 0.1
 * @date 2024-03-28
 * @author Italo Soares (italocjs@live.com)
 * @copyright Copyright (c) 2024
 */

#if MY_PROJECT_VERSION==10
#warning "MY_PROJECT_VERSION==10"
#include "entrypoint_native.h"

int main()
{
	abstracted_main();
	return 0;
}
#endif

#if MY_PROJECT_VERSION==20
#warning "MY_PROJECT_VERSION==env_esp32dev"
#include "entrypoint_esp32dev.h"

void setup()
{
	abstracted_setup();
}

void loop()
{
	abstracted_loop();
}
#endif

