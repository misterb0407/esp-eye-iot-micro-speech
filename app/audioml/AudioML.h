#ifndef APP_AUDIO_ML_H
#define APP_AUDIO_ML_H

// Standard includes.
#include <memory>

// Project includes.
#include "Event.h"
#include "MsgInbox.h"
#include "control/Control.h"
#include "os/OSWrapper.h"

namespace app {
namespace audioml {

class AudioML {
public:
    AudioML() = delete;
    explicit AudioML(std::shared_ptr<MsgInbox> inbox, std::shared_ptr<Control> control);
    ~AudioML() = default;

    // No copy allowed
    AudioML(const AudioML& other) = delete;
    AudioML& operator=(const AudioML& other) = delete;

    void run();

private:
    enum class State : uint8_t {
        Init
        // TODO
    };

    // State management.
    void runStateMachine(const app::Msg& msg);
    void onExitState(const State state);
    void onEnterState(const State state);

    std::shared_ptr<MsgInbox> m_inbox;
    std::shared_ptr<Control> m_control;
};

} // namespace app
} // namespace audioml

using app::audioml::AudioML;

#endif // APP_AUDIO_ML_H