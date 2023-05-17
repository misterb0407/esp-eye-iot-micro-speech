// Library includes
#include "mqtt_client.h"

// Platform includes.
#include "log/Log.h"
#include "com/wifi/Wifi.h"

// Project includes.
#include "Cloud.h"
#include "OSResourceSingleton.h"

using namespace app;

// This must match with the filename set in CMakeLists.txt with pattern '_binary_<file_name_extention>_<start/end>'
extern const uint8_t server_cert_pem_start[] asm("_binary_server_crt_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_server_crt_end");
extern const uint8_t client_cert_pem_start[] asm("_binary_client_crt_start");
extern const uint8_t client_cert_pem_end[] asm("_binary_client_crt_end");
extern const uint8_t client_key_pem_start[] asm("_binary_client_key_start");
extern const uint8_t client_key_pem_end[] asm("_binary_client_key_end");

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

static void log_error_if_nonzero(const char *message, int error_code) {
    if (error_code != 0) {
        log("Last error %s: 0x%x", message, error_code);
    }
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    OSResourceSingleton& resources = OSResourceSingleton::getInstance();
    using Id = app::OSResourceSingleton::Id;
    MsgQ qMsg(resources.getQHandle(Id::CloudTask));

    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;

    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            qMsg.set({EventId::CloudConnected, nullptr, 0U});
            log("MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
            log("sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
            log("sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
            log("sent unsubscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            qMsg.set({EventId::CloudDisconnected, nullptr, 0U});
            log("MQTT_EVENT_DISCONNECTED");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            log("MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
            log("sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            log("MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            log("MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            log("MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            log("MQTT_EVENT_ERROR");
            if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
                log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
                log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
                log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
                log("Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
            }
            break;
        default:
            log("Other event id:%d", event->event_id);
    }
}

}

Cloud::Cloud(QHandle rxQHandle):
    m_rxMsgQ(rxQHandle),
    m_controlMsgQ(OSResourceSingleton::getInstance().getQHandle(app::OSResourceSingleton::Id::ControlTask))
{}

void Cloud::run() {
    Msg msg = {EventId::Invalid, nullptr, 0U};

    Wifi wifi(wifi_status_callback);
    wifi.connect();

    for (;;) {
        m_rxMsgQ.get(&msg);
        handle(msg);
    }
}

void Cloud::handle(const app::Msg& msg) {
    switch(msg.ev) {
    case EventId::WifiConnected:
        m_controlMsgQ.set(msg); // forward it to control.
        connectToCloud();
        break;
    case EventId::WifiDisconnected:
        m_controlMsgQ.set(msg); // forward it to control.
        // TODO: error handling
        break;
    case EventId::CloudConnected:
        m_controlMsgQ.set(msg); // forward it to control.
        break;
    case EventId::CloudDisconnected:
        m_controlMsgQ.set(msg); // forward it to control.
        // TODO: error handling.
        break;
    default:
        break;
    }
}

void Cloud::connectToCloud() {
    esp_mqtt_client_config_t mqtt_cfg = {};
    mqtt_cfg.broker.address.uri = "mqtts://a38ojawji2af21-ats.iot.ap-southeast-1.amazonaws.com";
    mqtt_cfg.broker.verification.certificate = (const char*)server_cert_pem_start;
    mqtt_cfg.credentials.authentication.certificate = (const char*)client_cert_pem_start;
    mqtt_cfg.credentials.authentication.key = (const char*)client_key_pem_start;

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, MQTT_EVENT_ANY, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}

