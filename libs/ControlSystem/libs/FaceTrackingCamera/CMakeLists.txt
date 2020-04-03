cmake_minimum_required( VERSION 3.8 )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project ( lib_FaceTrackingCamera )

set(raspicam_DIR "/usr/local/lib/cmake")

#add open cv libraries for image processing
find_package(OpenCV REQUIRED)

#to help cmake find raspicam
find_package(raspicam REQUIRED)



include_directories(${OpenCV_INCLUDE_DIRS})
add_library (lib_FaceTrackingCamera SHARED ${CMAKE_CURRENT_SOURCE_DIR}/include/FaceTrackingCamera.h ${CMAKE_CURRENT_SOURCE_DIR}/src/FaceTrackingCamera.cpp )

add_library (FaceTrackingCamera::library ALIAS lib_FaceTrackingCamera)



target_include_directories( lib_FaceTrackingCamera
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include 
		${CMAKE_CURRENT_SOURCE_DIR}/src
)


#link with raspicam
target_link_libraries( lib_FaceTrackingCamera ${OpenCV_LIBS} ${raspicam_CV_LIBS})