set(SRCS
    "main.cpp"
    "VoxGame.h"
    "VoxGame.cpp"
    "VoxApplication.h"
    "VoxApplication.cpp"
    "VoxWindow.h"
    "VoxWindow.cpp"
    "VoxInput.cpp"
    "VoxRender.cpp"
    "VoxUpdate.cpp"
    "VoxGUI.cpp")

add_subdirectory(utils)
add_subdirectory(freetype)
add_subdirectory(glew)
add_subdirectory(lighting)
add_subdirectory(maths)
add_subdirectory(models)
add_subdirectory(particles)
add_subdirectory(renderer)
add_subdirectory(gui)
add_subdirectory(glm)
add_subdirectory(player)

source_group("source" FILES ${SRCS})
source_group("source\\utils" FILES ${UTIL_SRCS})
source_group("source\\freetype" FILES ${FREETYPE_SRCS})
source_group("source\\glew\\src" FILES ${GLEW_SRCS})
source_group("source\\glew\\include\\GL" FILES ${GLEW_HEADERS})
source_group("source\\lighting" FILES ${LIGHTING_SRCS})
source_group("source\\maths" FILES ${MATHS_SRCS})
source_group("source\\models" FILES ${MODELS_SRCS})
source_group("source\\particles" FILES ${PARTICLES_SRCS})
source_group("source\\renderer" FILES ${RENDERER_SRCS})
source_group("source\\gui" FILES ${GUI_SRCS})
source_group("source\\glm" FILES ${GLM_SRCS})
source_group("source\\glm\\detail" FILES ${GLM_DETAIL_SRCS})
source_group("source\\glm\\gtc" FILES ${GLM_GTC_SRCS})
source_group("source\\glm\\gtx" FILES ${GLM_GTX_SRCS})
source_group("source\\player" FILES ${PLAYER_SRCS})

add_executable(Vox
               ${SRCS}
               ${UTIL_SRCS}
               ${FREETYPE_SRCS}
               ${GLEW_SRCS}
               ${GLEW_HEADERS}
               ${LIGHTING_SRCS}
               ${MATHS_SRCS}
               ${MODELS_SRCS}
               ${PARTICLES_SRCS}
               ${RENDERER_SRCS}
               ${GUI_SRCS}
               ${GLM_SRCS}
               ${GLM_DETAIL_SRCS}
               ${GLM_GTC_SRCS}
               ${GLM_GTX_SRCS}
               ${PLAYER_SRCS})

include_directories(".")			   
include_directories("glfw\\include")
include_directories("glew\\include")
include_directories("freetype\\include")

target_link_libraries(Vox "opengl32.lib")
target_link_libraries(Vox "winmm.lib")

if(MSVC11)
	target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2012\\d\\glfw3.lib")
	target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2012\\freetype261d.lib")
	target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2012\\r\\glfw3.lib")
	target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2012\\freetype261.lib")
endif(MSVC11)
if(MSVC12)
	target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2013\\d\\glfw3.lib")
	target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2013\\freetype261d.lib")
	target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2013\\r\\glfw3.lib")
	target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2013\\freetype261.lib")
endif(MSVC12)
if(MSVC14)
	if(WIN32)
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2015\\d\\glfw3.lib")
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2015\\freetype261d.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2015\\r\\glfw3.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2015\\freetype261.lib")
	else(WIN32)
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2015\\d\\glfw3_64.lib")
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2015\\freetype261d_64.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2015\\r\\glfw3_64.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2015\\freetype261_64.lib")
	endif(WIN32)
endif(MSVC14)

if(MSVC)
	set_target_properties(Vox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../../")
	set_target_properties(Vox PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "../../")
	set_target_properties(Vox PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "../../")
	
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif(MSVC)

set(CMAKE_CONFIGURATION_TYPES Debug Release)
