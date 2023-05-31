#ifndef APP_CONTROL_H
#define APP_CONTROL_H

// Standard includes
#include <map>

// Project includes.
#include "Event.h"
#include "MsgQ.h"

// Platform includes.
#include "os/OSWrapper.h"

namespace app {
namespace control {

class Control {
public:
    Control() = delete;
    explicit Control(QHandle rxQHandle);
    ~Control() = default;

    // No copy allowed
    Control(const Control& other) = delete;
    Control& operator=(const Control& other) = delete;

    void run();

private:
    std::map<const EventId, const char*> m_mapStrEventId = {
        {EventId::WifiConnected, "WifiConnected"},
        {EventId::WifiDisconnected, "WifiDisconnected"},
        {EventId::CloudConnected, "CloudConnected"},
        {EventId::CloudDisconnected, "CloudDisonnected"},
    };

    // Private helpes
    void handle(const app::Msg& msg);
    const char* toString(EventId event) const;

    MsgQ m_rxMsgQ;
    MsgQ m_ledInbox;
};

} // namespace app
} // namespace control

using app::control::Control;

#endif // APP_CONTROL_H
