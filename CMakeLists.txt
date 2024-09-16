cmake_minimum_required(VERSION 3.28)
project(MiniNebula LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(SDLIMAGE_BUILD_SHARED_LIBS ON)
set(SDLMIXER_BUILD_SHARED_LIBS ON)
set(SDL_SHARED ON)
set(SDL_STATIC OFF)

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
    set(CMAKE_BUILD_)
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

set(TARGET_COMPILED_DIR ${CMAKE_BINARY_DIR}/compiled)

#macro(copy_subproject_target target)
#    add_custom_command(TARGET ${target} POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E make_directory ${TARGET_COMPILED_DIR}
#            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${target}> ${TARGET_COMPILED_DIR}
#            COMMENT "Copying ${target} files to output directory"
#    )
#endmacro()

#copy_subproject_target(MiniNebula)
#copy_subproject_target(${sdl3_image_target_name})
#copy_subproject_target(${sdl3_mixer_target_name})
#if ( SDL_SHARED )
#    copy_subproject_target(SDL3::SDL3-shared)
#endif()
set(APP_SHARED_LIB_PREFIX_NAME "lib")
set(APP_SHARED_LIB_SUFFIX_NAME ".so")
set(APP_SUFFIX_NAME "")


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(APP_SHARED_LIB_PREFIX_NAME "")
    set(APP_SHARED_LIB_SUFFIX_NAME ".dll")
    set(APP_PREFIX_NAME ".exe")
endif ()


add_custom_command(TARGET MiniNebula POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${TARGET_COMPILED_DIR}/res/
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/MiniNebula${APP_PREFIX_NAME} ${TARGET_COMPILED_DIR}/MiniNebula${APP_PREFIX_NAME}

        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ext/sdl/${APP_SHARED_LIB_PREFIX_NAME}SDL3${APP_SHARED_LIB_SUFFIX_NAME} ${TARGET_COMPILED_DIR}/${APP_SHARED_LIB_PREFIX_NAME}SDL3${APP_SHARED_LIB_SUFFIX_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ext/sdl_image/${APP_SHARED_LIB_PREFIX_NAME}SDL3_image${APP_SHARED_LIB_SUFFIX_NAME} ${TARGET_COMPILED_DIR}/${APP_SHARED_LIB_PREFIX_NAME}SDL3_image${APP_SHARED_LIB_SUFFIX_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ext/sdl_mixer/${APP_SHARED_LIB_PREFIX_NAME}SDL3_mixer${APP_SHARED_LIB_SUFFIX_NAME} ${TARGET_COMPILED_DIR}/${APP_SHARED_LIB_PREFIX_NAME}SDL3_mixer${APP_SHARED_LIB_SUFFIX_NAME}
)


#execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${TARGET_COMPILED_DIR}/res/)
#execute_process( COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/MiniNebula${APP_PREFIX_NAME} ${TARGET_COMPILED_DIR}/MiniNebula${APP_PREFIX_NAME})
#
#execute_process( COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ext/sdl/SDL3${APP_SHARED_LIB_PREFIX_NAME} ${TARGET_COMPILED_DIR}/SDL3${APP_SHARED_LIB_PREFIX_NAME})
#execute_process( COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ext/sdl_image/SDL3_image${APP_SHARED_LIB_PREFIX_NAME} ${TARGET_COMPILED_DIR}/SDL3_image${APP_SHARED_LIB_PREFIX_NAME})
#execute_process( COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ext/sdl_mixer/SDL3_mixer${APP_SHARED_LIB_PREFIX_NAME} ${TARGET_COMPILED_DIR}/SDL3_mixer${APP_SHARED_LIB_PREFIX_NAME})