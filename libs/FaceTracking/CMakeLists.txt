cmake_minimum_required( VERSION 3.0 )

project ( lib_FaceTracking )
#add open cv libraries for image processing
find_package(OpenCV REQUIRED)
include_directories( ./include ./src)

#target

add_library (FaceTracking SHARED ./src/FaceTracking.cpp )

#link with openCv
target_link_libraries( FaceTracking ${OpenCV_LIBS})