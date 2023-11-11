cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(rp2040ctf C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(ctf src/main.c)
# target_include_directories(ctf PRIVATE include/)

#target_link_libraries(gamecon PRIVATE pico_stdlib tinyusb_device tinyusb_board hardware_pwm)
target_link_libraries(ctf PRIVATE pico_stdlib hardware_pwm)
pico_add_extra_outputs(ctf)

