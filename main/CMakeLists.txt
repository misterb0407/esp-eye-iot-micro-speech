# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS
    "main.c"
    "../app/App.cpp"
    "../app/OSResourceSingleton.cpp"
    "../app/MsgQ.cpp"
    "../app/led/LED.cpp"
    "../app/control/Control.cpp"
    "../app/cloud/Cloud.cpp"
    "../app/audioml/AudioML.cpp"
    "../platform/esp/os/OSWrapper.cpp"
)
set(COMPONENT_ADD_INCLUDEDIRS
    "../"
    "../app"
    "../platform/esp"
)

register_component()
