cmake_minimum_required( VERSION 3.0 )

project( lib_ControlSystem)

include_directories( ./include./libs/SG90/include ./libs/FaceTrackingCamera/include)

add_subdirectory( ./libs/SG90 )
add_subdirectory( ./libs/FaceTrackingCamera )

add_library (ControlSystem SHARED ./src/ControlSystem.cpp )

target_link_libraries( ControlSystem SG90 )
target_link_libraries( ControlSystem FaceTrackingCamera )

