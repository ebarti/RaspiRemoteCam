cmake_minimum_required( VERSION 3.15 )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BINARY Exec_${CMAKE_PROJECT_NAME})



#source files
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/core/RaspiRemoteCam.cpp)

#target
add_executable( ${BINARY} ${SOURCES} )

# include files
target_include_directories(${BINARY}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include 
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src 
)