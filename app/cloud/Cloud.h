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
} // namespace cloud

using app::cloud::Cloud;

#endif // APP_CLOUD_H