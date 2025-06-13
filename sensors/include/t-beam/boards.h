/**
 * @file      boards.h
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2024  ShenZhen XinYuan Electronic Technology Co., Ltd
 * @date      2024-04-25
 * @last-update 2024-08-07
 */

#pragma once

#include "utilities.h"

#if defined(ARDUINO_ARCH_ESP32)
#include <FS.h>
#include <WiFi.h>
#endif

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <XPowersLib.h>
#include <esp_mac.h>
#include <webConfigurer.h>

#ifndef OLED_WIRE_PORT
#define OLED_WIRE_PORT Wire
#endif

#ifndef PMU_WIRE_PORT
#define PMU_WIRE_PORT Wire
#endif

#ifndef DISPLAY_ADDR
#define DISPLAY_ADDR 0x3C
#endif

#ifndef LORA_FREQ_CONFIG
#define LORA_FREQ_CONFIG 915.0
#endif

enum {
  POWERMANAGE_ONLINE = _BV(0),
  DISPLAY_ONLINE = _BV(1),
  RADIO_ONLINE = _BV(2),
  GPS_ONLINE = _BV(3),
  PSRAM_ONLINE = _BV(4),
  SDCARD_ONLINE = _BV(5),
  AXDL345_ONLINE = _BV(6),
  BME280_ONLINE = _BV(7),
  BMP280_ONLINE = _BV(8),
  BME680_ONLINE = _BV(9),
  QMC6310_ONLINE = _BV(10),
  QMI8658_ONLINE = _BV(11),
  PCF8563_ONLINE = _BV(12),
  OSC32768_ONLINE = _BV(13),
};

#define ENABLE_BLE  // Enable ble function

typedef struct {
  String chipModel;
  float psramSize;
  uint8_t chipModelRev;
  uint8_t chipFreq;
  uint8_t flashSize;
  uint8_t flashSpeed;
} DevInfo_t;

void setupBoards(WebConfigurer &conf, bool disable_u8g2 = false);

bool beginPower();

void printResult(bool radio_online);

void flashLed();

void scanDevices(TwoWire *w);

bool beginGPS();

bool recoveryGPS();

void loopPMU(void (*pressed_cb)(void));

void scanWiFi();

#ifdef HAS_PMU
extern XPowersLibInterface *PMU;
extern bool pmuInterrupt;
#endif

#if defined(ARDUINO_ARCH_ESP32)

#define SerialGPS Serial1
#elif defined(ARDUINO_ARCH_STM32)
extern HardwareSerial SerialGPS;
#endif

float getTempForNTC();

void setupBLE();

extern uint32_t deviceOnline;
