// Standard includes.
#include <cassert>

// Project includes.
#include "Control.h"

// Platform includes.
#include "log/Log.h"
#include "os/OSWrapper.h"

using namespace app;

Control::Control(std::shared_ptr<MsgInbox> inbox):
    m_inbox(inbox)
{
    assert(m_inbox != nullptr);
}

void Control::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};
    for (;;) {
        m_inbox->get(&msg);
        handle(msg);
    }
}

void Control::set(const Msg& msg, uint32_t timeoutMs) const {
    m_inbox->set(msg);
}

void Control::handle(const app::Msg& msg) {
    log("control: %s(%d) event received\n", toString(msg.ev), static_cast<int>(msg.ev));
    publish(msg); // publish event to subscriber(s).
}

const char* Control::toString(EventId event) const {
    auto it = m_mapStrEventId.find(event);
    return (it != m_mapStrEventId.end()) ? it->second : "";
}

void Control::subscribe(EventId event, std::shared_ptr<MsgInbox> inbox) {
    m_mapEventSubscriber[event].push_back(inbox);
}

void Control::publish(const app::Msg& msg) {
    auto vinbox = m_mapEventSubscriber[msg.ev];
    for (const auto& inbox : vinbox) {
        inbox->set(msg);
    }
}