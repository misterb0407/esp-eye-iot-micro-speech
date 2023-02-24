// Standard includes.
#include <cassert>

// Project includes.
#include "OSResourceSingleton.h"

OSResourceSingleton::OSResourceSingleton():
    m_qHandleControlTask(nullptr),
    m_qHandleLEDTask(nullptr),
    m_qHandleCloudTask(nullptr),
    m_qHandleAudioMLTask(nullptr)
{}

OSResourceSingleton& OSResourceSingleton::getInstance() {
    static OSResourceSingleton s_instance;
    return s_instance;
}

QHandle OSResourceSingleton::getQHandle(Id id) const {
    auto it = m_mapQHandle.find(id);
    assert(it != m_mapQHandle.end());

    if (it != m_mapQHandle.end()) {
        if (it->second != nullptr) {
            return *(it->second);
        }
    }

    return nullptr;
}

void OSResourceSingleton::setQHandle(Id id, const QHandle handle) {
    auto it = m_mapQHandle.find(id);
    assert(it != m_mapQHandle.end() && (handle != nullptr));

    if (it != m_mapQHandle.end()) {
        if (it->second != nullptr) {
            *(it->second) = handle;
        }
    }

}