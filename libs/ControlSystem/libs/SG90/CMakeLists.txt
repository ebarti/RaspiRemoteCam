cmake_minimum_required( VERSION 3.0 )

project( lib_SG90 )

# flags

# include files
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include ./src ${CMAKE_CURRENT_SOURCE_DIR}/libs/pigpio/include )

add_library(pigpio SHARED IMPORTED)
set_property(TARGET pigpio PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/pigpio/libpigpio.so)


# target

add_library(SG90 SHARED ./src/SG90.cpp)

target_link_libraries( SG90 pigpio )
# install(TARGETS SG90 DESTINATION ${CMAKE_SOURCE_DIR})
# install(TARGETS SG90.h DESTINATION lib)