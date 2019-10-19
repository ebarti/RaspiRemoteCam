cmake_minimum_required( VERSION 3.0 )

project ( lib_FaceTracking )
#add open cv libraries for image processing

#to help cmake find raspicam
#SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /home/pi/raspicam/build)
find_package(raspicam REQUIRED)
find_package(OpenCV REQUIRED)
include_directories( ./include ./src)

#target

add_library (FaceTracking SHARED ./src/FaceTracking.cpp )

#link with openCv
target_link_libraries( FaceTracking ${OpenCV_LIBS})

#link with raspicam
target_link_libraries( FaceTracking ${raspicam_LIBS})