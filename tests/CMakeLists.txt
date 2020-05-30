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

macro(package_add_test TESTSOURCE)
    # NOTE: place all tests in cpp files
	get_filename_component(testName ${TESTSOURCE} NAME_WE)
    add_executable(${testName} ${TESTSOURCE})
	message("Adding " ${testName})
	# NOTE: Currently linking all libraries.
	# TODO: Improve linking
    target_link_libraries(${testName} gtest gmock gtest_main SG90Controller FaceTrackingCamera SG90)
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
