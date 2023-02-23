// Standard includes.
#include <stdio.h>

// Project includes.
#include "App.h"
#include "log/Log.h"
#include "os/OSWrapper.h"

void APP_Start() {
    // TODO
    int i = 0;
    while (1) {
        log("[%d] Hello world!\n", i);
        i++;
        platform::os::OSWrapper::delay(5000);
    }
}