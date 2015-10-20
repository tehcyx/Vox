set(SRCS
    "main.cpp"
	"VoxGame.h"
	"VoxGame.cpp"
	"VoxApplication.h"
	"VoxApplication.cpp"
	"VoxWindow.h"
	"VoxWindow.cpp"
	"VoxInput.cpp")

add_subdirectory(utils)
add_subdirectory(freetype)
add_subdirectory(glew)
add_subdirectory(lighting)
add_subdirectory(maths)
add_subdirectory(models)
add_subdirectory(particles)
add_subdirectory(renderer)

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
			   ${RENDERER_SRCS})
			   
include_directories("glfw\\include")
include_directories("glew\\include")
include_directories("freetype\\include")

target_link_libraries(Vox "opengl32.lib")
target_link_libraries(Vox "winmm.lib")
target_link_libraries(Vox "${CMAKE_CURRENT_SOURCE_DIR}\\glfw\\libs\\d\\glfw3.lib")
target_link_libraries(Vox "${CMAKE_CURRENT_SOURCE_DIR}\\freetype\\libs\\freetype237d.lib")

#set_target_properties(Vox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../../bin/")
if ( MSVC )
    set_target_properties(Vox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../../")
    set_target_properties(Vox PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "../../")
    set_target_properties(Vox PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "../../")
    # etc for the other available configuration types (MinSizeRel, RelWithDebInfo)
endif ( MSVC )