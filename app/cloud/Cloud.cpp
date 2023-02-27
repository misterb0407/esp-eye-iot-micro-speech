// Project includes.
#include "Cloud.h"

// Platform includes.
#include "log/Log.h"

using namespace app;

Cloud::Cloud(QHandle rxQHandle):
    m_rxMsgQ(rxQHandle)
{}

void Cloud::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};
    for (;;) {
        runStateMachine(msg);
        m_rxMsgQ.get(&msg);
    }
}

void Cloud::runStateMachine(const app::Msg& msg) {
    // TODO
    int i = 0;
    while (1) {
        log("[%d] Hello world from cloudTask!\n", i);
        i++;
        platform::os::OSWrapper::delay(3000);
    }
}

void Cloud::onExitState(const State state) {
    // TODO.
    (void)state;
}

void Cloud::onEnterState(const State state) {
    // TODO
    (void)state;
}
