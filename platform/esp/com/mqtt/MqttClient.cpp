// Library includes
#include "mqtt_client.h"

// Platform includes.
#include "log/Log.h"

// Project includes.
#include "MqttClient.h"

// This must match with the filename set in CMakeLists.txt with pattern '_binary_<file_name_extention>_<start/end>'
extern const uint8_t server_cert_pem_start[] asm("_binary_server_crt_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_server_crt_end");
extern const uint8_t client_cert_pem_start[] asm("_binary_client_crt_start");
extern const uint8_t client_cert_pem_end[] asm("_binary_client_crt_end");
extern const uint8_t client_key_pem_start[] asm("_binary_client_key_start");
extern const uint8_t client_key_pem_end[] asm("_binary_client_key_end");

namespace {
std::function<void(bool)> g_callback = nullptr;
esp_mqtt_client_handle_t g_client;

static void log_error_if_nonzero(const char *message, int error_code) {
    if (error_code != 0) {
        log("Last error %s: 0x%x", message, error_code);
    }
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;

    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            if (g_callback != nullptr) {
                g_callback(true);
            }
            break;
        case MQTT_EVENT_DISCONNECTED:
            if (g_callback != nullptr) {
                g_callback(false);
            }
            break;
        case MQTT_EVENT_SUBSCRIBED:
            log("MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
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

MqttClient::MqttClient(std::function<void(bool)> callback):
    m_callback(callback)
{
    g_callback = m_callback;
}



bool MqttClient::connect() {
    esp_mqtt_client_config_t mqtt_cfg = {};
    mqtt_cfg.broker.address.uri = "mqtts://a38ojawji2af21-ats.iot.ap-southeast-1.amazonaws.com";
    mqtt_cfg.broker.verification.certificate = (const char*)server_cert_pem_start;
    mqtt_cfg.credentials.authentication.certificate = (const char*)client_cert_pem_start;
    mqtt_cfg.credentials.authentication.key = (const char*)client_key_pem_start;

    g_client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(g_client, MQTT_EVENT_ANY, mqtt_event_handler, NULL);
    esp_mqtt_client_start(g_client);

    return true;
}

void MqttClient::subscribe(const char* topic) {

    (void)esp_mqtt_client_subscribe(g_client, topic, 1);
}

void MqttClient::unsubscribe(const char* topic) {
    (void)esp_mqtt_client_unsubscribe(g_client, topic);

}

void MqttClient::publish(const char* topic, const char* data) {
    (void)esp_mqtt_client_publish(g_client, topic, data, 0, 0, 0);

}
