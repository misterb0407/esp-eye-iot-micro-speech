// Platform includes.
#include "log/Log.h"
#include "com/wifi/Wifi.h"

// Project includes.
#include "Cloud.h"
#include "OSResourceSingleton.h"

using namespace app;

namespace {
void wifi_status_callback(bool isConnected) {
    OSResourceSingleton& resources = OSResourceSingleton::getInstance();
    using Id = app::OSResourceSingleton::Id;
    MsgQ qMsg(resources.getQHandle(Id::CloudTask));

    if (isConnected) {
        qMsg.set({EventId::WifiConnected, nullptr, 0U});
    }
    else {
        qMsg.set({EventId::WifiDisconnected, nullptr, 0U});
    }
}
}

Cloud::Cloud(QHandle rxQHandle):
    m_rxMsgQ(rxQHandle),
    m_controlMsgQ(OSResourceSingleton::getInstance().getQHandle(app::OSResourceSingleton::Id::ControlTask)),
    m_currentState(State::Invalid),
    m_nextState(State::Init)
{}

void Cloud::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};

    for (;;) {
        runStateMachine(msg);
        m_rxMsgQ.get(&msg);
    }
}

void Cloud::runStateMachine(const app::Msg& msg) {
    switch(m_currentState) {
        case State::Init:
            break;
        case State::ConnectingToWifi:
            handleStateConnectingToWifi(msg);
            break;
        case State::ConnectingToCloud:
            handleStateConnectingToCloud(msg);
            break;
        default:
            break;
    };

    if(m_currentState != m_nextState) {
        onExitState(m_currentState);
        onEnterState(m_nextState);
        m_currentState = m_nextState;
    }
}

void Cloud::onExitState(const State state) {
    (void)state; // TODO.
}

void Cloud::onEnterState(const State state) {
    Wifi wifi(wifi_status_callback);
    switch(state) {
        case State::Init:
            wifi.connect();
            m_nextState = State::ConnectingToWifi;
            break;
        default:
            break;
    }
}

void Cloud::handleStateConnectingToWifi(const app::Msg& msg) {
    switch(msg.ev) {
    case EventId::WifiConnected:
        m_nextState = State::ConnectingToCloud;
        m_controlMsgQ.set(msg); // forward it to control.
        break;
    case EventId::WifiDisconnected:
        m_controlMsgQ.set(msg); // forward it to control.
        // TODO: error handling
        break;
    default:
        break;
    }
}

void Cloud::handleStateConnectingToCloud(const app::Msg& msg) {
    // TODO
}

