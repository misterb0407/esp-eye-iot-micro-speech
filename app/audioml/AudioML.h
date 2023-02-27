#ifndef APP_AUDIO_ML_H
#define APP_AUDIO_ML_H

// Project includes.
#include "Event.h"
#include "MsgQ.h"

// Platform includes.
#include "os/OSWrapper.h"

namespace app {
namespace audioml {

class AudioML {
public:
    AudioML() = delete;
    explicit AudioML(QHandle rxQHandle);
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

    // TODO
    MsgQ m_rxMsgQ;
};

} // namespace app
} // namespace audioml

using app::audioml::AudioML;

#endif // APP_AUDIO_ML_H