#pragma once

#include <data.pb.h>

#include <better_enums.hpp>

// clang-format off
BETTER_ENUM(
  ValueTypeStr,
  unsigned char,

  vo_raw = ValueType::vo_raw,
  voltage = ValueType::voltage,
  dust_density = ValueType::dust_density,

  temperature = ValueType::temperature,
  pressure = ValueType::pressure,
  altitude = ValueType::altitude
);
// clang-format on