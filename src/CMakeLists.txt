cmake_minimum_required( VERSION 3.15 )
set(EXEC_PROJECT_NAME Exec_${CMAKE_PROJECT_NAME})

find_library(SG90Controller
	NAMES ${CMAKE_SHARED_LIBRARY_PREFIX}SG90Controller
	PATHS ${CMAKE_SOURCE_DIR})

#source files
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/core/RaspiRemoteCam.cpp)

#target
add_executable( ${EXEC_PROJECT_NAME} ${SOURCES} )

# include files
target_include_directories(${EXEC_PROJECT_NAME}
	PUBLIC
		$<TARGET_PROPERTY:SG90Controller,INCLUDE_DIRECTORIES> 
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src 
)

set_target_properties(${EXEC_PROJECT_NAME} PROPERTIES
			CXX_STANDARD 14
			CXX_STANDARD_REQUIRED ON
			EXPORT_PACKAGE_REGISTRY ON
)
