### This is a template for building targets with simgrid
cmake_minimum_required(VERSION 2.8)

### Need to set rc ccompiler before enable language
if(WIN32)
    SET(CMAKE_RC_COMPILER "windres")
endif(WIN32)

project(HelloWorld C)
set(CMAKE_C_FLAGS "" CACHE TYPE INTERNAL FORCE)
set(CMAKE_EXE_LINKER_FLAGS "" CACHE TYPE INTERNAL FORCE)

###############################
# Test the build dependencies #
###############################
include(FindPCRE.cmake)
message(STATUS "Looking for lib Simgrid")
if("$ENV{SIMGRID_ROOT}" STREQUAL "")
    message(STATUS "Looking for lib Simgrid - Not found")
    message(FATAL_ERROR "Simgrid not found, reinstall it or set SIMGRID_ROOT")
else("$ENV{SIMGRID_ROOT}" STREQUAL "")
    link_directories($ENV{SIMGRID_ROOT}/lib)
    include_directories($ENV{SIMGRID_ROOT}/include)
    include_directories($ENV{SIMGRID_ROOT}/src)
    include_directories($ENV{SIMGRID_ROOT}/src/include)
    add_library(libsimgrid STATIC IMPORTED)
    message(STATUS "Looking for lib Simgrid - found") 
endif("$ENV{SIMGRID_ROOT}" STREQUAL "")

###########
# TARGETS #
###########

#########################
# add_executable        #
#    args1 target name  #
#    args2 sources      #
#########################
add_executable(HelloWorld HelloWorld.c)
# Any targets need to be linked with simgrid and pcre
target_link_libraries(HelloWorld simgrid pcre) 