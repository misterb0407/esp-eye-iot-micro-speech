# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS ./platform/esp/ml/ ./app/audioml/micro_speech/)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(aiot-esp32)

# Certificates to connect to MQTT
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "app/cloud/certs/server.crt" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "app/cloud/certs/client.crt" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "app/cloud/certs/client.key" TEXT)
