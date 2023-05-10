#ifndef APP_CLOUD_H
#define APP_CLOUD_H

// Project includes.
#include "Event.h"
#include "MsgQ.h"

// Platform includes.
#include "os/OSWrapper.h"

namespace app {
namespace cloud {

class Cloud {
public:
    Cloud() = delete;
    explicit Cloud(QHandle rxQHandle);
    ~Cloud() = default;

    // No copy allowed
    Cloud(const Cloud& other) = delete;
    Cloud& operator=(const Cloud& other) = delete;

    void run();

private:
    enum class State : uint8_t {
        Init,
        ConnectingToWifi,
        ConnectingToCloud,
        Running,
        Invalid
    };

    // State management.
    void runStateMachine(const app::Msg& msg);
    void onExitState(const State state);
    void onEnterState(const State state);

    // State handles
    void handleStateConnectingToWifi(const app::Msg& msg);
    void handleStateConnectingToCloud(const app::Msg& msg);

    MsgQ m_rxMsgQ;
    MsgQ m_controlMsgQ;

    State m_currentState;
    State m_nextState;
};

} // namespace app
} // namespace cloud

using app::cloud::Cloud;

#endif // APP_CLOUD_H
