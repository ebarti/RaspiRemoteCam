cmake_minimum_required( VERSION 3.0 )

project ( lib_FaceTrackingCamera )

#to help cmake find raspicam
find_package(raspicam REQUIRED)
#add open cv libraries for image processing
find_package(OpenCV)

include_directories( ./include ./src)

#target

add_library (FaceTrackingCamera SHARED ./src/FaceTrackingCamera.cpp )

#link with openCv
target_link_libraries( FaceTrackingCamera ${OpenCV_LIBS})

#link with raspicam
target_link_libraries( FaceTrackingCamera ${raspicam_CV_LIBS})