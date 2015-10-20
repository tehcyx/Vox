set(PARTICLES_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/BlockParticle.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/BlockParticle.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/BlockParticleEffect.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/BlockParticleEffect.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/BlockParticleEmitter.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/BlockParticleEmitter.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/BlockParticleManager.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/BlockParticleManager.cpp"
	PARENT_SCOPE)

source_group("particles" FILES ${PARTICLES_SRCS})