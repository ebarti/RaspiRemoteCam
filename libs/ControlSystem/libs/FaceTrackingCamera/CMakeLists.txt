cmake_minimum_required( VERSION 3.0 )

project ( lib_FaceTrackingCamera )

add_library (lib_FaceTrackingCamera SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/FaceTrackingCamera.cpp )

add_library (FaceTrackingCamera::library ALIAS lib_FaceTrackingCamera)

#to help cmake find raspicam
find_package(raspicam REQUIRED)
#add open cv libraries for image processing
find_package(OpenCV)

target_include_directories( lib_FaceTrackingCamera
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include 
		${CMAKE_CURRENT_SOURCE_DIR}/src 
)


#link with openCv
target_link_libraries( lib_FaceTrackingCamera ${OpenCV_LIBS})

#link with raspicam
target_link_libraries( lib_FaceTrackingCamera ${raspicam_CV_LIBS})