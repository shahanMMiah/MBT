cmake_minimum_required(VERSION 3.0.0)
project(MBT)
include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2 # Use the latest version tag
)
FetchContent_MakeAvailable(json)

SET(SOURCES 
    src/src.cpp
    src/graphics.cpp
    src/color.cpp
    src/vector2d.cpp
    src/line2d.cpp
    src/shape.cpp
    src/rectangle.cpp
    src/player.cpp
    src/controller.cpp
    src/wall.cpp
    src/game.cpp
    src/bubble.cpp
    src/object.cpp
    src/needle.cpp
    src/door.cpp
    src/level.cpp
    src/dialog.cpp
    )

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} /usr/include/SDL2)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} nlohmann_json::nlohmann_json SDL2_ttf SDL2_image)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

set(ASSETS_PATH ${CMAKE_SOURCE_DIR}/assets)
set(FONT_PATH ${ASSETS_PATH}/fonts/Vanilla.ttf)
set(PRINCESS_SPRITE_PATH ${ASSETS_PATH}/sprites/princess_sprite.png)


target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_PATH="${ASSETS_PATH}" FONT_PATH="${FONT_PATH}" PRINCESS_SPRITE_PATH="${PRINCESS_SPRITE_PATH}")
