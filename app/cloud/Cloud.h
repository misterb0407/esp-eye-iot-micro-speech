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
    // Private helper
    void handle(const app::Msg& msg);
    void connectToCloud();

    MsgQ m_rxMsgQ;
    MsgQ m_controlMsgQ;
};

} // namespace app
} // namespace cloud

using app::cloud::Cloud;

#endif // APP_CLOUD_H
