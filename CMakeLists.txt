cmake_minimum_required( VERSION 3.8 )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project( RaspiRemoteCam )

include_directories(libs/ControlSystem)

add_subdirectory( libs/ControlSystem )
add_subdirectory( libs/googletest )
add_subdirectory( src )
add_subdirectory( tst )

