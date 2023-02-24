#ifndef OS_RESOURCE_SINGLETON_H
#define OS_RESOURCE_SINGLETON_H

// Standard includes.
#include <map>

// Project includes.
#include "os/OSWrapper.h"

namespace app {
class OSResourceSingleton {
public:
    enum class Id {
        ControlTask,
        LEDTask,
        CloudTask,
        AudioMLTask
    };

    // No copy is allowed
    OSResourceSingleton(const OSResourceSingleton& other) = delete;
    OSResourceSingleton& operator=(const OSResourceSingleton& other) = delete;

    static OSResourceSingleton& getInstance();

    QHandle getQHandle(Id id) const;
    void setQHandle(Id id, const QHandle handle);

private:
    OSResourceSingleton();

    // Queue for received event of a task.
    QHandle m_qHandleControlTask;
    QHandle m_qHandleLEDTask;
    QHandle m_qHandleCloudTask;
    QHandle m_qHandleAudioMLTask;

    std::map<Id, QHandle* const> m_mapQHandle = {
        {Id::ControlTask, &m_qHandleControlTask},
        {Id::LEDTask, &m_qHandleLEDTask},
        {Id::CloudTask, &m_qHandleCloudTask},
        {Id::AudioMLTask, &m_qHandleAudioMLTask}
    };

};
} // namespace app

using app::OSResourceSingleton;

#endif // OS_RESOURCE_SINGLETON_H