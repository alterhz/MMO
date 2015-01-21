cmake_minimum_required (VERSION 2.8)

#src
set(LIB_PROTOCOL_SRC
	${CMAKE_SOURCE_DIR}/protocol/protoinc.h
	${CMAKE_SOURCE_DIR}/protocol/inc.pb.h
	${CMAKE_SOURCE_DIR}/protocol/inc.pb.cc
	${CMAKE_SOURCE_DIR}/protocol/csid.pb.h
	${CMAKE_SOURCE_DIR}/protocol/csid.pb.cc
	${CMAKE_SOURCE_DIR}/protocol/msg.pb.h
	${CMAKE_SOURCE_DIR}/protocol/msg.pb.cc
	${CMAKE_SOURCE_DIR}/protocol/scsid.pb.h
	${CMAKE_SOURCE_DIR}/protocol/scsid.pb.cc
	${CMAKE_SOURCE_DIR}/protocol/smsg.pb.h
	${CMAKE_SOURCE_DIR}/protocol/smsg.pb.cc
)

foreach(src ${LIB_PROTOCOL_SRC})
	file(APPEND ${src})
endforeach(src)

source_group("Protocol"		REGULAR_EXPRESSION	protocol)


#include path
include_directories(
	${PLATFORM_PATH_DIR}
	${CMAKE_SOURCE_DIR}/../3rd/boost_1_55_0
	${CMAKE_SOURCE_DIR}/../3rd/protobuf-2.5.0/src
	${CMAKE_SOURCE_DIR}/protocol
)

#output
add_library(ProtocolLib STATIC ${LIB_PROTOCOL_SRC})

if(WIN32)
	target_link_libraries(ProtocolLib)
	set_target_properties(ProtocolLib
		PROPERTIES
		COMPILE_FLAGS "/wd4819 /wd4996"
	)
else()
	target_link_libraries(ProtocolLib)
	set_target_properties(ProtocolLib
		PROPERTIES
		COMPILE_FLAGS "-std=c++11 -g"
	)
endif()
