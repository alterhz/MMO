cmake_minimum_required (VERSION 2.8)

#src
set(PJ_WORLDSERVER_SRC
	${CMAKE_SOURCE_DIR}/protocol/inc.pb.h
	${CMAKE_SOURCE_DIR}/protocol/inc.pb.cc
	${CMAKE_SOURCE_DIR}/protocol/csid.pb.h
	${CMAKE_SOURCE_DIR}/protocol/csid.pb.cc
	${CMAKE_SOURCE_DIR}/protocol/game.pb.h
	${CMAKE_SOURCE_DIR}/protocol/game.pb.cc
	${CMAKE_SOURCE_DIR}/protocol/protoinc.h

	${CMAKE_SOURCE_DIR}/../public/src/main.cpp
	${CMAKE_SOURCE_DIR}/../public/src/mainthread.h
	${CMAKE_SOURCE_DIR}/../public/src/mainthread.cpp
	${CMAKE_SOURCE_DIR}/../public/src/exitchildthread.h
	${CMAKE_SOURCE_DIR}/../public/src/exitchildthread.cpp

	${CMAKE_SOURCE_DIR}/worldserver/net/clientacceptor.h
	${CMAKE_SOURCE_DIR}/worldserver/net/clientacceptor.cpp
	${CMAKE_SOURCE_DIR}/worldserver/net/clientsocket.h
	${CMAKE_SOURCE_DIR}/worldserver/net/clientsocket.cpp
	${CMAKE_SOURCE_DIR}/worldserver/net/netmanager.h
	${CMAKE_SOURCE_DIR}/worldserver/net/netmanager.cpp
	${CMAKE_SOURCE_DIR}/worldserver/net/loginclient.h
	${CMAKE_SOURCE_DIR}/worldserver/net/loginclient.cpp
	${CMAKE_SOURCE_DIR}/worldserver/net/loginclientmanager.h
	${CMAKE_SOURCE_DIR}/worldserver/net/loginclientmanager.cpp

	${CMAKE_SOURCE_DIR}/worldserver/public/app.h
	${CMAKE_SOURCE_DIR}/worldserver/public/app.cpp
)

foreach(src ${PJ_WORLDSERVER_SRC})
	file(APPEND ${src})
endforeach(src)

source_group("Src"		REGULAR_EXPRESSION	../public/src)
source_group("Public"	REGULAR_EXPRESSION	worldserver/public)
source_group("Net"		REGULAR_EXPRESSION	worldserver/net)
source_group("Protocol"		REGULAR_EXPRESSION	protocol)


#include path
include_directories(
	${PLATFORM_PATH_DIR}
	${CMAKE_SOURCE_DIR}/../3rd/boost_1_55_0
	${CMAKE_SOURCE_DIR}/../3rd/protobuf-2.5.0/src
	${CMAKE_SOURCE_DIR}/../public/include
	${CMAKE_SOURCE_DIR}/../public/src
	${CMAKE_SOURCE_DIR}/protocol
	${CMAKE_SOURCE_DIR}/worldserver
	${CMAKE_SOURCE_DIR}/worldserver/public
	${CMAKE_SOURCE_DIR}/worldserver/net
)

#output
add_executable(WorldServer ${PJ_WORLDSERVER_SRC})

if(WIN32)
	target_link_libraries(WorldServer libprotobuf CommonLib AsioLib)
	set_target_properties(WorldServer
		PROPERTIES
		COMPILE_FLAGS "/wd4819 /wd4996 /ZI /Od /Ob0" LINK_FLAGS "/DEBUG"
	)
else()
	target_link_libraries(WorldServer)
	set_target_properties(WorldServer
		PROPERTIES
		COMPILE_FLAGS "-std=c++11 -Wall -g"
	)
endif()
