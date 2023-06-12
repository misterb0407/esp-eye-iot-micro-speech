#ifndef APP_LED_H
#define APP_LED_H

// Standard includes.
#include <memory>
#include <list>
#include <map>

// Project includes.
#include "Event.h"
#include "MsgInbox.h"
#include "control/Control.h"

// Platform includes.
#include "os/OSWrapper.h"

namespace app {
namespace led {

class LED {
public:
    LED() = delete;
    LED(std::shared_ptr<MsgInbox> inbox, std::shared_ptr<Control> control);
    ~LED() = default;

    // No copy allowed
    LED(const LED& other) = delete;
    LED& operator=(const LED& other) = delete;

    void run();

private:
    // Consult datasheet for the associated LED GPIO number.
    static const uint32_t RED_LED_GPIO_NUM = 21U;
    static const uint32_t WHITE_LED_GPIO_NUM = 22U;

    /*
     * Max duration this task is blocked when no incoming msg, ensure
     * it is smaller than the LED blinking rate.
     */
    static const uint32_t TASK_RATE_MS = 50U;
    // LED blinking rate
    static const uint32_t CONNECTING_TO_WIRELESS_BLINK_RATE_MS = 100U;
    static const uint32_t CONNECTING_TO_CLOUD_BLINK_RATE_MS = 500U;
    static const uint32_t PUBLISHING_TO_CLOUD_BLINK_DURATION_MS = 1000U;

    enum class State : uint8_t {
        ConnectingToWireless,
        ConnectingToCloud,
        Normal,
        PublishingToCloud,
        Error
    };

    std::list<EventId> m_events_to_subscribe = {
        EventId::WifiConnected,
        EventId::WifiDisconnected,
        EventId::CloudConnected,
        EventId::CloudDisconnected,
        EventId::DataPublishedToCloud
    };

    // State management.
    void runStateMachine(const app::Msg& msg);
    void onExitState(const State state);
    void onEnterState(const State state);

    // State handlers.
    void handleStateConnectingToWireless(const app::Msg& msg);
    void handleStateConnectingToCloud(const app::Msg& msg);
    void handleStateNormal(const app::Msg& msg);
    void handleStatePublishingToCloud(const app::Msg& msg);
    void handleStateError(const app::Msg& msg);

    // Private helpers
    void turnRed(bool isOn);
    void turnWhite(bool isOn);

    // Associate the state with its handler
    std::map<State, void (LED::*)(const app::Msg& msg)> m_mapStateHandler = {
        {State::ConnectingToWireless, &LED::handleStateConnectingToWireless},
        {State::ConnectingToCloud, &LED::handleStateConnectingToCloud},
        {State::Normal, &LED::handleStateNormal},
        {State::PublishingToCloud, &LED::handleStatePublishingToCloud},
        {State::Error, &LED::handleStateError},
    };

    std::shared_ptr<MsgInbox> m_inbox;
    std::shared_ptr<Control> m_control;

    // State mamagement.
    State m_currentState;
    State m_nextState;
};

} // namespace app
} // namespace led

using app::led::LED;

#endif // APP_LED_H
