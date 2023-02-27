// Standard includes.
#include <cassert>

// Library includes.
#include "driver/gpio.h"

// Project includes.
#include "GPIO.h"

void GPIO::setOutDirection(uint32_t gpio_num) {
    (void)gpio_set_direction(static_cast<gpio_num_t >(gpio_num), GPIO_MODE_OUTPUT);
}

void GPIO::set(uint32_t gpio_num) {
    (void)gpio_set_level(static_cast<gpio_num_t >(gpio_num), 1U);
}

void GPIO::clear(uint32_t gpio_num) {
    (void)gpio_set_level(static_cast<gpio_num_t >(gpio_num), 0U);
}
