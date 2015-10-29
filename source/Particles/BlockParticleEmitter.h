// ******************************************************************************
//
// Filename:	BlockParticleEmitter.h
// Project:		Game
// Author:		Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 09/11/14
//
// Copyright (c) 2005-2011, Steven Ball
//
// ******************************************************************************

#pragma once

#include "../Maths/3dmaths.h"
#include "../Renderer/Renderer.h"

class BlockParticleManager;
class BlockParticleEffect;
class BlockParticle;

enum EmitterType
{
	EmitterType_Point = 0,
	EmitterType_Square,
	EmitterType_Cube,
	EmitterType_Circle,
	EmitterType_Sphere,
	EmitterType_Mesh,
};

class BlockParticleEmitter
{
public:
	/* Public methods */
	BlockParticleEmitter(Renderer* pRenderer, BlockParticleManager* pBlockParticleManager);
	~BlockParticleEmitter();

	void CopyParams(BlockParticleEmitter* EmitterParams);

	// Update
	void Update(float dt);

	// Rendering
	void Render();

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */
	bool m_erase;

	// Name
	string m_emitterName;

	// Emitter position
	vec3 m_startingPosition;
	vec3 m_position;

	// Creation Time
	float m_creationTime;
	float m_creationTimer;

	// Number of particles to spawn
	int m_numParticlesToSpawn;

	// Should particles follow emitter movement
	bool m_particlesFollowEmitter;

	// Emitter orbiting
	bool m_orbit;
	bool m_orbitReverse;
	float m_orbitRadius;
	float m_orbitTime;
	float m_orbitTimer;

	// Playback controls
	bool m_started;
	bool m_paused;

	// Emitter type
	EmitterType m_emitterType;

	// Emitter radius and lengths
	float m_emitterRadius;
	float m_emitterLengthX;
	float m_emitterLengthY;
	float m_emitterLengthZ;

	// Are we spawning on the outside of the shape
	bool m_spawnOutline;

	// Particle creation params
	vec3 m_gravityDirection;
	float m_gravityMultiplier;
	vec3 m_pointOrigin;
	float m_startScale;
	float m_startScaleVariance;
	float m_endScale;
	float m_endScaleVariance;
	float m_startRed;
	float m_startRedVariance;
	float m_endRed;
	float m_endRedVariance;
	float m_startGreen;
	float m_startGreenVariance;
	float m_endGreen;
	float m_endGreenVariance;
	float m_startBlue;
	float m_startBlueVariance;
	float m_endBlue;
	float m_endBlueVariance;
	float m_startAlpha;
	float m_startAlphaVariance;
	float m_endAlpha;
	float m_endAlphaVariance;
	float m_lifeTime;
	float m_lifeTimeVariance;
	float m_velocityTowardsPoint;
	float m_accelerationTowardsPoint;
	bool m_checkWorldCollisions;
	bool m_destoryOnCollision;
	bool m_startLifeDecayOnCollision;
	vec3 m_startVelocity;
	vec3 m_startVelocityVariance;
	bool m_randomStartRotation;
	vec3 m_startRotation;
	vec3 m_startAngularVelocity;
	vec3 m_startAngularVelocityVariance;
	float m_tangentialVelocityXY;
	float m_tangentialAccelerationXY;
	float m_tangentialVelocityXZ;
	float m_tangentialAccelerationXZ;
	float m_tangentialVelocityYZ;
	float m_tangentialAccelerationYZ;
	bool m_createEmitters;
	string m_createEmitterName;
	bool m_isReferenceEmitter;

	// Parent effect
	BlockParticleEffect* m_pParent;

	// Parent particle
	BlockParticle* m_pParentParticle;

protected:
	/* Protected members */

public:
	/* Private members */
	Renderer* m_pRenderer;
	BlockParticleManager* m_pBlockParticleManager;
};
