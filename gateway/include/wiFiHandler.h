#include "WiFi.h"
#pragma once

/**
 * @brief Wifi Connection
 */
void wiFiConnection();

/**
 * @brief Try to connect on the WiFi
 */
void connectedToWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo);

/**
 * @brief After a successful connection, get ip
 */
void gotIpFromWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo);

/**
 * @brief Call when a deconnection occurs and try a new connection
 */
void disconnectedFromWiFi(WiFiEvent_t wifiEvent, WiFiEventInfo_t wifiInfo);

/**
 * @brief Function used for request sensor community through http
 */
void requestSensorCommunity(String xSensor, String xPin);
