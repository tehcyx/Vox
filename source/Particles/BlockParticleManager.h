// ******************************************************************************
//
// Filename:	BlockParticleManager.h
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
#include "../models/modelloader.h"
#include "../Renderer/Renderer.h"

#include "BlockParticle.h"
#include "BlockParticleEmitter.h"
#include "BlockParticleEffect.h"

class GameWindow;

typedef std::vector<BlockParticle*> BlockParticlesList;
typedef std::vector<BlockParticleEmitter*> BlockParticlesEmitterList;
typedef std::vector<BlockParticleEffect*> BlockParticleEffectList;


class BlockParticleManager
{
public:
	/* Public methods */
	BlockParticleManager(Renderer* pRenderer);
	~BlockParticleManager();

	void ClearBlockParticles();
	void ClearBlockParticleEmitters();
	void ClearBlockParticleEffects();

	void RemoveEmitterLinkage(BlockParticleEmitter* pEmitter);

	void SetupGLBuffers();

	// Accessors
	int GetNumBlockParticleEffects();
	int GetNumBlockParticleEmitters();
	int GetNumBlockParticles();
	int GetNumRenderableParticles();

	// Creation
	BlockParticle* CreateBlockParticleFromEmitterParams(BlockParticleEmitter* pEmitter);
	BlockParticle* CreateBlockParticle(Vector3d pos, Vector3d gravityDir, float gravityMultiplier, Vector3d pointOrigin,
									   float startScale, float startScaleVariance, float endScale, float endScaleVariance,
									   float startR, float startG, float startB, float startA,
									   float startRVariance, float startGVariance, float startBVariance, float startAVariance,
									   float endR, float endG, float endB, float endA,
									   float endRVariance, float endGVariance, float endBVariance, float endAVariance,
									   float lifetime, float lifetimeVariance,
									   float velocityTowardPoint, float accelerationTowardsPoint,
									   Vector3d startVelocity, Vector3d startVelocityVariance,
									   Vector3d startAngularVelocity, Vector3d startAngularVelocityVariance,
									   float tangentialVelocityXY, float tangentialAccelerationXY, float tangentialVelocityXZ, float tangentialAccelerationXZ, float tangentialVelocityYZ, float tangentialAccelerationYZ,
									   bool randomStartRotation, Vector3d startRotation, bool worldCollision, bool destoryOnCollision, bool startLifeDecayOnCollision,
									   bool createEmitters, BlockParticleEmitter* pCreatedEmitter);
	BlockParticleEmitter* CreateBlockParticleEmitter(string name, Vector3d pos);
	BlockParticleEffect* CreateBlockParticleEffect(string name, Vector3d pos);
	
	BlockParticleEffect* ImportParticleEffect(string fileName, Vector3d pos, unsigned int* particleEffectId);
	void DestroyParticleEffect(unsigned int particleEffectId);
	void UpdateParticleEffectPosition(unsigned int particleEffectId, Vector3d position);

	void ExplodeQubicleBinary(QubicleBinary* pQubicleBinary, float scale, int particleSpawnChance);
	void ExplodeQubicleMatrix(QubicleMatrix* pMatrix, float scale, int particleSpawnChance, bool allSameColour, float sameR, float sameG, float sameB, float sameA);

	// Update
	void Update(float dt);

	// Rendering
	void Render();
	void RenderDebug();
	void RenderEmitters();
	void RenderEffects();

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	Renderer* m_pRenderer;

	int m_particleEffectCounter;

	GLuint m_vertexArray;
	GLuint m_positionBuffer;
	GLuint m_normalBuffer;
	GLuint m_colourBuffer;
	GLuint m_matrixBuffer;

	unsigned int m_instanceShader;

	BlockParticlesList m_vpBlockParticlesList;

	BlockParticlesEmitterList m_vpBlockParticleEmittersList;
	BlockParticlesEmitterList m_vpBlockParticleEmittersAddList;

	BlockParticleEffectList m_vpBlockParticleEffectsList;
};
