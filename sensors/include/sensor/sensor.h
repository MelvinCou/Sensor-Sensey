#pragma once

#include <stddef.h>

/**
 * @brief Value to send to sensor.community
 */
struct RawValue
{
    // Type of the value
    char key[18];
    // Value that was detected
    char value[11];
};

/**
 * @brief An abstract sensor
 */
class Sensor
{
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
    const RawValue* getValues() const {
        return m_values;
    };
    /**
     * @brief Get number of values.
     * @see getValues
     */
    const size_t& getValuesCount() const {
        return m_valuesCount;
    }
protected:
    size_t m_valuesCount;
    RawValue* m_values;
};
