// Project includes.
#include "LED.h"

// Platform includes.
#include "log/Log.h"
#include "peripheral/gpio/GPIO.h"

using namespace app;
using namespace platform::peripheral::gpio;

LED::LED(QHandle rxQHandle):
    m_rxMsgQ(rxQHandle),
    m_currentState(State::Invalid),
    m_nextState(State::Init)
{}

void LED::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};
    for (;;) {
        runStateMachine(msg);
        m_rxMsgQ.get(&msg);
    }
}

void LED::runStateMachine(const Msg& msg) {
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
    switch (state) {
        case State::Init:
            GPIO::setOutDirection(RED_LED_GPIO_NUM);
            GPIO::setOutDirection(WHITE_LED_GPIO_NUM);

            GPIO::set(RED_LED_GPIO_NUM);
            GPIO::set(WHITE_LED_GPIO_NUM);
            break;
        default:
            break;
    }
}

void LED::handleStateInit(const Msg& msg) {
    // TODO
}

void LED::handleStateConnectingToCloud(const Msg& msg) {
    // TODO
}

void LED::handleStatePublishingToCloud(const Msg& msg) {
    // TODO
}

void LED::handleStateError(const Msg& msg) {
    // TODO
}

void LED::handleStateSleep(const Msg& msg) {
    // TODO
}