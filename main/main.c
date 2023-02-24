#include "app/App.h"

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

void app_main(void) {
    APP_Init();

    // To tickle watchdog.
    while (1) {
        vTaskDelay(1000U / portTICK_PERIOD_MS);
    }
}
