cmake_minimum_required( VERSION 3.0 )

project( RaspiRemoteCam )

include_directories(src)

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/libs/ControlSystem )

add_executable( Exec_RaspiRemoteCam ${CMAKE_CURRENT_SOURCE_DIR}/src/core/RaspiRemoteCam.cpp )

# flags

# include files
target_include_directories(Exec_RaspiRemoteCam
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include 
		${CMAKE_CURRENT_SOURCE_DIR}/src/core 
		${CMAKE_CURRENT_SOURCE_DIR}/libs/ControlSystem/include 
)



# target



#libs
target_link_libraries( Exec_RaspiRemoteCam lib_ControlSystem )