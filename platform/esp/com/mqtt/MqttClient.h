#ifndef MQTT_CLIENT_WRAPPER_H
#define MQTT_CLIENT_WRAPPER_H

// Standard includes.
#include <cstdint>
#include <functional>

namespace platform {
namespace com {
namespace mqtt {

class MqttClient {
public:
    MqttClient() = default;
    explicit MqttClient(std::function<void(bool)> callback);
    ~MqttClient() = default;

    // No copy allowed
    MqttClient(const MqttClient& other) = delete;
    MqttClient& operator=(const MqttClient& other) = delete;

    bool connect();
    void subscribe(const char* topic);
    void unsubscribe(const char* topic);
    void publish(const char* topic, const char* data);

private:
    std::function<void(bool)> m_callback;
};

} // namespace mqtt
} // namespace com
} // namespace platform

using platform::com::mqtt::MqttClient;

#endif // MQTT_CLIENT_WRAPPER_H
