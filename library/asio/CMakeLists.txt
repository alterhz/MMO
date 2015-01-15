cmake_minimum_required (VERSION 2.8)

#src
set(PJ_ASIOLIB_SRC
	${CMAKE_SOURCE_DIR}/asio/version.txt

	${CMAKE_SOURCE_DIR}/../public/include/asio/tcpaccept.h
	${CMAKE_SOURCE_DIR}/../public/include/asio/tcpsocket.h
	${CMAKE_SOURCE_DIR}/../public/include/asio/tcpconnector.h

	${CMAKE_SOURCE_DIR}/asio/src/tcpaccept.cpp
	${CMAKE_SOURCE_DIR}/asio/src/tcpsocket.cpp
	${CMAKE_SOURCE_DIR}/asio/src/tcpconnector.cpp
)

foreach(src ${PJ_ASIOLIB_SRC})
	file(APPEND ${src})
endforeach(src)

source_group("Include"	REGULAR_EXPRESSION public/include)
source_group("Asio"		REGULAR_EXPRESSION public/include/asio)
source_group("Src"		REGULAR_EXPRESSION asio/src)

#include path
include_directories(
	${PLATFORM_PATH_DIR}
	${CMAKE_SOURCE_DIR}/../3rd/boost_1_55_0
	${CMAKE_SOURCE_DIR}/../public/include
	${CMAKE_SOURCE_DIR}/asio/src
)

#output
add_library(AsioLib STATIC ${PJ_ASIOLIB_SRC})

if(WIN32)
	target_link_libraries(AsioLib)
	set_target_properties(AsioLib
		PROPERTIES
		COMPILE_FLAGS "/wd4819 /wd4996"
	)
else()
	target_link_libraries(AsioLib)
	set_target_properties(AsioLib
		PROPERTIES
		COMPILE_FLAGS "-std=c++11 -g"
	)
endif()