cmake_minimum_required (VERSION 2.8)

#src
set(PJ_GATESERVER_SRC
	${CMAKE_SOURCE_DIR}/protocol/inc.pb.h
	${CMAKE_SOURCE_DIR}/protocol/inc.pb.cc
	${CMAKE_SOURCE_DIR}/protocol/csid.pb.h
	${CMAKE_SOURCE_DIR}/protocol/csid.pb.cc
	${CMAKE_SOURCE_DIR}/protocol/game.pb.h
	${CMAKE_SOURCE_DIR}/protocol/game.pb.cc
	${CMAKE_SOURCE_DIR}/protocol/protoinc.h

	${CMAKE_SOURCE_DIR}/gateserver/net/wanacceptor.h
	${CMAKE_SOURCE_DIR}/gateserver/net/wanacceptor.cpp
	${CMAKE_SOURCE_DIR}/gateserver/net/wansocket.h
	${CMAKE_SOURCE_DIR}/gateserver/net/wansocket.cpp
	${CMAKE_SOURCE_DIR}/gateserver/net/lanworldsocket.h
	${CMAKE_SOURCE_DIR}/gateserver/net/lanworldsocket.cpp

	${CMAKE_SOURCE_DIR}/gateserver/src/main.cpp
)

foreach(src ${PJ_GATESERVER_SRC})
	file(APPEND ${src})
endforeach(src)


source_group("Interface"	REGULAR_EXPRESSION gateserver/interface)
source_group("Public"	REGULAR_EXPRESSION gateserver/public)
source_group("Net"		REGULAR_EXPRESSION gateserver/net)
source_group("Protocol"		REGULAR_EXPRESSION	protocol)

#include path
include_directories(
	${PLATFORM_PATH_DIR}
	${CMAKE_SOURCE_DIR}/../3rd/boost_1_55_0
	${CMAKE_SOURCE_DIR}/../3rd/protobuf-2.5.0/src
	${CMAKE_SOURCE_DIR}/../public/include
	${CMAKE_SOURCE_DIR}/protocol
	${CMAKE_SOURCE_DIR}/gateserver
	${CMAKE_SOURCE_DIR}/gateserver/net
	${CMAKE_SOURCE_DIR}/gateserver/src
)

#output
add_executable(GateServer ${PJ_GATESERVER_SRC})

if(WIN32)
	target_link_libraries(GateServer libprotobuf CommonLib AsioLib)
	set_target_properties(GateServer
		PROPERTIES
		COMPILE_FLAGS "/wd4819 /wd4996 /ZI /Od /Ob0" LINK_FLAGS "/DEBUG"
	)
else()
	target_link_libraries(GateServer)
	set_target_properties(GateServer
		PROPERTIES
		COMPILE_FLAGS "-std=c++11 -Wall -g"
	)
endif()
