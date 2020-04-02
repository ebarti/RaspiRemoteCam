cmake_minimum_required( VERSION 3.0 )

enable_testing()

set(BINARY tst_${CMAKE_PROJECT_NAME})

#source files
set(test_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tstCamera.cpp)

################
# Define the
add_executable(${BINARY} ${test_SOURCES})

target_include_directories(${BINARY} 
	PRIVATE
		${CMAKE_SOURCE_DIR}/libs/ControlSystem/include 
		${CMAKE_SOURCE_DIR}/libs/ControlSystem/libs/SG90/include
		${CMAKE_SOURCE_DIR}/libs/ControlSystem/libs/FaceTrackingCamera/include
)

target_link_libraries(${BINARY} PRIVATE lib_ControlSystem lib_FaceTrackingCamera lib_SG90 gtest)