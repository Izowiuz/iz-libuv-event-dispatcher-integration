cmake_minimum_required(VERSION 3.20)
include(FetchContent)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(iz-libuv-event-dispatcher-integration)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(libuv CONFIG REQUIRED)

FetchContent_Declare(
    iz-libuv-event-dispatcher
    GIT_REPOSITORY https://github.com/Izowiuz/iz-libuv-event-dispatcher
    GIT_TAG master
)
FetchContent_MakeAvailable(iz-libuv-event-dispatcher)

add_executable(
    iz-libuv-event-dispatcher-integration
    "src/main.cpp"
)

target_sources(
    iz-libuv-event-dispatcher-integration
PRIVATE
    "src/main.cpp"
    "${iz-libuv-event-dispatcher_SOURCE_DIR}/LibUvEventDispatcher.h"
    "${iz-libuv-event-dispatcher_SOURCE_DIR}/LibUvEventDispatcher.cpp"
)

set_property(
TARGET
    iz-libuv-event-dispatcher-integration
PROPERTY
    CXX_STANDARD 20
)

set_property(
TARGET
    iz-libuv-event-dispatcher-integration
PROPERTY
    AUTOMOC ON
)

target_include_directories(
    iz-libuv-event-dispatcher-integration
PRIVATE
    "src"
    "${iz-libuv-event-dispatcher_SOURCE_DIR}"
)

target_link_libraries(
    iz-libuv-event-dispatcher-integration
PRIVATE
    Qt6::Core
    $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>
)
