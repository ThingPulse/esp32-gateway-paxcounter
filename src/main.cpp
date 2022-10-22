#include <Arduino.h>
#include <HTTPClient.h>
//#include "mqtt.h"
#include "pax.h"
#include "lora.h"
#include "led.h"

boolean isNewDataAvailable = false;

void process_count(void) {
  printf("pax: %d; %d; %d;\n", count_from_libpax.pax, count_from_libpax.wifi_count, count_from_libpax.ble_count);
  isNewDataAvailable = true;
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  //mqttInit();
  initStatusLeds();
  updateLed(0, CRGB::Red);
  updateLed(1, CRGB::Red);
  initLora();
  updateLed(0, CRGB::Green);
  paxInit();
  updateLed(1, CRGB::Green);
}

void loop() {
  if(isNewDataAvailable) {
    updateLed(0, CRGB::Blue);
    isNewDataAvailable = false;

    sendLoraMessage(count_from_libpax.pax, count_from_libpax.wifi_count, count_from_libpax.ble_count);
    updateLed(0, CRGB::Green);
  }

}