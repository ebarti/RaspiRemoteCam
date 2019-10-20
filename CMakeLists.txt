cmake_minimum_required( VERSION 3.0 )

project( RaspiRemoteCam )


# flags

# include files
include_directories( ./include ./src/core ./libs/ControlSystem/include)

add_subdirectory( ./libs/ControlSystem )

# target
add_executable( TheProgram ./src/core/RaspiRemoteCam.cpp )


#libs
target_link_libraries( TheProgram ControlSystem )