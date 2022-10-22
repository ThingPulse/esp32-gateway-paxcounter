#pragma once

#include <Arduino.h>
#include "disk91_LoRaE5.h"
#include "settings.h"


Disk91_LoRaE5 lorae5((uint16_t)LORA_DEFAULT_AT_TIMEOUT_MILLIS, &Serial);



void initLora() {

  // init the library, search the LORAE5 over the different WIO port available
  Serial1.begin(9600, SERIAL_8N1, LORA_RXD, LORA_TXD, false);
  if ( ! lorae5.begin(&Serial1) ) {
    Serial.println("LoRa E5 Init Failed");
    return;
  } else {
    Serial.println("LoRa E5 Init succeeded");
  }

  // Setup the LoRaWan Credentials
  if ( ! lorae5.setup(
          DSKLORAE5_ZONE_EU868,     // LoRaWan Radio Zone EU868 here
          deveui,
          appeui,
          appkey
       ) ){
    Serial.println("LoRa E5 Setup Failed");  
  } else {
    Serial.println("LoRa E5 Setup succeeded");  
  }

}

void sendLoraMessage(uint8_t paxCount, uint8_t wifiCount, uint8_t bleCount) {
    printf("pax: %d; %d; %d;\n", paxCount, wifiCount, bleCount);
    uint8_t data[] = { 0x00, paxCount, 0x00, wifiCount, 0x00, bleCount }; 
  
    bool result = lorae5.send_sync(
        1,              // LoRaWan Port
        data,           // data array
        sizeof(data),   // size of the data
        false,          // we are not expecting a ack
        7,              // Spread Factor
        14              // Tx Power in dBm
       );

    if (result) {
      Serial.println("Uplink done");
      if ( lorae5.isDownlinkReceived() ) {
        Serial.println("A downlink has been received");
        if ( lorae5.isDownlinkPending() ) {
          Serial.println("More downlink are pending");
        }
      }
    } else {
        Serial.println("Sending message failed...");
    }

}