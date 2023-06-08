// Library includes
#include "mqtt_client.h"

// Platform includes.
#include "log/Log.h"

// Project includes.
#include "Cloud.h"
#include "SysResMgmtSingleton.h"

using namespace app;

namespace {
// callback when platform feedback about the wifi connection status
void wifi_status_callback(bool isConnected) {
    auto event = (isConnected) ? EventId::WifiConnected : EventId::WifiDisconnected;
    auto control = SysResMgmtSingleton::getInstance().getControl();
    control->set({event, nullptr, 0});
}

// callback when platform feedback about the mqtt connection status
void mqtt_status_callback(bool isConnected) {
    auto event = (isConnected) ? EventId::CloudConnected : EventId::CloudDisconnected;
    auto control = SysResMgmtSingleton::getInstance().getControl();
    control->set({event, nullptr, 0});
}
}

Cloud::Cloud(std::shared_ptr<MsgInbox> inbox, std::shared_ptr<Control> control):
    m_inbox(inbox),
    m_control(control),
    m_wifi(wifi_status_callback),
    m_mqtt(mqtt_status_callback)
{
    // Subscribe to event(s) of interest.
    m_control->subscribe(EventId::WifiConnected, m_inbox);
    m_control->subscribe(EventId::WifiDisconnected, m_inbox);
    m_control->subscribe(EventId::CloudConnected, m_inbox);
    m_control->subscribe(EventId::CloudDisconnected, m_inbox);
}

void Cloud::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};
    m_wifi.connect();

    for (;;) {
        m_inbox->get(&msg);
        handle(msg);
    }
}

void Cloud::handle(const app::Msg& msg) {
    switch(msg.ev) {
    case EventId::WifiConnected:
        connectToCloud();
        break;
    case EventId::WifiDisconnected:
        // TODO: error handling
        break;
    case EventId::CloudConnected:
        m_mqtt.publish("/topic/startup", "hello master Babang/Sunil, how I may serve you?");
        m_control->set({EventId::DataPublishedToCloud, nullptr, 0U});
        break;
    case EventId::CloudDisconnected:
        // TODO: error handling.
        break;
    default:
        break;
    }
}

void Cloud::connectToCloud() {
    m_mqtt.connect();
}

