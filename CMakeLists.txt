# Set minimum CMAKE
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project( KWayMergeSort)

# require C++14
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( APP_EXECUTABLE KWayMergeSortTest )

include_directories( inc )

ADD_EXECUTABLE( ${APP_EXECUTABLE} "src/kway-mergesort-test.cpp" )
#TARGET_LINK_LIBRARIES( ${APP_EXECUTABLE} ${LIB_NAME} )

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${APP_EXECUTABLE} )

#include (CTest)
enable_testing()
#set (CTEST_OUTPUT_ON_FAILURE 1)
#list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
add_test(${APP_EXECUTABLE}_PresuppliedSorts ${APP_EXECUTABLE} 1)
add_test(${APP_EXECUTABLE}_KWayMerge ${APP_EXECUTABLE} 2)
add_test(${APP_EXECUTABLE}_KWayTemplates ${APP_EXECUTABLE} 3)

find_program(VALGRIND "valgrind")
if(VALGRIND)
	add_custom_target(valgrind
		COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes --error-exitcode=1 $<TARGET_FILE:${APP_EXECUTABLE}>)
endif()
