// Standard includes.
#include <stdio.h>

// Project includes.
#include "App.h"
#include "log/Log.h"
#include "os/OSWrapper.h"

static void initQ() {
    // TODO
}

static void controlTask(void* argument) {
    // TODO
    int i = 0;
    while (1) {
        log("[%d] Hello world from controlTask!\n", i);
        i++;
        platform::os::OSWrapper::delay(5000);
    }
}

static void ledTask(void* argument) {
    int i = 0;
    while (1) {
        log("[%d] Hello world from ledTask!\n", i);
        i++;
        platform::os::OSWrapper::delay(7000);
    }
}

static void cloudTask(void* argument) {
    int i = 0;
    while (1) {
        log("[%d] Hello world from cloudTask!\n", i);
        i++;
        platform::os::OSWrapper::delay(3000);
    }
}

static void audimlTask(void* argument) {
    int i = 0;
    while (1) {
        log("[%d] Hello world from audimlTask!\n", i);
        i++;
        platform::os::OSWrapper::delay(9000);
    }
}

static void initTask() {
    const uint16_t DEFAULT_STACK_SIZE = 2048U;
    const uint32_t TASK_PRIORITY_HIGHEST = OSWrapper::getMaxTaskPriority();

    const platform::os::TaskAttribute attr[] = {
        {controlTask, "controlTask", 2*DEFAULT_STACK_SIZE, nullptr, TASK_PRIORITY_HIGHEST},
        {ledTask, "ledTask", DEFAULT_STACK_SIZE, nullptr, TASK_PRIORITY_HIGHEST - 2},
        {cloudTask, "cloudTask", 2*DEFAULT_STACK_SIZE, nullptr, TASK_PRIORITY_HIGHEST - 2},
        {audimlTask, "audimlTask", 4U*DEFAULT_STACK_SIZE, nullptr, TASK_PRIORITY_HIGHEST - 2}


    };

    const size_t TASK_COUNT = sizeof(attr)/sizeof(attr[0]);

    for (size_t i = 0; i < TASK_COUNT; i++) {
        OSWrapper::createTask(&(attr[i]));
    }
}

void APP_Init() {
    initQ();
    initTask();
}
