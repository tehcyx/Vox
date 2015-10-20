set(UTIL_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Random.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Interpolator.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Interpolator.cpp"
	PARENT_SCOPE)

source_group("utils" FILES ${UTIL_SRCS})