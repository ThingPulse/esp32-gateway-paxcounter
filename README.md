![Master Build](https://github.com/ThingPulse/esp32-gateway-paxcounter/actions/workflows/main.yaml/badge.svg)

# ThingPulse ESPGateway Ethernet PAX counter

The ThingPulse ESPGateway Ethernet is a versatile device that comes with one ESP32-WROVER-IB module, 
a CH9102F Serial-To-USB chip and the LAN8720 chip for Ethernet communication. The ESP32 can display its
status by controlling four WS2812B RGB Leds at the front of the device. 

The ESPGateway Ethernet is available for purchase at [ThingPulse ESPGateway Ethernet](https://thingpulse.com/product/espgateway-ethernet-esp32-wifi-ble-gateway-with-rj45-ethernet-connector/)

![Gateway](https://thingpulse.com/wp-content/uploads/2021/11/GatewayWithAntenna.jpg)

## The Project

This project shows how the ESPGateway Ethernet can be used to count WiFi and BLE
devices to meter passenger flows in realtime. To count the devices it uses the 
libpax library which is the core of the 
[ESP32-Paxcounter](https://github.com/cyberman54/ESP32-Paxcounter) project.

![Pax Counter Chart in Grafana](https://thingpulse.com/wp-content/uploads/2021/11/PaxCounter-Grafana.png)

The measured data can be transmitted for reporting by one of two backhaul channels:

### Ethernet

The ThingPulse ESPGateway Ethernet has a LAN8720 chip to let the ESP32 communicate
over an RJ45 ethnernet cable with a 10/100 networking device. The code in this repository
shows how to publish the measurements over ethernet and MQTT to an MQTT broker. From there
the data can be stored and visualized. E.g. by using Node-Red, Influx and Grafana.

### LoRaWAN with WIO-E5

The ThingPulse ESPGateway Ethernet also features a four pin digital grove connector. By attaching
a [Seeedstudio Grove - Wio-E5 (STM32WLE5JC), for Long Range Application](https://www.seeedstudio.com/Grove-LoRa-E5-STM32WLE5JC-p-4867.html)
the gateway can use LoRaWAN as backhaul and transmit the measured data to networks like
[The Things Network (TTN)](https://www.thethingsnetwork.org/). This project uses a slightly adapted
version of the Disk91_LoRaE5 library to communicate over serial lines with the LoRa-E5 module

![Seeedstudio Grove - Wio-E5](https://thingpulse.com/wp-content/uploads/2021/11/WIO-E5.jpeg)

The PAX counter measurements are transmitted in 6 bytes. The following formatter can be used to decode
the bytes into a json structure at the TTN console:

```JavaScript
function decodeUplink(input) {
  return {
    data: {
      pax: (input.bytes[0] << 8) + input.bytes[1],
      wifi_count: (input.bytes[2] << 8) + input.bytes[3],
      ble_count: (input.bytes[4] << 8) + input.bytes[5],
    },
    warnings: [],
    errors: []
  };
}
```

The device also needs to know its deveui, appeui and appkey to connect to a LoRaWAN network.
These values can be set in the settings.h file:

```JavaScript
uint8_t deveui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appeui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appkey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
```




