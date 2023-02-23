#ifndef RTOS_WRAPPER_H
#define RTOS_WRAPPER_H

// Standard includes.
#include <cstdint>

// Data type wrapper.
typedef void* QHandle;
typedef void* TimerHandle;
typedef void (*TimerCallback)( TimerHandle xTimer );

namespace platform {
namespace os {

typedef void (*TaskFunc)(void*);

typedef struct {
    TaskFunc func;
    const char* const name;
    const uint16_t stackSize;
    void* const argument;
    uint32_t priority;
}TaskAttribute;

class OSWrapper {
public:
    OSWrapper() = delete;
    ~OSWrapper() = default;
    // No copy allowed
    OSWrapper(const OSWrapper& other) = delete;
    OSWrapper& operator=(const OSWrapper& other) = delete;

    // Queue management
    static QHandle createQueue(uint32_t count, uint32_t size);
    static bool putQueue(QHandle handle, const void* pMsg, uint32_t timeoutMs = UINT32_MAX);
    static bool getQueue(QHandle handle, void* pMsg, uint32_t timeoutMs = UINT32_MAX);
    static bool putQueueFromISR(QHandle handle, const void* pMsg);

    // Task management
    static bool createTask(const TaskAttribute* attr);
    static void startOS();
    static void delay(uint32_t msec);

    // Timer management.
    static TimerHandle createTimer(const char* name, uint32_t periodMs, TimerCallback callback);
    static void startTimer(TimerHandle handle, uint32_t msec);
    static void stopTimer(TimerHandle handle);

    // OS Config getter
    static uint16_t getMinStackSize();
    static uint32_t getMaxTaskPriority();

private:
    static uint32_t getTickCount(uint32_t msec);
};

} // namespace platform
} // namespace os

using platform::os::OSWrapper;

#endif // RTOS_WRAPPER_H