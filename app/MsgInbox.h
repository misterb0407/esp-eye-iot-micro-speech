#ifndef MSG_INBOX_H
#define MSG_INBOX_H

// Standard includes.
#include <cstdint>
#include <cstddef>
#include <limits>

// Project includes.
#include "Event.h"
#include "os/OSWrapper.h"

namespace app {

class MsgInbox {
public:
    MsgInbox() = delete;
    explicit MsgInbox(size_t count);
    ~MsgInbox() = default;

    // No copy allowed.
    MsgInbox(const MsgInbox& other) = delete;
    MsgInbox& operator=(const MsgInbox& other) = delete;

    void get(Msg* pMsg, uint32_t timeoutMs = UINT32_MAX) const;
    void set(const Msg& msg, uint32_t timeoutMs = UINT32_MAX) const;

private:
    QHandle m_qHandle;
};

} // namespace app

using app::MsgInbox;

#endif // MSG_INBOX_H