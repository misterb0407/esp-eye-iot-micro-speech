#ifndef ESP32_LOG_H_
#define ESP32_LOG_H_

// Library include
#include <stdio.h>

#define log(fmt, ...)   printf(fmt, ##__VA_ARGS__)

#endif