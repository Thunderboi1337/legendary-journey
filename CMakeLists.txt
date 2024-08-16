cmake_minimum_required(VERSION 3.14)
project(MEMETRIS)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

if (MSVC)
    add_compile_options(/wd4068) # Disable unknown pragma warning. https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4068
    add_compile_options(/wd4996) # Disable unsecure function warnings (e.g., sprintf())
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fpermissive)
endif()

# Dependencies
include(FetchContent)

# Raylib
set(RAYLIB_VERSION 4.0.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(RAYGUI_VERSION 3.2)
find_package(raygui ${RAYGUI_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raygui_FOUND) # If there's none, fetch and build raygui
  include(FetchContent)
  FetchContent_Declare(
    raygui
    URL https://github.com/raysan5/raygui/archive/refs/tags/${RAYGUI_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raygui)
  if (NOT raygui_POPULATED) # Have we downloaded raygui yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raygui)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raygui_SOURCE_DIR}/projects/CMake ${raygui_BINARY_DIR})
  endif()
endif()

# nlohmann/json
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Add your libraries
add_library(guylib guy.cpp)
add_library(worldlib world.cpp)
add_library(objectslib objects.cpp)
add_library(enemieslib enemy.cpp)
add_library(attacklib attack.cpp)
add_library(healthlib health.cpp)

# Ensure the include directories are set for tileson
include_directories(ThirdParty/tileson/include)
add_library(tylesonlib ThirdParty/tileson/src/raylib-tileson.cpp)

# Create the executable
add_executable(main main.cpp)

# Include directories for json
target_include_directories(worldlib PRIVATE ${json_SOURCE_DIR}/include . ThirdParty/raylib-cpp/include ThirdParty/tileson/include )
target_include_directories(objectslib PRIVATE ${json_SOURCE_DIR}/include )
# Link libraries to the main executable
target_link_libraries(main raylib raygui nlohmann_json::nlohmann_json guylib worldlib tylesonlib  objectslib enemieslib attacklib healthlib)  

# Apply strict compile flags only to the main executable
target_compile_options(main PRIVATE ${STRICT_COMPILE_FLAGS})

# Make sure Raylib is built before linking
add_dependencies(main raylib)

# Define the path to your maps.json file
set(MAPS_JSON_PATH ${CMAKE_CURRENT_SOURCE_DIR}/maps/*.json)

# Copy maps.json to the target directory after building the executable
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${MAPS_JSON_PATH} $<TARGET_FILE_DIR:main>
)

set(TILE_IMAGE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sprites/*.png)
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${TILE_IMAGE_PATH} $<TARGET_FILE_DIR:main>)
