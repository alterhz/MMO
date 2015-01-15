cmake_minimum_required (VERSION 2.8)

#src
set(PJ_COMMONLIB_SRC
	${CMAKE_SOURCE_DIR}/common/version.txt

	${CMAKE_SOURCE_DIR}/../public/include/stringjoin.h
	${CMAKE_SOURCE_DIR}/../public/include/loginc.h
	${CMAKE_SOURCE_DIR}/../public/include/utility.h

	${CMAKE_SOURCE_DIR}/../public/include/common/boostheader.h
	${CMAKE_SOURCE_DIR}/../public/include/common/ringbuffer.h
	${CMAKE_SOURCE_DIR}/../public/include/common/thread.h
	${CMAKE_SOURCE_DIR}/../public/include/common/file.h
	${CMAKE_SOURCE_DIR}/../public/include/common/log.h
	${CMAKE_SOURCE_DIR}/../public/include/common/safequeue.h
	${CMAKE_SOURCE_DIR}/../public/include/common/timer.h

	${CMAKE_SOURCE_DIR}/common/src/boostheader.cpp
	${CMAKE_SOURCE_DIR}/common/src/boostheaderext.cpp
	${CMAKE_SOURCE_DIR}/common/src/ringbuffer.cpp
	${CMAKE_SOURCE_DIR}/common/src/thread.cpp
	${CMAKE_SOURCE_DIR}/common/src/file.cpp
	${CMAKE_SOURCE_DIR}/common/src/log.cpp
	${CMAKE_SOURCE_DIR}/common/src/safequeue.cpp
	${CMAKE_SOURCE_DIR}/common/src/timer.cpp
)

foreach(src ${PJ_COMMONLIB_SRC})
	file(APPEND ${src})
endforeach(src)

source_group("Include"		REGULAR_EXPRESSION public/include)
source_group("Common"		REGULAR_EXPRESSION public/include/common)
source_group("Src"			REGULAR_EXPRESSION common/src)

#include path
include_directories(
	${PLATFORM_PATH_DIR}
	${CMAKE_SOURCE_DIR}/../3rd/boost_1_55_0
	${CMAKE_SOURCE_DIR}/../public/include
	${CMAKE_SOURCE_DIR}/common/src
)

#output
add_library(CommonLib STATIC ${PJ_COMMONLIB_SRC})

if(WIN32)
	target_link_libraries(CommonLib)
	set_target_properties(CommonLib
		PROPERTIES
		COMPILE_FLAGS "/wd4819 /wd4996"
	)
else()
	target_link_libraries(CommonLib)
	set_target_properties(CommonLib
		PROPERTIES
		COMPILE_FLAGS "-std=c++11 -g"
	)
endif()