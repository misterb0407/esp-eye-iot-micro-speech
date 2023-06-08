// Standard includes.
#include <cassert>

// Project includes.
#include "MsgInbox.h"
#include "os/OSWrapper.h"

MsgInbox::MsgInbox(size_t count):
    m_qHandle(OSWrapper::createQueue(count, sizeof(app::Msg)))
{
    assert(m_qHandle != nullptr);
}

void MsgInbox::get(Msg* pMsg, uint32_t timeoutMs) const {
    if (pMsg == nullptr) {
        return;
    }

    if (OSWrapper::getQueue(m_qHandle, static_cast<void*>(pMsg), timeoutMs) == false) {
        pMsg->ev = EventId::Invalid;
        pMsg->pData = nullptr;
        pMsg->size = 0U;
    }
}

void MsgInbox::set(const Msg& msg, uint32_t timeoutMs) const {
    (void)OSWrapper::putQueue(m_qHandle, static_cast<const void*>(&msg), timeoutMs);
}