cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(RP2040_IoT_System C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(RP2040_IoT_System
    main.c
    bootloader.S
)

# Linkowanie bibliotek Pico
target_link_libraries(RP2040_IoT_System pico_stdlib pico_cyw43_arch_lwip_threadsafe_background lwip)

# Ustawienia pliku UF2 (do flashowania)
pico_add_extra_outputs(RP2040_IoT_System)
