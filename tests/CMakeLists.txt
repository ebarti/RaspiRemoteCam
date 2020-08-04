cmake_minimum_required( VERSION 3.15 )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_library(FaceTrackingCamera
	NAMES ${CMAKE_SHARED_LIBRARY_PREFIX}FaceTrackingCamera
	PATHS ${CMAKE_SOURCE_DIR})

find_library(SG90
	NAMES ${CMAKE_SHARED_LIBRARY_PREFIX}SG90
	PATHS ${CMAKE_SOURCE_DIR})

find_library(SG90Controller
	NAMES ${CMAKE_SHARED_LIBRARY_PREFIX}SG90Controller
	PATHS ${CMAKE_SOURCE_DIR})


set(TESTS_FOLDER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/tests/)

function(my_add_test TEST_NAME) # ARGN are the libraries to link
	message("Adding " ${TEST_NAME})
	set(TEST_SOURCE ${TESTS_FOLDER_PATH}${TEST_NAME}.cpp)
	add_executable(${TEST_NAME} ${TEST_SOURCE})
	target_link_libraries(${TEST_NAME} gtest gmock gtest_main ${ARGN})
    gtest_discover_tests(${TEST_NAME}
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
    set_target_properties(${TEST_NAME} PROPERTIES 
										CXX_STANDARD 14
										CXX_STANDARD_REQUIRED ON
										EXPORT_PACKAGE_REGISTRY ON
										FOLDER tests)
endfunction()

set(CAMERA_TEST_NAME "CameraTests")
my_add_test(${CAMERA_TEST_NAME} FaceTrackingCamera)


set(CONTROLSYSTEM_TEST_NAME "ControlSystemTests")
my_add_test(${CONTROLSYSTEM_TEST_NAME} SG90Controller SG90)

set(PANTILTSERVOSYSTEM_TEST_NAME "PanTiltServoSystemTest")
my_add_test(${PANTILTSERVOSYSTEM_TEST_NAME} SG90)
