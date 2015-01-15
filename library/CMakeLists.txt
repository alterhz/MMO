cmake_minimum_required (VERSION 2.8)

project (Library)

add_definitions(-D_UNICODE -DUNICODE)

if(WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501)
	set(PLATFORM_PATH_DIR		${CMAKE_SOURCE_DIR}/../public/platform/win32)
	set(LIBRARY_OUTPUT_PATH		${CMAKE_SOURCE_DIR}/../public/lib/win32)
	set(EXECUTABLE_OUTPUT_PATH	${CMAKE_SOURCE_DIR}/../bin/win32)
else()
	add_definitions(-DLINUX_ENGINE -DNDEBUG)
	set(PLATFORM_PATH_DIR		${CMAKE_SOURCE_DIR}/../public/platform/linux)
	set(LIBRARY_OUTPUT_PATH		${CMAKE_SOURCE_DIR}/../public/lib/linux)
	set(EXECUTABLE_OUTPUT_PATH	${CMAKE_SOURCE_DIR}/../bin/linux)
endif()

enable_testing()

add_subdirectory(common)
add_subdirectory(asio)
add_subdirectory(test)

