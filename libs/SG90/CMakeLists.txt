cmake_minimum_required( VERSION 3.15 )
project( SG90 VERSION 1.0.0 LANGUAGES CXX)

find_package(pigpio REQUIRED)

if(${pigpio_FOUND})
	message(STATUS "Found pigpio for SG90 build")
else(${pigpio_FOUND})
	message(FATAL_ERROR "Could not locate pigpio lib for SG90 build")
endif(${pigpio_FOUND})

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${CPP_FILES})
target_link_libraries( ${PROJECT_NAME} pigpio )

target_include_directories(${PROJECT_NAME}
	PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>  # <prefix>/include/mylib
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${pigpio_INCLUDE_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
			CXX_STANDARD 14
			CXX_STANDARD_REQUIRED ON
			EXPORT_PACKAGE_REGISTRY ON
)

