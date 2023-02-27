#ifndef CONTROL_H
#define CONTROL_H

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
    enum class State : uint8_t {
        Init
        // TODO
    };

    // State management.
    void runStateMachine(const app::Msg& msg);
    void onExitState(const State state);
    void onEnterState(const State state);

    // TODO
    MsgQ m_rxMsgQ;
};

} // namespace app
} // namespace control

using app::control::Control;

#endif // CONTROL_H