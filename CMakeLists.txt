cmake_minimum_required(VERSION 3.12)
# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)

project(rp2040-ctf C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

if (TARGET tinyusb_device)
    add_executable(ctf src/main.c)

    # pull in common dependencies
    target_link_libraries(ctf pico_stdlib hardware_adc)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(ctf 1)
    pico_enable_stdio_uart(ctf 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(ctf)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building ctf because TinyUSB submodule is not initialized in the SDK")
endif()
add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()
