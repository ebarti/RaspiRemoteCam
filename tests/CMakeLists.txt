cmake_minimum_required( VERSION 3.15 )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#include(GoogleTest)
add_subdirectory("${PROJECT_SOURCE_DIR}/libs/googletest" "libs/googletest")
macro(package_add_test TESTSOURCE)
    # NOTE: place all tests in cpp files
	get_filename_component(testName ${TESTSOURCE} NAME_WE)
    add_executable(${testName} ${TESTSOURCE})
	message("Adding " ${testName})
	# NOTE: Currently linking all libraries.
	# TODO: Improve linking
    target_link_libraries(${testName} gtest gmock gtest_main lib_ControlSystem lib_FaceTrackingCamera lib_SG90)
	#target_link_libraries(${testName} GTest::GTest lib_ControlSystem lib_FaceTrackingCamera lib_SG90)
    gtest_discover_tests(${testName}
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
    set_target_properties(${testName} PROPERTIES FOLDER tests)
endmacro()

file(GLOB_RECURSE testSrcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
foreach(testSrc ${testSrcs})
	message("Processing " ${testSrc})
	package_add_test(${testSrc})
endforeach()
