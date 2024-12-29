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
    )

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")



target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} nlohmann_json::nlohmann_json)




