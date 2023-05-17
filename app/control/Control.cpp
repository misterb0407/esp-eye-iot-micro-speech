// Project includes.
#include "Control.h"

// Platform includes.
#include "log/Log.h"

using namespace app;

Control::Control(QHandle rxQHandle):
    m_rxMsgQ(rxQHandle)
{}

void Control::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};
    for (;;) {
        m_rxMsgQ.get(&msg);
        handle(msg);
    }
}

void Control::handle(const app::Msg& msg) {
    log("control: %s(%d) event received\n", toString(msg.ev), static_cast<int>(msg.ev));

    switch(msg.ev) {
        case EventId::WifiConnected:
            // TODO: forward to LED
            break;
        case EventId::WifiDisconnected:
            // TODO: forward to LED
            break;
        case EventId::CloudConnected:
            // TODO: forward to LED
            break;
        case EventId::CloudDisconnected:
            // TODO: forward to LED
            break;
        default:
            break;
    }
}

const char* Control::toString(EventId event) const {
    auto it = m_mapStrEventId.find(event);

    return (it != m_mapStrEventId.end()) ? it->second : "";
}

