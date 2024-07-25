cmake_minimum_required(VERSION 3.14)
project(MEMETRIS)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Dependencies
include(FetchContent)

# Raylib
set(RAYLIB_VERSION 4.5.0)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
set(RAYLIB_BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

# nlohmann/json
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)
FetchContent_MakeAvailable(json)


# Add your libraries
add_library(guylib guy.cpp)
add_library(gridlib grid.cpp)

# Create the executable
add_executable(main main.cpp)

# Include directories for json
target_include_directories(gridlib PRIVATE ${json_SOURCE_DIR}/include)
target_include_directories(main PRIVATE ${json_SOURCE_DIR}/include)

# Link libraries to the main executable
target_link_libraries(main raylib guylib gridlib nlohmann_json::nlohmann_json)

# Apply strict compile flags only to the main executable
target_compile_options(main PRIVATE ${STRICT_COMPILE_FLAGS})

# Make sure Raylib is built before linking
add_dependencies(main raylib)

set(TILE_IMAGE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sprites/)
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${TILE_IMAGE_PATH} $<TARGET_FILE_DIR:main>)
