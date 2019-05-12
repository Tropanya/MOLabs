cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
#===============================================================================
project(MOLabs)
#===============================================================================
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4")
#===============================================================================
add_subdirectory(SimplexMethod)
add_subdirectory(GomoryAlgorithm)
add_subdirectory(BranchAndBoundMethod)
add_subdirectory(Launcher)
add_subdirectory(3rdparty)
#===============================================================================