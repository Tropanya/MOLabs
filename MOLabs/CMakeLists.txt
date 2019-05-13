project(MOLabs)
#===============================================================================
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#===============================================================================
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
#===============================================================================
target_link_libraries(${PROJECT_NAME}
PUBLIC
  SimplexMethod
)
#===============================================================================
target_include_directories(${PROJECT_NAME}
PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
#===============================================================================