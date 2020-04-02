cmake_minimum_required( VERSION 3.0 )

project( RaspiRemoteCam )

include_directories(libs/ControlSystem)

add_subdirectory( libs/ControlSystem )
add_subdirectory( libs/googletest )
add_subdirectory( src )
add_subdirectory( tst )

