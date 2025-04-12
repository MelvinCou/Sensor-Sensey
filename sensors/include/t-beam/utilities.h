/**
 * @file      utilities.h
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2024  ShenZhen XinYuan Electronic Technology Co., Ltd
 * @date      2024-05-12
 * @last-update 2024-08-07
 */
#pragma once

// Support board list , Macro definition below, select the board definition to be used

// #define T3_V1_3_SX1276
// #define T3_V1_3_SX1278

// #define T3_V1_6_SX1276
// #define T3_V1_6_SX1278

// #define T3_V1_6_SX1276_TCXO
// #define T3_V3_0_SX1276_TCXO

// #define T_BEAM_SX1262
#define T_BEAM_SX1276
// #define T_BEAM_SX1278
// #define T_BEAM_LR1121

// #define T_BEAM_S3_SUPREME_SX1262
// #define T_BEAM_S3_SUPREME_LR1121

// #define T3_S3_V1_2_SX1262
// #define T3_S3_V1_2_SX1276
// #define T3_S3_V1_2_SX1278
// #define T3_S3_V1_2_SX1280
// #define T3_S3_V1_2_SX1280_PA
// #define T3_S3_V1_2_LR1121

// #define T_MOTION

// #define T3_C6

// #define T_BEAM_S3_BPF

// LoRa configuration
#define CONFIG_RADIO_FREQ 868E6
#define CONFIG_RADIO_BW 125.0

// Sensor community configuration
#define SENSOR_COM_ID "esp32-1234"
// TODO : Change PIN number according to sensor community registered pin
#define DUST_SENSOR_COM_PIN 8
#define DUST_SENSOR_COM_TYPE "Dust"
#define PRESSURE_SENSOR_COM_PIN 9
#define PRESSURE_SENSOR_COM_TYPE "Pressure"

#define UNUSED_PIN (0)

#if defined(T_BEAM_SX1262) || defined(T_BEAM_SX1276) || defined(T_BEAM_SX1278) || defined(T_BEAM_LR1121)

#if defined(T_BEAM_SX1262)
#ifndef USING_SX1262
#define USING_SX1262
#endif
#elif defined(T_BEAM_SX1276)
#ifndef USING_SX1276
#define USING_SX1276
#endif
#elif defined(T_BEAM_SX1278)
#ifndef USING_SX1278
#define USING_SX1278
#endif
#elif defined(T_BEAM_LR1121)
#ifndef USING_LR1121
#define USING_LR1121
#endif
#endif  // T_BEAM_SX1262

#define GPS_RX_PIN 34
#define GPS_TX_PIN 12
#define BUTTON_PIN 38
#define BUTTON_PIN_MASK GPIO_SEL_38
#define I2C_SDA 21
#define I2C_SCL 22
#define PMU_IRQ 35

#define RADIO_SCLK_PIN 5
#define RADIO_MISO_PIN 19
#define RADIO_MOSI_PIN 27
#define RADIO_CS_PIN 18
#define RADIO_DIO0_PIN 26
#define RADIO_RST_PIN 23
#define RADIO_DIO1_PIN 33
// SX1276/78
#define RADIO_DIO2_PIN 32
// SX1262
#define RADIO_BUSY_PIN 32

// LR1121 Only
#define RADIO_DIO9_PIN 33

// DUST PINS
#define DUST_AOUT_PIN 13
#define DUST_ILED_PIN 14

// VCC References
#define VCC_3V 3.3
#define VCC_5V 5

#define BOARD_LED 4
#define LED_ON LOW
#define LED_OFF HIGH

#define BUTTON_PIN 38

#define GPS_BAUD_RATE 9600
#define HAS_GPS
#define HAS_PMU

#define BOARD_VARIANT_NAME "T-Beam"
#define DISPLAY_MODEL_SSD_LIB SSD1306Wire

#elif defined(T3_V1_3_SX1276) || defined(T3_V1_3_SX1278)

#if defined(T3_V1_3_SX1276)

#ifndef USING_SX1276
#define USING_SX1276
#endif

#elif defined(T3_V1_3_SX1278)

#ifndef USING_SX1278
#define USING_SX1278
#endif

#endif  // T3_V1_3_SX1276

#define I2C_SDA 21
#define I2C_SCL 22
#define OLED_RST UNUSED_PIN

#define RADIO_SCLK_PIN 5
#define RADIO_MISO_PIN 19
#define RADIO_MOSI_PIN 27
#define RADIO_CS_PIN 18
#define RADIO_DIO0_PIN 26
#define RADIO_RST_PIN 14
#define RADIO_DIO1_PIN 33

// SX1276/78
#define RADIO_DIO2_PIN 32
// SX1262
#define RADIO_BUSY_PIN 32

#define ADC_PIN 35
#define HAS_DISPLAY
#define BOARD_VARIANT_NAME "T3 V1.3"

#elif defined(T3_V1_6_SX1276) || defined(T3_V1_6_SX1278)

#if defined(T3_V1_6_SX1276)
#ifndef USING_SX1276
#define USING_SX1276
#endif
#elif defined(T3_V1_6_SX1278)
#ifndef USING_SX1278
#define USING_SX1278
#endif
#endif  // T3_V1_6_SX1276

#define I2C_SDA 21
#define I2C_SCL 22
#define OLED_RST UNUSED_PIN

#define RADIO_SCLK_PIN 5
#define RADIO_MISO_PIN 19
#define RADIO_MOSI_PIN 27
#define RADIO_CS_PIN 18
#define RADIO_DIO0_PIN 26
#define RADIO_RST_PIN 23
#define RADIO_DIO1_PIN 33
// SX1276/78
#define RADIO_DIO2_PIN 32
// SX1262
#define RADIO_BUSY_PIN 32

#define SDCARD_MOSI 15
#define SDCARD_MISO 2
#define SDCARD_SCLK 14
#define SDCARD_CS 13

#define BOARD_LED 25
#define LED_ON HIGH

#define ADC_PIN 35

#define HAS_SDCARD
#define HAS_DISPLAY

#define BOARD_VARIANT_NAME "T3 V1.6"

#elif defined(T3_V1_6_SX1276_TCXO)

#ifndef USING_SX1276
#define USING_SX1276
#endif

#define I2C_SDA 21
#define I2C_SCL 22
#define OLED_RST UNUSED_PIN

#define RADIO_SCLK_PIN 5
#define RADIO_MISO_PIN 19
#define RADIO_MOSI_PIN 27
#define RADIO_CS_PIN 18
#define RADIO_DIO0_PIN 26
#define RADIO_RST_PIN 23
#define RADIO_DIO1_PIN -1  // 33
/*
 * In the T3 V1.6.1 TCXO version, Radio DIO1 is connected to Radio’s
 * internal temperature-compensated crystal oscillator enable
 * */
// TCXO pin must be set to HIGH before enabling Radio
#define RADIO_TCXO_ENABLE 33
#define RADIO_BUSY_PIN 32

#define SDCARD_MOSI 15
#define SDCARD_MISO 2
#define SDCARD_SCLK 14
#define SDCARD_CS 13

#define BOARD_LED 25
#define LED_ON HIGH

#define ADC_PIN 35

#define HAS_SDCARD
#define HAS_DISPLAY

#define BOARD_VARIANT_NAME "T3 V1.6 TCXO"

#elif defined(T3_V3_0)

#define I2C_SDA 21
#define I2C_SCL 22
#define OLED_RST 4

#define RADIO_SCLK_PIN 5
#define RADIO_MISO_PIN 19
#define RADIO_MOSI_PIN 27
#define RADIO_CS_PIN 18
#define RADIO_RST_PIN 23

// TCXO pin must be set to HIGH before enabling Radio
#define RADIO_TCXO_ENABLE 12  // only sx1276 tcxo version
#define RADIO_BUSY_PIN 32

#if defined(USING_SX1262)

#define RADIO_DIO1_PIN 26
#define RADIO_BUSY_PIN 32

#elif defined(USING_SX1276) || defined(USING_SX1278)
//! SX1276/78 module only

#define RADIO_DIO0_PIN 26
#define RADIO_DIO1_PIN 32

#elif defined(USING_LR1121)

#define RADIO_DIO9_PIN 26  // LR1121 DIO9
#define RADIO_BUSY_PIN 32  // LR1121 BUSY

#endif

#define SDCARD_MOSI 15
#define SDCARD_MISO 2
#define SDCARD_SCLK 14
#define SDCARD_CS 13

#define BOARD_LED 25
#define LED_ON HIGH

#define ADC_PIN 35

#define HAS_SDCARD
#define HAS_DISPLAY

#define BOARD_VARIANT_NAME "T3 V3.0"

#define BUTTON_PIN 0
#define ADC_PIN 35

#elif defined(T3_S3_V1_2_SX1262) || defined(ARDUINO_LILYGO_T3S3_SX1262) || defined(T3_S3_V1_2_SX1276) ||        \
    defined(ARDUINO_LILYGO_T3S3_SX1276) || defined(T3_S3_V1_2_SX1278) || defined(ARDUINO_LILYGO_T3S3_SX1278) || \
    defined(T3_S3_V1_2_SX1280) || defined(ARDUINO_LILYGO_T3S3_SX1280) || defined(T3_S3_V1_2_SX1280_PA) ||       \
    defined(ARDUINO_LILYGO_T3S3_SX1280PA) || defined(T3_S3_V1_2_LR1121) || defined(ARDUINO_LILYGO_T3S3_LR1121)

#if defined(T3_S3_V1_2_SX1262) || defined(ARDUINO_LILYGO_T3S3_SX1262)
#ifndef USING_SX1262
#define USING_SX1262
#endif
#elif defined(T3_S3_V1_2_SX1276) || defined(ARDUINO_LILYGO_T3S3_SX1276)
#ifndef USING_SX1276
#define USING_SX1276
#endif
#elif defined(T3_S3_V1_2_SX1278) || defined(ARDUINO_LILYGO_T3S3_SX1278)
#ifndef USING_SX1278
#define USING_SX1278
#endif
#elif defined(T3_S3_V1_2_SX1280) || defined(ARDUINO_LILYGO_T3S3_SX1280)
#ifndef USING_SX1280
#define USING_SX1280
#endif
#elif defined(T3_S3_V1_2_SX1280_PA) || defined(ARDUINO_LILYGO_T3S3_SX1280PA)
#ifndef USING_SX1280PA
#define USING_SX1280PA
#endif
#elif defined(T3_S3_V1_2_LR1121) || defined(ARDUINO_LILYGO_T3S3_LR1121)
#ifndef USING_LR1121
#define USING_LR1121
#endif

#endif  // T3_S3_V1_2_SX1262

// REMOVING THIS ELSE IT SEEMS TO OVERRIDE OTHER VALUES DEFINED FOR i2C_SDA AND I2C_SCL
// #define I2C_SDA 18
// #define I2C_SCL 17
#define OLED_RST UNUSED_PIN

#define RADIO_SCLK_PIN 5
#define RADIO_MISO_PIN 3
#define RADIO_MOSI_PIN 6
#define RADIO_CS_PIN 7

#define SDCARD_MOSI 11
#define SDCARD_MISO 2
#define SDCARD_SCLK 14
#define SDCARD_CS 13

#define BOARD_LED 37
#define LED_ON HIGH

#define BUTTON_PIN 0
#define ADC_PIN 1

#define RADIO_RST_PIN 8

#if defined(USING_SX1262)

#define RADIO_DIO1_PIN 33
#define RADIO_BUSY_PIN 34

#elif defined(USING_SX1276) || defined(USING_SX1278)
//! SX1276/78 module only
#define RADIO_BUSY_PIN 33  // DIO1

#define RADIO_DIO0_PIN 9
#define RADIO_DIO1_PIN 33
#define RADIO_DIO2_PIN 34
#define RADIO_DIO3_PIN 21
#define RADIO_DIO4_PIN 10
#define RADIO_DIO5_PIN 36

#elif defined(USING_SX1280)

#define RADIO_DIO1_PIN 9   // SX1280 DIO1 = IO9
#define RADIO_BUSY_PIN 36  // SX1280 BUSY = IO36

#elif defined(USING_SX1280PA)

#define RADIO_DIO1_PIN 9   // SX1280 DIO1 = IO9
#define RADIO_BUSY_PIN 36  // SX1280 BUSY = IO36
#define RADIO_RX_PIN 21
#define RADIO_TX_PIN 10

#elif defined(USING_LR1121)

#define RADIO_DIO9_PIN 36  // LR1121 DIO9  = IO36
#define RADIO_BUSY_PIN 34  // LR1121 BUSY  = IO34

#endif

#define BUTTON_PIN 0

#define HAS_SDCARD
#define HAS_DISPLAY

#define BOARD_VARIANT_NAME "T3-S3-V1.X"

#else
#error "When using it for the first time, please define the board model in <utilities.h>"
#endif
