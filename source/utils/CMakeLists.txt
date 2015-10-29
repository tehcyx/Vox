set(UTIL_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Random.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Interpolator.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Interpolator.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/CountdownTimer.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/CountdownTimer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/TimeManager.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TimeManager.h"
	PARENT_SCOPE)

source_group("utils" FILES ${UTIL_SRCS})