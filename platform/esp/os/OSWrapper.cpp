// Standard includes.
#include <cassert>

// Library includes.

// RTOS to wrap.
/* FreeRTOS kernel includes. */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

// Project includes.
#include "OSWrapper.h"

QHandle OSWrapper::createQueue(uint32_t count, uint32_t size) {
    return static_cast<QHandle>(xQueueCreate(count, size));
}

bool OSWrapper::putQueue(QHandle handle, const void* pMsg, uint32_t timeoutMs) {
    if (pMsg == nullptr) {
        return false;
    }

    auto ticks = getTickCount(timeoutMs);
    return (pdPASS == xQueueSendToBack (static_cast<QueueHandle_t>(handle), pMsg, static_cast<TickType_t>(ticks)));
}

bool OSWrapper::getQueue(QHandle handle, void* pMsg, uint32_t timeoutMs) {
    if (pMsg == nullptr) {
        return false;
    }

    auto ticks = getTickCount(timeoutMs);
    return (pdPASS == xQueueReceive (static_cast<QueueHandle_t>(handle), pMsg, static_cast<TickType_t>(ticks)));
}

bool OSWrapper::putQueueFromISR(QHandle handle, const void* pMsg) {
    if (pMsg == nullptr) {
        return false;
    }

    /*
     * Consult FreeRTOS docs for this param.
     * pdFALSE : No tasks have yet been unblocked.
     */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    return (pdPASS == xQueueSendToBackFromISR(static_cast<QueueHandle_t>(handle), pMsg, &xHigherPriorityTaskWoken));
}

bool OSWrapper::createTask(const TaskAttribute* attr) {
    bool result;

    result = xTaskCreate(attr->func, attr->name, attr->stackSize, attr->argument, attr->priority, nullptr);

    assert(result == pdPASS);

    return result;
}

void OSWrapper::startOS() {
    vTaskStartScheduler();
}

void OSWrapper::delay(uint32_t msec) {
    auto ticks = getTickCount(msec);
    vTaskDelay(ticks);
}

TimerHandle OSWrapper::createTimer(const char* name, uint32_t periodMs, TimerCallback callback)
{
  auto periodTicks = getTickCount(periodMs);

  return (TimerHandle)xTimerCreate(
          name,
          periodTicks,
          pdTRUE, // Only for auto reload timer.
          0, // Not using timer ID.
          (TimerCallbackFunction_t)callback);
}

void OSWrapper::startTimer(TimerHandle handle, uint32_t msec) {
    auto ticks = getTickCount(msec);
    (void)xTimerChangePeriod(static_cast<TimerHandle_t>(handle),ticks, 0);
}

void OSWrapper::stopTimer(TimerHandle handle) {
    (void)xTimerStop(static_cast<TimerHandle_t>(handle), 0);
}

uint32_t OSWrapper::getTickCount(uint32_t msec) {
    auto freq = configTICK_RATE_HZ;
    auto tickCount = (freq*msec)/1000U;
    return tickCount;
}

uint16_t OSWrapper::getMinStackSize() {
	return configMINIMAL_STACK_SIZE;
}

uint32_t OSWrapper::getMaxTaskPriority() {
	return configMAX_PRIORITIES;
}