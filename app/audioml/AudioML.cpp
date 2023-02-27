// Project includes.
#include "AudioML.h"

// Platform includes.
#include "log/Log.h"

using namespace app;

AudioML::AudioML(QHandle rxQHandle):
    m_rxMsgQ(rxQHandle)
{}

void AudioML::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};
    for (;;) {
        runStateMachine(msg);
        m_rxMsgQ.get(&msg);
    }
}

void AudioML::runStateMachine(const app::Msg& msg) {
    // TODO
    int i = 0;
    while (1) {
        log("[%d] Hello world from audiomlTask!\n", i);
        i++;
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
