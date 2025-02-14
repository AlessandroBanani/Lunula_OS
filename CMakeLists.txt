cmake_minimum_required(VERSION 3.13)

# Nazwa projektu
project(RP2040_IoT_System)

# Ustawienie zmiennej środowiskowej dla PICO SDK
if (NOT DEFINED PICO_SDK_PATH)
    set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}")
endif ()

# Dołączenie Pico SDK
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

# Tworzenie projektu
add_executable(main 
    src/main.c
)

# Dodanie biblioteki Pico SDK
target_link_libraries(main pico_stdlib pico_cyw43_arch_lwip pico_multicore)

# Konfiguracja standardowych bibliotek Pico
pico_add_extra_outputs(main)
