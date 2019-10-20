cmake_minimum_required( VERSION 3.0 )

project( lib_ControlSystem)

include_directories( ./include ./src ./libs/pigpio/include ./libs/SG90/include ./libs/FaceTrackingCamera/include)

add_subdirectory( ./libs/SG90 )
add_subdirectory( ./libs/FaceTrackingCamera )

add_library (ControlSystem SHARED ./src/ControlSystem.cpp )

add_library(pigpio SHARED IMPORTED)
set_property(TARGET pigpio PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/pigpio/libpigpio.so)
target_link_libraries( ControlSystem pigpio )
target_link_libraries( ControlSystem SG90 )
target_link_libraries( ControlSystem FaceTrackingCamera )

