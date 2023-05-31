// Library includes
#include "mqtt_client.h"

// Platform includes.
#include "log/Log.h"

// Project includes.
#include "Cloud.h"
#include "OSResourceSingleton.h"

using namespace app;

namespace {
// callback when platform feedback about the wifi connection status
void wifi_status_callback(bool isConnected) {
    OSResourceSingleton& resources = OSResourceSingleton::getInstance();
    using Id = app::OSResourceSingleton::Id;
    MsgQ qMsg(resources.getQHandle(Id::CloudTask));

    auto event = (isConnected) ? EventId::WifiConnected : EventId::WifiDisconnected;
    qMsg.set({event, nullptr, 0U});
}

// callback when platform feedback about the mqtt connection status
void mqtt_status_callback(bool isConnected) {
    OSResourceSingleton& resources = OSResourceSingleton::getInstance();
    using Id = app::OSResourceSingleton::Id;
    MsgQ qMsg(resources.getQHandle(Id::CloudTask));

    auto event = (isConnected) ? EventId::CloudConnected : EventId::CloudDisconnected;
    qMsg.set({event, nullptr, 0U});
}
}

Cloud::Cloud(QHandle rxQHandle):
    m_rxMsgQ(rxQHandle),
    m_controlMsgQ(OSResourceSingleton::getInstance().getQHandle(app::OSResourceSingleton::Id::ControlTask)),
    m_wifi(wifi_status_callback),
    m_mqtt(mqtt_status_callback)
{}

void Cloud::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};

    m_wifi.connect();

    for (;;) {
        m_rxMsgQ.get(&msg);
        handle(msg);
    }
}

void Cloud::handle(const app::Msg& msg) {
    switch(msg.ev) {
    case EventId::WifiConnected:
        m_controlMsgQ.set(msg); // forward it to control.
        connectToCloud();
        break;
    case EventId::WifiDisconnected:
        m_controlMsgQ.set(msg); // forward it to control.
        // TODO: error handling
        break;
    case EventId::CloudConnected:
        m_controlMsgQ.set(msg); // forward it to control.
        m_mqtt.publish("/topic/startup", "hello master Babang/Sunil, how I may serve you?");
        m_controlMsgQ.set({EventId::DataPublishedToCloud, nullptr, 0U});
        break;
    case EventId::CloudDisconnected:
        m_controlMsgQ.set(msg); // forward it to control.
        // TODO: error handling.
        break;
    default:
        break;
    }
}

void Cloud::connectToCloud() {
    m_mqtt.connect();
}

