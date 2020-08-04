cmake_minimum_required( VERSION 3.15 )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "lib_")

project( RaspiRemoteCam VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(extern/googletest)
add_subdirectory(extern/pigpio)
add_subdirectory( libs )
add_subdirectory( src )

option(BUILD_TESTS "Build associated tests" ON)
if(BUILD_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()




