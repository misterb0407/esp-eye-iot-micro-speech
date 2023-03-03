#ifndef GPIO_WRAPPER_H
#define GPIO_WRAPPER_H

// Standard includes.
#include <cstdint>

namespace platform {
namespace peripheral {
namespace gpio {

class GPIO {
public:
    GPIO() = delete;
    ~GPIO() = default;
    // No copy allowed
    GPIO(const GPIO& other) = delete;
    GPIO& operator=(const GPIO& other) = delete;

    static void setOutDirection(uint32_t gpio_num);
    static void set(uint32_t gpio_num);
    static void clear(uint32_t gpio_num);
};

} // namespace platform
} // namespace peripheral
} // namespace gpio

using platform::peripheral::gpio::GPIO;

#endif // GPIO_WRAPPER_H