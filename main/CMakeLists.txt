# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS
    "main.c"
    "../app/App.cpp"
    "../app/MsgInbox.cpp"
    "../app/SysResMgmtSingleton.cpp"
    "../app/control/Control.cpp"
    "../app/led/LED.cpp"
    "../app/cloud/Cloud.cpp"
    "../app/audioml/AudioML.cpp"
    "../app/audioml/hello-world/constants.cc"
    "../app/audioml/hello-world/main_functions.cc"
    "../app/audioml/hello-world/model.cc"
    "../app/audioml/hello-world/output_handler.cc"
    "../platform/esp/os/OSWrapper.cpp"
    "../platform/esp/os/OSWrapper.cpp"
    "../platform/esp/peripheral/gpio/GPIO.cpp"
    "../platform/esp/com/wifi/Wifi.cpp"
    "../platform/esp/com/mqtt/MqttClient.cpp"
)
set(COMPONENT_ADD_INCLUDEDIRS
    "../"
    "../app"
    "../platform/esp"
)

register_component()
