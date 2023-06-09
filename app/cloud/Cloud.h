#ifndef APP_CLOUD_H
#define APP_CLOUD_H

// Standard includes.
#include <memory>
#include <list>

// Project includes.
#include "Event.h"
#include "MsgInbox.h"
#include "control/Control.h"
#include "com/wifi/Wifi.h"
#include "com/mqtt/MqttClient.h"


// Platform includes.
#include "os/OSWrapper.h"

namespace app {
namespace cloud {

class Cloud {
public:
    Cloud() = delete;
    explicit Cloud(std::shared_ptr<MsgInbox> inbox, std::shared_ptr<Control> control);
    ~Cloud() = default;

    // No copy allowed
    Cloud(const Cloud& other) = delete;
    Cloud& operator=(const Cloud& other) = delete;

    void run();

private:
    // Private helper
    void handle(const app::Msg& msg);
    void connectToCloud();

    std::list<EventId> m_events_to_subscribe = {
        EventId::WifiConnected,
        EventId::WifiDisconnected,
        EventId::CloudConnected,
        EventId::CloudDisconnected,
    };

    std::shared_ptr<MsgInbox> m_inbox;
    std::shared_ptr<Control> m_control;
    Wifi m_wifi;
    MqttClient m_mqtt;
};

} // namespace app
} // namespace cloud

using app::cloud::Cloud;

#endif // APP_CLOUD_H
