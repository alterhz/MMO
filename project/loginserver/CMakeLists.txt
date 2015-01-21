cmake_minimum_required (VERSION 2.8)

#src
set(PJ_LOGINSERVER_SRC
	${CMAKE_SOURCE_DIR}/../public/src/main.cpp
	${CMAKE_SOURCE_DIR}/../public/src/mainthread.h
	${CMAKE_SOURCE_DIR}/../public/src/mainthread.cpp
	${CMAKE_SOURCE_DIR}/../public/src/exitchildthread.h
	${CMAKE_SOURCE_DIR}/../public/src/exitchildthread.cpp

	${CMAKE_SOURCE_DIR}/loginserver/net/clientmanager.h
	${CMAKE_SOURCE_DIR}/loginserver/net/clientmanager.cpp
	${CMAKE_SOURCE_DIR}/loginserver/net/client.h
	${CMAKE_SOURCE_DIR}/loginserver/net/client.cpp
	${CMAKE_SOURCE_DIR}/loginserver/net/worldconnector.h
	${CMAKE_SOURCE_DIR}/loginserver/net/worldconnector.cpp

	${CMAKE_SOURCE_DIR}/loginserver/public/app.h
	${CMAKE_SOURCE_DIR}/loginserver/public/app.cpp
)

foreach(src ${PJ_LOGINSERVER_SRC})
	file(APPEND ${src})
endforeach(src)

source_group("Src"		REGULAR_EXPRESSION	../public/src)
source_group("Public"	REGULAR_EXPRESSION	loginserver/public)
source_group("Net"		REGULAR_EXPRESSION	loginserver/net)
source_group("Protocol"		REGULAR_EXPRESSION	protocol)

#include path
include_directories(
	${PLATFORM_PATH_DIR}
	${CMAKE_SOURCE_DIR}/../3rd/boost_1_55_0
	${CMAKE_SOURCE_DIR}/../3rd/protobuf-2.5.0/src
	${CMAKE_SOURCE_DIR}/../public/include
	${CMAKE_SOURCE_DIR}/../public/src
	${CMAKE_SOURCE_DIR}/protocol
	${CMAKE_SOURCE_DIR}/loginserver
	${CMAKE_SOURCE_DIR}/loginserver/public
	${CMAKE_SOURCE_DIR}/loginserver/net
)

#output
add_executable(LoginServer ${PJ_LOGINSERVER_SRC})

if(WIN32)
	target_link_libraries(LoginServer libprotobuf ProtocolLib CommonLib AsioLib)
	set_target_properties(LoginServer
		PROPERTIES
		COMPILE_FLAGS "/wd4819 /wd4996 /ZI /Od /Ob0" LINK_FLAGS "/DEBUG"
	)
else()
	target_link_libraries(LoginServer)
	set_target_properties(LoginServer
		PROPERTIES
		COMPILE_FLAGS "-std=c++11 -Wall -g"
	)
endif()
