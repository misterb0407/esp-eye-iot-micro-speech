// Project includes.
#include "Control.h"

// Platform includes.
#include "log/Log.h"
#include "OSResourceSingleton.h"

using namespace app;

Control::Control(QHandle rxQHandle):
    m_rxMsgQ(rxQHandle),
    m_ledInbox(OSResourceSingleton::getInstance().getQHandle(app::OSResourceSingleton::Id::LEDTask))
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
            m_ledInbox.set(msg);
            break;
        case EventId::WifiDisconnected:
            m_ledInbox.set(msg);
            break;
        case EventId::CloudConnected:
            m_ledInbox.set(msg);
            break;
        case EventId::CloudDisconnected:
            m_ledInbox.set(msg);
            break;
        case EventId::DataPublishedToCloud:
            m_ledInbox.set(msg);
            break;
        default:
            break;
    }
}

const char* Control::toString(EventId event) const {
    auto it = m_mapStrEventId.find(event);

    return (it != m_mapStrEventId.end()) ? it->second : "";
}

