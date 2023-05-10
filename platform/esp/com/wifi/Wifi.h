#ifndef ESP_WIFI_H
#define ESP_WIFI_H

// Standard includes.
#include <cstdint>
#include <functional>

namespace platform {
namespace com {
namespace wifi {

class Wifi {
public:
    Wifi() = default;
    explicit Wifi(std::function<void(bool)> callback);
    ~Wifi() = default;

    // No copy allowed
    Wifi(const Wifi& other) = delete;
    Wifi& operator=(const Wifi& other) = delete;

    bool connect();

private:
    std::function<void(bool)> m_callback;
};

} // namespace wifi
} // namespace com
} // namespace platform

using platform::com::wifi::Wifi;

#endif // ESP_WIFI_H
