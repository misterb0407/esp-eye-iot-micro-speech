// Standard includes.
#include <stdio.h>

// Project includes.
#include "App.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void APP_Start() {
    // TODO
    int i = 0;
    while (1) {
        printf("[%d] Hello world!\n", i);
        i++;
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}