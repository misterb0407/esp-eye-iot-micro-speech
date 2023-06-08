// Project includes.
#include "LED.h"

// Platform includes.
#include "log/Log.h"
#include "peripheral/gpio/GPIO.h"

using namespace app;
using namespace platform::peripheral::gpio;

LED::LED(std::shared_ptr<MsgInbox> inbox, std::shared_ptr<Control> control):
    m_inbox(inbox),
    m_control(control),
    m_currentState(State::ConnectingToWireless),
    m_nextState(State::ConnectingToWireless)
{
    // Subscribe to event(s) of interest.
    m_control->subscribe(EventId::WifiConnected, m_inbox);
    m_control->subscribe(EventId::WifiDisconnected, m_inbox);
    m_control->subscribe(EventId::CloudConnected, m_inbox);
    m_control->subscribe(EventId::CloudDisconnected, m_inbox);
    m_control->subscribe(EventId::DataPublishedToCloud, m_inbox);
}

void LED::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};
    GPIO::setOutDirection(RED_LED_GPIO_NUM);
    GPIO::setOutDirection(WHITE_LED_GPIO_NUM);

    for (;;) {
        runStateMachine(msg);
        m_inbox->get(&msg, TASK_RATE_MS);
    }
}

void LED::runStateMachine(const Msg& msg) {
    switch (m_currentState) {
        case State::ConnectingToWireless:
            handleStateConnectingToWireless(msg);
            break;
        case State::ConnectingToCloud:
            handleStateConnectingToCloud(msg);
            break;
        case State::PublishingToCloud:
            handleStatePublishingToCloud(msg);
            break;
        case State::Normal:
            handleStateNormal(msg);
            break;
        case State::Error:
            handleStateError(msg);
            break;
        default:
            break;
    }

    if (m_currentState != m_nextState) {
        log("LED: State %d -> %d\n", (int)m_currentState, (int)m_nextState);
        onExitState(m_currentState);
        onEnterState(m_nextState);
        m_currentState = m_nextState;
    }
}

void LED::onExitState(const State state) {
    (void)state;
    // Do nothing.
}

void LED::onEnterState(const State state) {
    switch (state) {
        case State::Normal:
            turnWhite(true);
            turnRed(false);
            break;
        default:
            break;
    }
}

void LED::handleStateConnectingToWireless(const Msg& msg) {
    static bool s_isReadOn = true;
    static uint32_t s_counter = 0U;

    s_counter++;
    switch(msg.ev) {
        case EventId::WifiConnected:
            m_nextState = State::ConnectingToCloud;
            break;
        case EventId::WifiDisconnected:
            m_nextState = State::Error;
            break;
        case EventId::CloudConnected:
            m_nextState = State::Normal;
            break;
        default:
            // Toggle LED at certain rate.
            if (s_counter*TASK_RATE_MS >= CONNECTING_TO_WIRELESS_BLINK_RATE_MS) {
                turnRed(s_isReadOn^=true);
                s_counter = 0;
            }
            break;
    }

}

void LED::handleStateConnectingToCloud(const Msg& msg) {
    static bool s_isReadOn2 = true;
    static uint32_t s_counter2 = 0U;

    s_counter2++;
    switch(msg.ev) {
        case EventId::CloudConnected:
            m_nextState = State::Normal;
            break;
        case EventId::CloudDisconnected:
            m_nextState = State::Error;
            break;
        default:
            // Toggle LED at certain rate.
            if (s_counter2*TASK_RATE_MS >= CONNECTING_TO_CLOUD_BLINK_RATE_MS) {
                turnRed(s_isReadOn2^=true);
                s_counter2 = 0;
            }
            break;
    }
}

void LED::handleStateNormal(const app::Msg& msg) {
    switch(msg.ev) {
        case EventId::DataPublishedToCloud:
            m_nextState = State::PublishingToCloud;
            break;
        default:
            break;
    }
}

void LED::handleStatePublishingToCloud(const Msg& msg) {
    static bool s_isOn = false;
    static uint32_t s_counter3 = 0;

    turnWhite(s_isOn^=true);
    s_counter3++;

    if (s_counter3*TASK_RATE_MS >= PUBLISHING_TO_CLOUD_BLINK_DURATION_MS) {
        m_nextState = State::Normal;
    }
}

void LED::handleStateError(const Msg& msg) {
    static bool s_isReadOn3 = true;
    turnRed(s_isReadOn3^=true);
}

// Private helpers
void LED::turnRed(bool isOn) {
    if (isOn) {
        GPIO::set(RED_LED_GPIO_NUM);
    }
    else {
        GPIO::clear(RED_LED_GPIO_NUM);
    }
}

void LED::turnWhite(bool isOn) {
    if (isOn) {
        GPIO::set(WHITE_LED_GPIO_NUM);
    }
    else {
        GPIO::clear(WHITE_LED_GPIO_NUM);
    }
}
