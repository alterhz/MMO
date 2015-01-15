cmake_minimum_required (VERSION 2.8)

#src
set(PJ_TEST_SRC
	${CMAKE_SOURCE_DIR}/test/src/main.cpp
)

foreach(src ${PJ_TEST_SRC})
	file(APPEND ${src})
endforeach(src)

source_group("Common"		REGULAR_EXPRESSION public/include/common)
source_group("Src"			REGULAR_EXPRESSION test/src)

#include path
include_directories(
	${PLATFORM_PATH_DIR}
	${CMAKE_SOURCE_DIR}/../3rd/boost_1_55_0
	${CMAKE_SOURCE_DIR}/../public/include
	${CMAKE_SOURCE_DIR}/test/src
)

#output
add_executable(Test ${PJ_TEST_SRC})

if(WIN32)
	target_link_libraries(Test CommonLib AsioLib)
	set_target_properties(Test
		PROPERTIES
		COMPILE_FLAGS "/wd4819 /wd4996"
	)
else()
	target_link_libraries(Test)
	set_target_properties(Test
		PROPERTIES
		COMPILE_FLAGS "-std=c++11 -g"
	)
endif()