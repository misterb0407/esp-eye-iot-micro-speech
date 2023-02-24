// Project includes.
#include "MsgQ.h"

using namespace app;

MsgQ::MsgQ(QHandle handle):
    m_qHandle(handle)
{}

void MsgQ::get(Msg* pMsg, uint32_t timeoutMs) const {
    if (pMsg == nullptr) {
        return;
    }

    if (OSWrapper::getQueue(m_qHandle, static_cast<void*>(pMsg), timeoutMs) == false) {
        pMsg->ev = EventId::Invalid;
        pMsg->pData = nullptr;
        pMsg->size = 0U;
    }
}

void MsgQ::set(const Msg& msg, uint32_t timeoutMs) const {
    (void)OSWrapper::putQueue(m_qHandle, static_cast<const void*>(&msg), timeoutMs);
}