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

	unsigned int GetInstanceShaderIndex();

	void SetupGLBuffers();

	// Accessors
	int GetNumBlockParticleEffects();
	int GetNumBlockParticleEmitters();
	int GetNumBlockParticles();
	int GetNumRenderableParticles();

	// Creation
	BlockParticle* CreateBlockParticleFromEmitterParams(BlockParticleEmitter* pEmitter);
	BlockParticle* CreateBlockParticle(vec3 pos, vec3 gravityDir, float gravityMultiplier, vec3 pointOrigin,
									   float startScale, float startScaleVariance, float endScale, float endScaleVariance,
									   float startR, float startG, float startB, float startA,
									   float startRVariance, float startGVariance, float startBVariance, float startAVariance,
									   float endR, float endG, float endB, float endA,
									   float endRVariance, float endGVariance, float endBVariance, float endAVariance,
									   float lifetime, float lifetimeVariance,
									   float velocityTowardPoint, float accelerationTowardsPoint,
									   vec3 startVelocity, vec3 startVelocityVariance,
									   vec3 startAngularVelocity, vec3 startAngularVelocityVariance,
									   float tangentialVelocityXY, float tangentialAccelerationXY, float tangentialVelocityXZ, float tangentialAccelerationXZ, float tangentialVelocityYZ, float tangentialAccelerationYZ,
									   bool randomStartRotation, vec3 startRotation, bool worldCollision, bool destoryOnCollision, bool startLifeDecayOnCollision,
									   bool createEmitters, BlockParticleEmitter* pCreatedEmitter);
	BlockParticleEmitter* CreateBlockParticleEmitter(string name, vec3 pos);
	BlockParticleEffect* CreateBlockParticleEffect(string name, vec3 pos);
	
	BlockParticleEffect* ImportParticleEffect(string fileName, vec3 pos, unsigned int* particleEffectId);
	void DestroyParticleEffect(unsigned int particleEffectId);
	void UpdateParticleEffectPosition(unsigned int particleEffectId, vec3 position);

	void ExplodeQubicleBinary(QubicleBinary* pQubicleBinary, float scale, int particleSpawnChance);
	void ExplodeQubicleMatrix(QubicleMatrix* pMatrix, float scale, int particleSpawnChance, bool allSameColour, float sameR, float sameG, float sameB, float sameA);

	// Rendering modes
	void SetWireFrameRender(bool wireframe);
	void SetInstancedRendering(bool instance);

	// Update
	void Update(float dt);

	// Rendering
	void Render();
	void RenderInstanced();
	void RenderDefault();
	void RenderBlockParticle(BlockParticle* pBlockParticle);
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

	// Particle effect counter
	int m_particleEffectCounter;

	// Render modes
	bool m_renderWireFrame;
	bool m_instanceRendering;

	// Array buffers
	GLuint m_vertexArray;
	GLuint m_positionBuffer;
	GLuint m_normalBuffer;
	GLuint m_colourBuffer;
	GLuint m_matrixBuffer;

	// Shader
	unsigned int m_instanceShader;

	// Non-instanced rendering
	unsigned int m_blockMaterialID;
	OGLPositionNormalColourVertex m_vertexBuffer[24];

	// Block particles list
	BlockParticlesList m_vpBlockParticlesList;

	// Block particle emitters list
	BlockParticlesEmitterList m_vpBlockParticleEmittersList;
	BlockParticlesEmitterList m_vpBlockParticleEmittersAddList;

	// Block particle effects list
	BlockParticleEffectList m_vpBlockParticleEffectsList;
};
