#ifndef APP_CONTROL_H
#define APP_CONTROL_H

// Standard includes
#include <map>
#include <memory>
#include <vector>

// Project includes.
#include "Event.h"
#include "MsgInbox.h"

// Platform includes.
#include "os/OSWrapper.h"

namespace app {
namespace control {

class Control {
public:
    Control() = delete;
    explicit Control(std::shared_ptr<MsgInbox> inbox);
    ~Control() = default;

    // No copy allowed
    Control(const Control& other) = delete;
    Control& operator=(const Control& other) = delete;

    void run();
    void set(const Msg& msg, uint32_t timeoutMs = UINT32_MAX) const;
    void subscribe(EventId event, std::shared_ptr<MsgInbox> inbox);

private:
    std::map<const EventId, const char*> m_mapStrEventId = {
        {EventId::WifiConnected, "WifiConnected"},
        {EventId::WifiDisconnected, "WifiDisconnected"},
        {EventId::CloudConnected, "CloudConnected"},
        {EventId::CloudDisconnected, "CloudDisonnected"},
        {EventId::DataPublishedToCloud, "DataPublishedToCloud"}
    };

    std::map<EventId, std::vector<std::shared_ptr<MsgInbox>>> m_mapEventSubscriber;

    // Private helpers.
    void handle(const app::Msg& msg);
    const char* toString(EventId event) const;
    void publish(const app::Msg& msg);

    std::shared_ptr<MsgInbox> m_inbox;
};

} // namespace app
} // namespace control

using app::control::Control;

#endif // APP_CONTROL_H
