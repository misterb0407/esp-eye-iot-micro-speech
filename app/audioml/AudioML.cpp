// Project includes.
#include "AudioML.h"
#include "micro_speech/main_functions.h"

// Platform includes.
#include "log/Log.h"

using namespace app;

AudioML::AudioML(std::shared_ptr<MsgInbox> inbox, std::shared_ptr<Control> control):
    m_inbox(inbox),
    m_control(control)
{}

void AudioML::run() {
    // For now just use the tflm sample from ESP
    setup();
    for(;;) {
        loop();
    }

#if(0) // to remove
    Msg msg = {EventId::Invalid, nullptr, 0U};

    for (;;) {
        runStateMachine(msg);
        m_inbox->get(&msg);
    }
#endif
}

void AudioML::runStateMachine(const app::Msg& msg) {
    // TODO
}

void AudioML::onExitState(const State state) {
    // TODO.
}

void AudioML::onEnterState(const State state) {
    // TODO
}
