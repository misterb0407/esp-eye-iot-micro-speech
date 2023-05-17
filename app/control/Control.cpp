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
    switch(msg.ev) {
        case EventId::WifiConnected:
            log("rcvd event: wifi connected\n");
            break;
        case EventId::WifiDisconnected:
            log("rcvd event: wifi connected\n");
            break;
        case EventId::CloudConnected:
            log("rcvd event: cloud connected\n");
            break;
        case EventId::CloudDisconnected:
            log("rcvd event: cloud disconnected\n");
            break;
        default:
            break;
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
