cmake_minimum_required(VERSION 3.13)

# Nazwa projektu
project(Lunula_OS)

# Sprawdzenie i ustawienie PICO_SDK_PATH
if (NOT DEFINED PICO_SDK_PATH)
    set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}")
endif ()

# Dołączenie Pico SDK
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

# Inicjalizacja SDK
pico_sdk_init()

# Tworzenie projektu
add_executable(main 
    src/main.c
)

# Dodanie bibliotek Pico SDK
target_link_libraries(main pico_stdlib pico_cyw43_arch_lwip pico_multicore)

# Wygenerowanie plików .uf2 i binarnych
pico_add_extra_outputs(main)
