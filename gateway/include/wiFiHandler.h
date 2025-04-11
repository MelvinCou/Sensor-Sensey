#include "WiFi.h"
#pragma once

/**
 * @brief Wifi Connection
 */
void wiFiConnection();

/**
 * @brief Try to connect on the WiFi
 */
void connectedToAp(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo);

/**
 * @brief Call when a deconnection occurs and try a new connection
 */
void disconnectedFromAp(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo);
