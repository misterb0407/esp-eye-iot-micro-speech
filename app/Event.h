#ifndef EVENT_H
#define EVENT_H

// Standard includes.
#include <cstdint>
namespace app {
enum class EventId : uint8_t {
    Invalid = 0,
    WifiConnected,
    WifiDisconnected,
    CloudConnected,
    CloudDisconnected,
    DataPublishedToCloud,
    VoiceYesDetected,
    VoiceNoDetected
};

// Message is event with payload.
struct Msg {
    EventId ev; // Event type.
    void* pData; // since different event might have different payload.
    uint32_t size; // size of the message payload (i.e. data pointed by pData).
};

} // namespace app

#endif // EVENT_H
