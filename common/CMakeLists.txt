cmake_minimum_required(VERSION 3.0)

project(common)

message(STATUS "Build type : ${CMAKE_BUILD_TYPE}")

# Configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(DEFINED CMAKE_BUILD_TYPE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS  ${CMAKE_CONFIGURATION_TYPES})
endif()

# no note displayed
set(CMAKE_CXX_FLAGS "-Wfatal-errors")

# set C_SOURCES variable with all C files
file(GLOB_RECURSE C_SOURCES src/*.c)

# add include directory
include_directories(include)

# create library
add_library(${PROJECT_NAME} SHARED ${C_SOURCES})

# strip target
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)
