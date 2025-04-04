#ifndef LOGGER_HPP
#define LOGGER_HPP

// clang-format off

#define LOG_LEVEL_NONE (0)
#define LOG_LEVEL_ERROR (1)
#define LOG_LEVEL_WARN (2)
#define LOG_LEVEL_INFO (3)
#define LOG_LEVEL_DEBUG (4)
#define LOG_LEVEL_TRACE (5)

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif // !defined(LOG_LEVEL)

#define LOG_PRINTF(format, ...) Serial.printf(format, ##__VA_ARGS__)

#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(format, ...) LOG_PRINTF("[E] " format, ##__VA_ARGS__)
#else
#define LOG_ERROR(format, ...) do {} while(0) 
#endif // LOG_LEVEL >= LOG_LEVEL_ERROR

#if LOG_LEVEL >= LOG_LEVEL_WARN
#define LOG_WARN(format, ...) LOG_PRINTF("[W] " format, ##__VA_ARGS__)
#else
#define LOG_WARN(format, ...) do {} while(0)
#endif // LOG_LEVEL >= LOG_LEVEL_WARN

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(format, ...) LOG_PRINTF("[I] " format, ##__VA_ARGS__)
#else
#define LOG_INFO(format, ...) do {} while(0)
#endif // LOG_LEVEL >= LOG_LEVEL_INFO

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOG_DEBUG(format, ...) LOG_PRINTF("[D] " format, ##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...) do {} while(0)
#endif // LOG_LEVEL >= LOG_LEVEL_DEBUG

#if LOG_LEVEL >= LOG_LEVEL_TRACE
#define LOG_TRACE(format, ...) LOG_PRINTF("[T] " format, ##__VA_ARGS__)
#else
#define LOG_TRACE(format, ...) do {} while(0)
#endif // LOG_LEVEL >= LOG_LEVEL_TRACE

// clang-format on

#endif  // !defined(LOGGER_HPP)