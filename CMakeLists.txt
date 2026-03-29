cmake_minimum_required(VERSION 3.28)
project(speis-inveiders)

set(BUILD_SHARED_LIBS OFF)
set(SDL3_DIR libs/edl/libs/SDL3-3.4.0/cmake/)
set(SDL3_image_DIR libs/edl/libs/SDL3_image-3.4.0/cmake)
set(SDL3_ttf_DIR libs/edl/libs/SDL3_ttf-3.2.2/cmake)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(libs/edl/include)
include_directories(libs/edl/libs/SDL3-3.4.0)

# Link statico per runtime GCC
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wwrite-strings -static-libgcc -static-libstdc++ -static")

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(speis-inveiders src/main.cpp libs/edl/src/easy_sdl.cpp
        src/main_menu.cpp
        src/printGame.cpp
        src/utility.cpp
        src/player.cpp
        src/alien.cpp
        src/pause_menu.cpp
        src/gameOver.cpp
        src/reset_status_play.cpp
        src/levelUP.cpp
)

target_link_libraries(speis-inveiders
        SDL3::SDL3-shared
        SDL3_ttf::SDL3_ttf-shared
        SDL3_image::SDL3_image-shared
)


