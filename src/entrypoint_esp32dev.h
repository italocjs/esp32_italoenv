#pragma once
#warning "Entrypoint ESP32 Dev"

#include <Arduino.h>
#include "esp_log.h"
#include <string>


String getResetReason(esp_reset_reason_t reason)
{
	switch (reason)
	{
	case ESP_RST_UNKNOWN:
		return "Unknown";
	case ESP_RST_POWERON:
		return "Power on";
	case ESP_RST_EXT:
		return "External";
	case ESP_RST_SW:
		return "Software";
	case ESP_RST_PANIC:
		return "Exception/panic";
	case ESP_RST_INT_WDT:
		return "Interrupt watchdog";
	case ESP_RST_TASK_WDT:
		return "Task watchdog";
	case ESP_RST_WDT:
		return "Other watchdog";
	case ESP_RST_DEEPSLEEP:
		return "Deep sleep";
	case ESP_RST_BROWNOUT:
		return "Brownout";
	case ESP_RST_SDIO:
		return "SDIO";
	default:
		return "Unknown";
	}
}

void print_device_information()
{
	/* Print chip information */
	esp_chip_info_t chip_info;
	uint32_t flash_size;
	esp_chip_info(&chip_info);
	unsigned major_rev = chip_info.revision / 100;
	unsigned minor_rev = chip_info.revision % 100;

	ESP_LOGI("INFO",
			 "This is %s chip with %d CPU core(s), "											 // Chip type and core count
			 "%s"																				 // WiFi capability
			 "%s"																				 // Bluetooth Classic capability
			 "%s"																				 // BLE capability
			 "%s, "																				 // IEEE 802.15.4 (Zigbee/Thread) capability
			 "silicon revision v%d.%d",															 // Silicon revision
			 CONFIG_IDF_TARGET,																	 // Chip type (e.g., ESP32)
			 chip_info.cores,																	 // Number of CPU cores
			 (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",						 // WiFi support
			 (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",								 // Bluetooth Classic support
			 (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",								 // BLE support
			 (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "", // IEEE 802.15.4 support
			 major_rev, minor_rev);																 // Major and minor silicon revision numbers

	if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
	{
		ESP_LOGE("INFO", "Get flash size failed");
	}
	else
	{
		ESP_LOGI("INFO", "%" PRIu32 "MB %s flash", flash_size / (uint32_t)(1024 * 1024),
				 (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
	}

	ESP_LOGI("INFO", "Minimum free heap size now: %" PRIu32 " bytes", esp_get_minimum_free_heap_size());

	ESP_LOGI("INFO", "CPU FREQ %d | SDK VERSION %s", getCpuFrequencyMhz(),
			 esp_get_idf_version());

	esp_reset_reason_t reset_reason = esp_reset_reason();
	String reset_cause = getResetReason(reset_reason);
	ESP_LOGI("INFO", "LAST RESET REASON: %s", reset_cause.c_str());
	ESP_LOGI("AUTHOR", "github/italocjs");
}

void abstracted_setup()
{
	Serial.begin(115200);
	Serial.println("Hello from ESP32 Dev setup"); //using arduino function to demonstrate accessibility to Arduino Framework
	ESP_LOGI("SETUP", "Hello from ESP32 Dev setup"); //using esp_log function to demonstrate accessibility to ESP-IDF
	print_device_information();
}

void abstracted_loop()
{
	Serial.println("Hello from ESP32 Dev loop");  //using arduino function to demonstrate accessibility to Arduino Framework
	ESP_LOGI("LOOP", "Hello from ESP32 Dev loop"); //using esp_log function to demonstrate accessibility to ESP-IDF
	delay(1000);
}

