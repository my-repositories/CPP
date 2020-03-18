# Download https://cmake.org/download/
cmake_minimum_required(VERSION 3.15)

set(projectName libqa)
project(${projectName})
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)


include_directories(app/inc deps/inc lib/inc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(libraryName testlib)
file(GLOB librarySources "lib/src/*.cpp")
add_library(${libraryName} STATIC ${librarySources})

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/lib)
file(GLOB appSources "app/src/*.cpp")
add_executable(${projectName} ${appSources})
target_link_libraries(${projectName} ${libraryName})
