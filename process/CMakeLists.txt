cmake_minimum_required(VERSION 3.0)

project(process)

message(STATUS "Build type : ${CMAKE_BUILD_TYPE}")

# Configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(DEFINED CMAKE_BUILD_TYPE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS  ${CMAKE_CONFIGURATION_TYPES})
endif()

# no note displayed
set(CMAKE_CXX_FLAGS "-Wfatal-errors")

file(GLOB_RECURSE C_SOURCES src/*.c)

include_directories(../common/include include)

add_executable(${PROJECT_NAME} ${C_SOURCES})

target_link_libraries(${PROJECT_NAME} common)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)