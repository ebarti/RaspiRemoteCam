cmake_minimum_required( VERSION 3.15 )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
project (FaceTrackingCamera LANGUAGES CXX VERSION 1.0.0)

#add open cv libraries for image processing
find_package(OpenCV REQUIRED)
if(${OpenCV_FOUND})
	message(STATUS "Found OpenCV for FaceTrackingCamera build")
else(${OpenCV_FOUND})
	message(FATAL_ERROR "Could not locate OpenCV lib for FaceTrackingCamera build")
endif(${OpenCV_FOUND})


#to help cmake find raspicam
set(raspicam_DIR "/usr/local/lib/cmake")

find_package(raspicam REQUIRED)

if(${raspicam_FOUND})
	message(STATUS "Found raspicam for FaceTrackingCamera build")
else(${raspicam_FOUND})
	message(FATAL_ERROR "Could not locate raspicam lib for FaceTrackingCamera build")
endif(${raspicam_FOUND})

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library (${PROJECT_NAME} SHARED ${HEADER_FILES} ${CPP_FILES})

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ${raspicam_CV_LIBS})

target_include_directories( ${PROJECT_NAME}
	PUBLIC
		${OpenCV_INCLUDE_DIRS}
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${raspicam_INCLUDE_DIRS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
			CXX_STANDARD 14
			CXX_STANDARD_REQUIRED ON
			EXPORT_PACKAGE_REGISTRY ON
)
