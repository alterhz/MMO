cmake_minimum_required (VERSION 2.8)

#src
set(PJ_DEMO_SRC
	${CMAKE_SOURCE_DIR}/demo/public/header.h
	${CMAKE_SOURCE_DIR}/demo/public/header.cpp
	${CMAKE_SOURCE_DIR}/demo/public/headerext.cpp

	${CMAKE_SOURCE_DIR}/demo/src/main.cpp
)

foreach(src ${PJ_DEMO_SRC})
	file(APPEND ${src})
endforeach(src)


source_group("Interface"	REGULAR_EXPRESSION demo/interface)
source_group("Public"	REGULAR_EXPRESSION demo/public)
source_group("Net"		REGULAR_EXPRESSION demo/net)

#include path
include_directories(
	${PLATFORM_PATH_DIR}
	${CMAKE_SOURCE_DIR}/../3rd/boost_1_55_0
	${CMAKE_SOURCE_DIR}/demo
	${CMAKE_SOURCE_DIR}/demo/interface
	${CMAKE_SOURCE_DIR}/demo/public
	${CMAKE_SOURCE_DIR}/demo/net
	${CMAKE_SOURCE_DIR}/demo/src
)

#output
add_executable(Demo ${PJ_DEMO_SRC})

if(WIN32)
	target_link_libraries(Demo)
	set_target_properties(Demo
		PROPERTIES
		COMPILE_FLAGS "/wd4819 /wd4996 /ZI /Od /Ob0" LINK_FLAGS "/DEBUG"
	)
else()
	target_link_libraries(Demo)
	set_target_properties(Demo
		PROPERTIES
		COMPILE_FLAGS "-std=c++11 -Wall -g"
	)
endif()
