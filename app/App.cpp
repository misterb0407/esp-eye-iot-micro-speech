// Standard includes.
#include <stdio.h>

// Project includes.
#include "App.h"
#include "Event.h"
#include "OSResourceSingleton.h"
#include "led/LED.h"
#include "control/Control.h"
#include "cloud/Cloud.h"
#include "audioml/AudioML.h"

// Platform includes.
#include "log/Log.h"
#include "os/OSWrapper.h"

static void initQ() {
    auto controlQHandle = OSWrapper::createQueue(10, sizeof(app::Msg));
    auto ledQHandle = OSWrapper::createQueue(3, sizeof(app::Msg));
    auto cloudQHandle = OSWrapper::createQueue(10, sizeof(app::Msg));
    auto audiomlQHandle = OSWrapper::createQueue(10, sizeof(app::Msg));

    OSResourceSingleton& resources = OSResourceSingleton::getInstance();
    using Id = app::OSResourceSingleton::Id;

    resources.setQHandle(Id::ControlTask, controlQHandle);
    resources.setQHandle(Id::LEDTask, ledQHandle);
    resources.setQHandle(Id::CloudTask, cloudQHandle);
    resources.setQHandle(Id::AudioMLTask, audiomlQHandle);
}

static void controlTask(void* argument) {
    OSResourceSingleton& resources = OSResourceSingleton::getInstance();
    using Id = app::OSResourceSingleton::Id;

    static Control s_control(resources.getQHandle(Id::ControlTask));

    s_control.run();
}

static void ledTask(void* argument) {
    OSResourceSingleton& resources = OSResourceSingleton::getInstance();
    using Id = app::OSResourceSingleton::Id;

    static LED s_led(resources.getQHandle(Id::LEDTask));

    s_led.run();
}

static void cloudTask(void* argument) {
    OSResourceSingleton& resources = OSResourceSingleton::getInstance();
    using Id = app::OSResourceSingleton::Id;

    static Cloud s_cloud(resources.getQHandle(Id::CloudTask));

    s_cloud.run();
}

static void audimlTask(void* argument) {
    OSResourceSingleton& resources = OSResourceSingleton::getInstance();
    using Id = app::OSResourceSingleton::Id;

    static AudioML s_audioml(resources.getQHandle(Id::CloudTask));

    s_audioml.run();
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
