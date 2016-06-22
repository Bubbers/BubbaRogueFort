
# Files to compile
set(GAME_SOURCE_FILES main.cpp
        controls.h)

add_subdirectory(cameras)
add_subdirectory(components)
add_subdirectory(level)
add_subdirectory(ui)
add_subdirectory(scenes)
add_subdirectory(logic)

# Define the executable
INCLUDE_DIRECTORIES(src)
set(EXECUTABLE_NAME BubbaRogueFort)
add_executable(${EXECUTABLE_NAME} ${GAME_SOURCE_FILES} ${GAME_HEADER_FILES})
target_link_libraries(${EXECUTABLE_NAME} LINK_PUBLIC Bubba3D)


