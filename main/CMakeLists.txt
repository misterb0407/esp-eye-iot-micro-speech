# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS
    "main.c"
    "../app/App.cpp"
    "../platform/esp/os/OSWrapper.cpp"
)
set(COMPONENT_ADD_INCLUDEDIRS
    "../"
    "../platform/esp"
)

register_component()
