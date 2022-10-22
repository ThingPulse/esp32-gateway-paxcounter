#pragma once

#include <libpax_api.h>
#include <stdio.h>
#include "settings.h"

struct count_payload_t count_from_libpax;

void process_count(void);


void paxInit() {
  struct libpax_config_t configuration; 
  libpax_default_config(&configuration);
  configuration.blecounter = 1;
  configuration.blescantime = 0; // infinit
  configuration.wificounter = 1; 
  configuration.wifi_channel_map = WIFI_CHANNEL_ALL;
  configuration.wifi_channel_switch_interval = 50;
  configuration.wifi_rssi_threshold = -80;
  configuration.ble_rssi_threshold = -80;
  configuration.wifi_my_country = PAX_WIFI_COUNTRY;
  libpax_update_config(&configuration);

  // internal processing initialization
  libpax_counter_init(process_count, &count_from_libpax, PAX_REPORT_INTERVAL_SEC, 0); 
  libpax_counter_start();

}
