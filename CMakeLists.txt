cmake_minimum_required(VERSION 3.28)
project(MiniNebula LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(SDLIMAGE_BUILD_SHARED_LIBS ON)
set(SDLMIXER_BUILD_SHARED_LIBS ON)


add_subdirectory(ext/sdl)       # RENDERER
add_subdirectory(ext/sdl_image) # IMAGE
add_subdirectory(ext/sdl_mixer) # AUDIO
add_subdirectory(ext/json)      # nlohmann_json

include_directories(
        inc
        ext/sdl3/include
        ext/sdl_image/include
        ext/sdl_mixer/include
        ext/stb
        ext/json/include
)

link_libraries(
        SDL3::SDL3-shared
        SDL3_mixer-shared
        SDL3_image-shared

        nlohmann_json
)

set(__SOURCE_FILE
        src/main.cpp
        src/App.cpp
        src/Sprite.cpp
        src/Timer.cpp
        src/ResourceManager.cpp
        src/SceneManager.cpp
        src/CollisionBox.cpp
        src/CollisionManager.cpp
)

set(__DEBUG_FILE

)

set(__TEST_FILE

)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(MiniNebula
            ${__SOURCE_FILE}
            ${__DEBUG_FILE}
            ${__TEST_FILE}
    )
else(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(MiniNebula
            ${__SOURCE_FILE}
    )
endif()

execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res/)
execute_process( COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ext/sdl/SDL3.dll ${CMAKE_BINARY_DIR}/SDL3.dll)
execute_process( COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ext/sdl_image/SDL3_image.dll ${CMAKE_BINARY_DIR}/SDL3_image.dll)
execute_process( COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ext/sdl_mixer/SDL3_mixer.dll ${CMAKE_BINARY_DIR}/SDL3_mixer.dll)