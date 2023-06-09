// Standard includes
#include <memory>

// Project includes.
#include "App.h"
#include "MsgInbox.h"
#include "ResourceMgmt.h"
#include "control/Control.h"
#include "led/LED.h"
#include "cloud/Cloud.cpp"
#include "audioml/AudioML.h"

static void controlTask(void* argument) {
    auto control = ResourceMgmt::getInstance().getControl();
    control->run();
}

static void ledTask(void* argument) {
    auto inbox = std::make_shared<MsgInbox>(5);
    auto control = ResourceMgmt::getInstance().getControl();
    LED led(inbox, control);
    led.run();
}

static void cloudTask(void* argument) {
    auto inbox = std::make_shared<MsgInbox>(10);
    auto control = ResourceMgmt::getInstance().getControl();
    Cloud cloud(inbox, control);
    cloud.run();
}

static void audimlTask(void* argument) {
    auto inbox = std::make_shared<MsgInbox>(10);
    auto control = ResourceMgmt::getInstance().getControl();
    AudioML audioml(inbox, control);
    audioml.run();
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

static void initResources() {
    auto inbox = std::make_shared<MsgInbox>(10);
    auto control = std::make_shared<Control>(inbox);
    ResourceMgmt::getInstance().setControl(control);
}

void APP_Init() {
    initResources();
    initTask();
}
