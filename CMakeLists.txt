cmake_minimum_required( VERSION 3.15 )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project( RaspiRemoteCam )

include_directories(libs/ControlSystem)

add_subdirectory( libs/ControlSystem )
add_subdirectory( libs/googletest )
add_subdirectory( src )

option(PACKAGE_TESTS "Build the tests" ON)
#if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
#endif()

