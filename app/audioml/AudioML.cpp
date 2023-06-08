// Project includes.
#include "AudioML.h"
#include "hello-world/main_functions.h"

// Platform includes.
#include "log/Log.h"

using namespace app;

AudioML::AudioML(std::shared_ptr<MsgInbox> inbox, std::shared_ptr<Control> control):
    m_inbox(inbox),
    m_control(control)
{}

void AudioML::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};

    for (;;) {
        runStateMachine(msg);
        m_inbox->get(&msg);
    }
}

void AudioML::runStateMachine(const app::Msg& msg) {
    // TODO
    //setup();
    while (1) {
        //loop();
        platform::os::OSWrapper::delay(3000);
    }
}

void AudioML::onExitState(const State state) {
    // TODO.
    (void)state;
}

void AudioML::onEnterState(const State state) {
    // TODO
    (void)state;
}
