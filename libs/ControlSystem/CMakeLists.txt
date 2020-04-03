cmake_minimum_required( VERSION 3.8 )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project( lib_ControlSystem)

add_library (lib_ControlSystem SHARED ./src/ControlSystem.cpp )

add_library (ControlSystem::library ALIAS lib_ControlSystem)

target_include_directories(lib_ControlSystem
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include 
		${CMAKE_CURRENT_SOURCE_DIR}/src 
		${CMAKE_CURRENT_SOURCE_DIR}/libs/SG90/include 
		${CMAKE_CURRENT_SOURCE_DIR}/libs/FaceTrackingCamera/include )


add_subdirectory( ./libs/SG90 )
add_subdirectory( ./libs/FaceTrackingCamera )


target_link_libraries( lib_ControlSystem lib_SG90 )
target_link_libraries( lib_ControlSystem lib_FaceTrackingCamera )

