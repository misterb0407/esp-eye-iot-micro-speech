#ifndef APP_CONTROL_H
#define APP_CONTROL_H

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
    // State management.
    void handle(const app::Msg& msg);

    MsgQ m_rxMsgQ;
};

} // namespace app
} // namespace control

using app::control::Control;

#endif // APP_CONTROL_H
