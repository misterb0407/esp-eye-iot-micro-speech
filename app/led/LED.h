#ifndef SENSOR_H
#define SENSOR_H

// Project includes.
#include "Event.h"
#include "MsgQ.h"

// Platform includes.
#include "os/OSWrapper.h"

namespace app {
namespace led {

class LED {
public:
    LED() = delete;
    explicit LED(QHandle rxQHandle);
    ~LED() = default;

    // No copy allowed
    LED(const LED& other) = delete;
    LED& operator=(const LED& other) = delete;

    void run();

private:
    enum class State : uint8_t {
        Init,
        ConnectingToCloud,
        PublishingToCloud,
        Error,
        Sleep
    };

    // State management.
    void runStateMachine(const app::Msg& msg);
    void onExitState(const State state);
    void onEnterState(const State state);

    // State handlers.
    void handleStateInit(const app::Msg& msg);
    void handleStateConnectingToCloud(const app::Msg& msg);
    void handleStatePublishingToCloud(const app::Msg& msg);
    void handleStateError(const app::Msg& msg);
    void handleStateSleep(const app::Msg& msg);

    MsgQ m_rxMsgQ;
    MsgQ m_txMsgQSocIfc;

    // State mamagement.
    State m_currentState;
    State m_nextState;
};

} // namespace app
} // namespace led

using app::led::LED;

#endif // SENSOR_H