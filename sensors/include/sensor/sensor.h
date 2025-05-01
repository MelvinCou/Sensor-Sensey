#pragma once

#include <data.pb.h>
#include <stddef.h>

// clang-format off
enum class CValueType : unsigned char {
  INT,
  FLOAT
};
// clang-format on

/**
 * @brief Value to send to sensor.community
 */
struct RawValue {
  // Type of the value
  ValueType key;

  // C type of the value
  CValueType type;

  // Value that was detected
  union Value {
    int as_int;
    float as_float;
  } value;
};

/**
 * @brief An abstract sensor
 */
class Sensor {
 public:
  virtual ~Sensor() = default;
  /**
   * @brief Sense data
   */
  virtual void sense() = 0;
  /**
   * @brief Get values. must be called after sense().
   * @see sense
   */
  const RawValue* getValues() const { return m_values; };
  /**
   * @brief Get number of values.
   * @see getValues
   */
  const size_t& getValuesCount() const { return m_valuesCount; }

 protected:
  size_t m_valuesCount;
  RawValue* m_values;
};
