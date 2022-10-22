#pragma once

#include <ETH.h>

// Ethernet settings
#define ETH_CLK_MODE    ETH_CLOCK_GPIO16_OUT
#define ETH_POWER_PIN   5
#define ETH_TYPE        ETH_PHY_LAN8720
#define ETH_ADDR        0
#define ETH_MDC_PIN     23
#define ETH_MDIO_PIN    18

// MQTT Settings
#define MQTT_HOST IPAddress(192, 168, 0, 100)
#define MQTT_PORT 1883
#define MQTT_TOPIC_SEND "packetmonitor/pax"

// LoRa Settings
#define LORA_RXD 13
#define LORA_TXD 12
#define LORA_SERIAL Serial1
#define LORA_DEFAULT_AT_TIMEOUT_MILLIS 8000

// Get from LoRaWAN Network, e.g. TheThingsNetwork
uint8_t deveui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appeui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appkey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// PAX Settings
#define PAX_REPORT_INTERVAL_SEC       60
#define PAX_WIFI_COUNTRY              0

// LED Settings
#define ESP_LED_PIN 32
#define LED_COUNT   4
#define CHANNEL     0
