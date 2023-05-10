// Library includes
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

// Platform includes.
#include "log/Log.h"

// Project includes.
#include "Wifi.h"

namespace {
std::function<void(bool)> g_callback = nullptr;

// Wifi event handler (callback).
void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        log("Connecting to wifi ssid %s\n", CONFIG_ESP_WIFI_SSID);
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        log("ERROR: Not able to connect to wifi %s\n", CONFIG_ESP_WIFI_SSID);
        if (g_callback != nullptr) {
            g_callback(false);
        }
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        log("wifi AP ip addr:" IPSTR, IP2STR(&event->ip_info.ip));
        log("\n");
        if (g_callback != nullptr) {
            g_callback(true);
        }
    }
    else { /* Do nothing*/}
}
}

Wifi::Wifi(std::function<void(bool)> callback):
    m_callback(callback)
{
    g_callback = m_callback;
}



bool Wifi::connect() {
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Init wifi
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,ESP_EVENT_ANY_ID, &event_handler, NULL, &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL, &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = CONFIG_ESP_WIFI_SSID,
            .password = CONFIG_ESP_WIFI_PASSWORD,
            .scan_method = WIFI_FAST_SCAN, // options: WIFI_FAST_SCAN, WIFI_ALL_CHANNEL_SCAN
            .bssid_set = 0, // Does not need to set MAC address of the target AP,
            .bssid = {0},
            .channel = 0, // options: 1-13, 0 is unknown,
            .listen_interval = 0, // 0 is for default,
            .sort_method = WIFI_CONNECT_AP_BY_SIGNAL, // options: WIFI_CONNECT_AP_BY_SIGNAL,  WIFI_CONNECT_AP_BY_SECURITY
            .threshold = {
                .rssi = 0,
                .authmode = WIFI_AUTH_WPA2_PSK
            },
            .pmf_cfg = {}, // let it default
            .rm_enabled = 0,
            .btm_enabled = 0,
            .mbo_enabled = 0,
            .ft_enabled = 0,
            .owe_enabled = 0,
            .transition_disable = 0,
            .reserved = 0,
            .sae_pwe_h2e =  WPA3_SAE_PWE_UNSPECIFIED,
            .failure_retry_cnt = 3
        }
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    return true;
}

