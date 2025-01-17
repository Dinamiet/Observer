cmake_minimum_required(VERSION 3.20.0)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
	Buffers
	GIT_REPOSITORY
		git@github.com:Dinamiet/Buffers.git
	GIT_TAG
		main
	SOURCE_DIR
		${CMAKE_SOURCE_DIR}/lib/Buffers
)

FetchContent_MakeAvailable(
	Buffers
)
