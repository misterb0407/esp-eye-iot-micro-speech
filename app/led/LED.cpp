// Project includes.
#include "LED.h"

// Platform includes.
#include "log/Log.h"

using namespace app;

LED::LED(QHandle rxQHandle):
    m_rxMsgQ(rxQHandle),
    m_txMsgQSocIfc(nullptr),
    m_currentState(State::Init),
    m_nextState(State::Init)
{}

void LED::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};
    for (;;) {
        runStateMachine(msg);
        m_rxMsgQ.get(&msg);
    }
}

void LED::runStateMachine(const app::Msg& msg) {
    switch (m_currentState) {
        case State::Init:
            handleStateInit(msg);
            break;
        case State::ConnectingToCloud:
            handleStateConnectingToCloud(msg);
            break;
        case State::PublishingToCloud:
            handleStatePublishingToCloud(msg);
            break;
        case State::Error:
            handleStateError(msg);
            break;
        case State::Sleep:
            handleStateSleep(msg);
            break;
        default:
            break;
    }

    if (m_currentState != m_nextState) {
        onExitState(m_currentState);
        onEnterState(m_nextState);
        m_currentState = m_nextState;
    }
}

void LED::onExitState(const State state) {
    // TODO.
    (void)state;
}

void LED::onEnterState(const State state) {
    // TODO
    (void)state;
}

void LED::handleStateInit(const app::Msg& msg) {
    // TODO
    log("Hello world LED state init!\n");
}

void LED::handleStateConnectingToCloud(const app::Msg& msg) {
    // TODO
}

void LED::handleStatePublishingToCloud(const app::Msg& msg) {
    // TODO
}

void LED::handleStateError(const app::Msg& msg) {
    // TODO
}

void LED::handleStateSleep(const app::Msg& msg) {
    // TODO
}