#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

// Standard includes.
#include <cstdint>
#include <limits>

// Project includes.
#include "Event.h"
#include "os/OSWrapper.h"

namespace app {

class MsgQ {
public:
    MsgQ() = delete;
    explicit MsgQ(QHandle handle);
    ~MsgQ() = default;

    // No copy allowed.
    MsgQ(const MsgQ& other) = delete;
    MsgQ& operator=(const MsgQ& other) = delete;

    void get(Msg* pMsg, uint32_t timeoutMs = UINT32_MAX) const;
    void set(const Msg& msg, uint32_t timeoutMs = UINT32_MAX) const;

private:
    QHandle m_qHandle;
};

} // namespace app

using app::MsgQ;

#endif // MSG_QUEUE_H