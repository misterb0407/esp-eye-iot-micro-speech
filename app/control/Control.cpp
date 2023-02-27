// Project includes.
#include "Control.h"

// Platform includes.
#include "log/Log.h"

using namespace app;

Control::Control(QHandle rxQHandle):
    m_rxMsgQ(rxQHandle)
{}

void Control::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};
    for (;;) {
        runStateMachine(msg);
        m_rxMsgQ.get(&msg);
    }
}

void Control::runStateMachine(const app::Msg& msg) {
    // TODO
    int i = 0;
    while (1) {
        log("[%d] Hello world from controlTask!\n", i);
        i++;
        platform::os::OSWrapper::delay(5000);
    }
}

void Control::onExitState(const State state) {
    // TODO.
    (void)state;
}

void Control::onEnterState(const State state) {
    // TODO
    (void)state;
}
