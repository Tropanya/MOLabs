project(mpir)
#===============================================================================
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
#===============================================================================
add_library(${PROJECT_NAME} INTERFACE)
#===============================================================================
target_link_libraries(${PROJECT_NAME}
INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/lib/mpir.lib"
)
#===============================================================================
target_include_directories(${PROJECT_NAME}
INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
#===============================================================================
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/bin/mpir.dll"
     DESTINATION "${Launcher_BINARY_DIR}/Debug")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/bin/mpir.dll"
     DESTINATION "${Launcher_BINARY_DIR}/Release")
#===============================================================================