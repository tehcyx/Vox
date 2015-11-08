set(SRCS
    "main.cpp"
    "VoxGame.h"
    "VoxGame.cpp"
    "VoxApplication.h"
    "VoxApplication.cpp"
    "VoxWindow.h"
    "VoxWindow.cpp"
    "VoxInput.cpp"
    "VoxControls.cpp"
    "VoxCamera.cpp"
    "VoxRender.cpp"
    "VoxUpdate.cpp"
    "VoxGUI.cpp")

add_subdirectory(utils)
add_subdirectory(freetype)
add_subdirectory(glew)
add_subdirectory(Lighting)
add_subdirectory(Maths)
add_subdirectory(models)
add_subdirectory(Particles)
add_subdirectory(Renderer)
add_subdirectory(gui)
add_subdirectory(glm)
add_subdirectory(Player)
add_subdirectory(blocks)
add_subdirectory(lua)
add_subdirectory(selene)
add_subdirectory(frontend)

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
source_group("source\\blocks" FILES ${BLOCKS_SRCS})
source_group("source\\lua" FILES ${LUA_SRCS})
source_group("source\\selene" FILES ${SELENE_HEADERS})
source_group("source\\selene\\selene" FILES ${SELENE_SRCS})
source_group("source\\frontend" FILES ${FRONTEND_SRCS})

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
               ${PLAYER_SRCS}
               ${BLOCKS_SRCS}
               ${LUA_SRCS}
               ${SELENE_HEADERS}
               ${SELENE_SRCS}
               ${FRONTEND_SRCS})

include_directories(".")			   
include_directories("glfw\\include")
include_directories("glew\\include")
include_directories("freetype\\include")
include_directories("lua")
include_directories("selene")

if(MSVC)
target_link_libraries(Vox "opengl32.lib")
target_link_libraries(Vox "winmm.lib")
elseif(UNIX)
target_link_libraries(Vox "GL")
target_link_libraries(Vox "GLU")
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}/glfw/libs/linux/d/libglfw3_64.a")
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}source/freetype/libs/linux/libfreetype261d_64.a")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}/freetype/libs/linux/libfreetype261_64.a")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}/glfw/libs/linux/r/libglfw3_64.a")
	else()
		target_link_libraries(Vox debug "source/glfw/libs/linux/d/libglfw3.a")
		target_link_libraries(Vox debug "source/freetype/libs/linux/libfreetype261d.a")
		target_link_libraries(Vox optimized "source/glfw/libs/linux/r/libglfw3.a")
		target_link_libraries(Vox optimized "source/freetype/libs/linux/libfreetype261.a")
	endif()
target_link_libraries(Vox "X11")
target_link_libraries(Vox "Xrandr")
target_link_libraries(Vox "Xi")
target_link_libraries(Vox "Xxf86vm")
target_link_libraries(Vox "Xcursor")
target_link_libraries(Vox "Xinerama")
target_link_libraries(Vox "pthread")
target_link_libraries(Vox "dl")
endif()

if(MSVC11)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2012\\d\\glfw3_64.lib")
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2012\\freetype261d_64.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2012\\r\\glfw3_64.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2012\\freetype261_64.lib")
	else()
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2012\\d\\glfw3.lib")
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2012\\freetype261d.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2012\\r\\glfw3.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2012\\freetype261.lib")
	endif()
endif(MSVC11)
if(MSVC12)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2013\\d\\glfw3_64.lib")
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2013\\freetype261d_64.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2013\\r\\glfw3_64.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2013\\freetype261_64.lib")
	else()
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2013\\d\\glfw3.lib")
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2013\\freetype261d.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2013\\r\\glfw3.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2013\\freetype261.lib")
	endif()
endif(MSVC12)
if(MSVC14)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2015\\d\\glfw3_64.lib")
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2015\\freetype261d_64.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2015\\r\\glfw3_64.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2015\\freetype261_64.lib")
	else()
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2015\\d\\glfw3.lib")
		target_link_libraries(Vox debug "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2015\\freetype261d.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\2015\\r\\glfw3.lib")
		target_link_libraries(Vox optimized "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\2015\\freetype261.lib")
	endif()
endif(MSVC14)

if(MSVC)
	set_target_properties(Vox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../../")
	set_target_properties(Vox PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "../../")
	set_target_properties(Vox PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "../../")
	
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif(MSVC)

set(CMAKE_CONFIGURATION_TYPES Debug Release)
