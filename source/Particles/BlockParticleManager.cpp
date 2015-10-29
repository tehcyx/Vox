// ******************************************************************************
//
// Filename:	BlockParticleManager.cpp
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

#include "BlockParticleManager.h"
#include "../utils/Random.h"

#include <algorithm>


float vertices[] = { -0.5f, -0.5f, 0.5f, 1.0f, // Front
	0.5f, -0.5f, 0.5f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f,
	-0.5f, 0.5f, 0.5f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, // Back
	-0.5f, 0.5f, -0.5f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, // Left
	-0.5f, -0.5f, 0.5f, 1.0f,
	-0.5f, 0.5f, 0.5f, 1.0f,
	-0.5f, 0.5f, -0.5f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, // Right
	0.5f, 0.5f, -0.5f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, // Top
	0.5f, 0.5f, 0.5f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f,
	-0.5f, 0.5f, -0.5f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, // Bottom
	-0.5f, -0.5f, -0.5f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f
};

float normals[] = { 0.0f, 0.0f, 1.0f, 1.0f, // Front
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, -1.0f, 1.0f, // Back
	0.0f, 0.0f, -1.0f, 1.0f,
	0.0f, 0.0f, -1.0f, 1.0f,
	0.0f, 0.0f, -1.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f, // Left
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 0.0f, 1.0f, // Right
	-1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f, // Top
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, -1.0f, 0.0f, 1.0f, // Bottom
	0.0f, -1.0f, 0.0f, 1.0f,
	0.0f, -1.0f, 0.0f, 1.0f,
	0.0f, -1.0f, 0.0f, 1.0f
};

int indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };

BlockParticleManager::BlockParticleManager(Renderer* pRenderer)
{
	m_pRenderer = pRenderer;

	m_particleEffectCounter = 0;

	m_renderWireFrame = false;

	m_vertexArray = -1;
	m_positionBuffer = -1;
	m_normalBuffer = -1;
	m_colourBuffer = -1;
	m_matrixBuffer = -1;

	m_instanceShader = -1;
	m_pRenderer->LoadGLSLShader("media/shaders/instance.vertex", "media/shaders/instance.pixel", &m_instanceShader);

	SetupGLBuffers();
}

BlockParticleManager::~BlockParticleManager()
{
	ClearBlockParticles();
	ClearBlockParticleEmitters();
	ClearBlockParticleEffects();
}

void BlockParticleManager::ClearBlockParticles()
{
	for(unsigned int i = 0; i < m_vpBlockParticlesList.size(); i++)
	{
		delete m_vpBlockParticlesList[i];
		m_vpBlockParticlesList[i] = 0;
	}
	m_vpBlockParticlesList.clear();
}

void BlockParticleManager::ClearBlockParticleEmitters()
{
	for(unsigned int i = 0; i < m_vpBlockParticleEmittersList.size(); i++)
	{
		delete m_vpBlockParticleEmittersList[i];
		m_vpBlockParticleEmittersList[i] = 0;
	}
	m_vpBlockParticleEmittersList.clear();
}

void BlockParticleManager::ClearBlockParticleEffects()
{
	for(unsigned int i = 0; i < m_vpBlockParticleEffectsList.size(); i++)
	{
		delete m_vpBlockParticleEffectsList[i];
		m_vpBlockParticleEffectsList[i] = 0;
	}
	m_vpBlockParticleEffectsList.clear();
}

void BlockParticleManager::RemoveEmitterLinkage(BlockParticleEmitter* pEmitter)
{
	for(unsigned int i = 0; i < m_vpBlockParticlesList.size(); i++)
	{
		if(m_vpBlockParticlesList[i]->m_pParent == pEmitter)
		{
			m_vpBlockParticlesList[i]->m_pParent = NULL;
		}
	}
}

void BlockParticleManager::SetupGLBuffers()
{
	glShader* pShader = m_pRenderer->GetShader(m_instanceShader);

	GLint in_position = glGetAttribLocation(pShader->GetProgramObject(), "in_position");
	GLint in_normal = glGetAttribLocation(pShader->GetProgramObject(), "in_normal");
	GLint in_color = glGetAttribLocation(pShader->GetProgramObject(), "in_color");
	GLint in_model_matrix = glGetAttribLocation(pShader->GetProgramObject(), "in_model_matrix");

	glBindFragDataLocation(pShader->GetProgramObject(), 0, "outputColor");
	glBindFragDataLocation(pShader->GetProgramObject(), 1, "outputPosition");
	glBindFragDataLocation(pShader->GetProgramObject(), 2, "outputNormal");

	if (m_vertexArray != -1)
	{
		glDeleteVertexArrays(1, &m_vertexArray);
	}

	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	if(m_positionBuffer != -1)
	{
		glDeleteBuffers(1, &m_positionBuffer);
	}
	glGenBuffers(1, &m_positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_positionBuffer);
	int sizeOfVertices = sizeof(vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(in_position);
	glVertexAttribPointer(in_position, 4, GL_FLOAT, 0, 0, 0);

	if(m_normalBuffer != -1)
	{
		glDeleteBuffers(1, &m_normalBuffer);
	}
	glGenBuffers(1, &m_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	int sizeOfNormals = sizeof(normals);
	glBufferData(GL_ARRAY_BUFFER, sizeOfNormals, normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(in_normal);
	glVertexAttribPointer(in_normal, 4, GL_FLOAT, 0, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Accessors
int BlockParticleManager::GetNumBlockParticleEffects()
{
	int numEffects = (int)m_vpBlockParticleEffectsList.size();

	return numEffects;
}

int BlockParticleManager::GetNumBlockParticleEmitters()
{
	int numEmitters = (int)m_vpBlockParticleEmittersList.size();

	return numEmitters;
}

int BlockParticleManager::GetNumBlockParticles()
{
	int numParticles = (int)m_vpBlockParticlesList.size();

	return numParticles;
}

int BlockParticleManager::GetNumRenderableParticles()
{
	int numparticlesToRender = 0;
	for(int i = 0; i < (int)m_vpBlockParticlesList.size(); i++)
	{
		if(m_vpBlockParticlesList[i]->m_createEmitters == true)
		{
			continue;
		}

		if(m_vpBlockParticlesList[i]->m_erase == true)
		{
			continue;
		}

		numparticlesToRender++;
	}

	return numparticlesToRender;
}

// Creation
BlockParticle* BlockParticleManager::CreateBlockParticleFromEmitterParams(BlockParticleEmitter* pEmitter)
{
	vec3 posToSpawn = pEmitter->m_position;
	if(pEmitter->m_particlesFollowEmitter)
	{
		posToSpawn = vec3(0.0f, 0.0f, 0.0f);
	}
	else if(pEmitter->m_pParent != NULL && pEmitter->m_pParentParticle == NULL)
	{
		// If our emitter's parent effect has a position offset
		posToSpawn += pEmitter->m_pParent->m_position;
	}

	vec3 posOffset;
	if(pEmitter->m_emitterType == EmitterType_Point)
	{
		// No position offset since we are emitting from a point
	}
	else if(pEmitter->m_emitterType == EmitterType_Square)
	{
		if(pEmitter->m_spawnOutline)
		{
			float lRandPoint = float((rand()%100)/100.0f);
			int lRandSide = rand()%4;

			vec3 lSquarePosition;
			float lHalfLength = pEmitter->m_emitterLengthX;
			float lHalfWidth = pEmitter->m_emitterLengthZ;
			if(lRandSide == 0)
			{
				lSquarePosition = vec3(pEmitter->m_emitterLengthX*2.0f * lRandPoint - lHalfLength, 0.0f, -lHalfWidth);
			}
			else if(lRandSide == 1)
			{
				lSquarePosition = vec3(pEmitter->m_emitterLengthX*2.0f * lRandPoint - lHalfLength, 0.0f, lHalfWidth);
			}
			else if(lRandSide == 2)
			{
				lSquarePosition = vec3(-lHalfLength, 0.0f, pEmitter->m_emitterLengthZ*2.0f * lRandPoint - lHalfWidth);
			}
			else if(lRandSide == 3)
			{
				lSquarePosition = vec3(lHalfLength, 0.0f, pEmitter->m_emitterLengthZ*2.0f * lRandPoint - lHalfWidth);
			}

			posOffset = lSquarePosition;
		}
		else
		{
			posOffset = vec3(GetRandomNumber(-1, 1, 2)*pEmitter->m_emitterLengthX, 0.0f, GetRandomNumber(-1, 1, 2)*pEmitter->m_emitterLengthZ);
		}
	}
	else if(pEmitter->m_emitterType == EmitterType_Cube)
	{
		// Get a random point around the cube
		float lRandPoint = float((rand()%100)/100.0f);
		int lRandEdge = rand()%12;

		if(pEmitter->m_spawnOutline)
		{
			vec3 lCubePosition;
			float lHalfLength = pEmitter->m_emitterLengthX;
			float lHalfHeight = pEmitter->m_emitterLengthY;
			float lHalfWidth = pEmitter->m_emitterLengthZ;		
			if(lRandEdge == 0)
			{
				lCubePosition = vec3(pEmitter->m_emitterLengthX*2.0f * lRandPoint - lHalfLength, -lHalfHeight, -lHalfWidth);
			}
			else if(lRandEdge == 1)
			{
				lCubePosition = vec3(pEmitter->m_emitterLengthX*2.0f * lRandPoint - lHalfLength, -lHalfHeight, lHalfWidth);
			}
			else if(lRandEdge == 2)
			{
				lCubePosition = vec3(-lHalfLength, -lHalfHeight, pEmitter->m_emitterLengthZ*2.0f * lRandPoint - lHalfWidth);
			}
			else if(lRandEdge == 3)
			{
				lCubePosition = vec3(lHalfLength, -lHalfHeight, pEmitter->m_emitterLengthZ*2.0f * lRandPoint - lHalfWidth);
			}
			else if(lRandEdge == 4)
			{
				lCubePosition = vec3(pEmitter->m_emitterLengthX*2.0f * lRandPoint - lHalfLength, lHalfHeight, -lHalfWidth);
			}
			else if(lRandEdge == 5)
			{
				lCubePosition = vec3(pEmitter->m_emitterLengthX*2.0f * lRandPoint - lHalfLength, lHalfHeight, lHalfWidth);
			}
			else if(lRandEdge == 6)
			{
				lCubePosition = vec3(-lHalfLength, lHalfHeight, pEmitter->m_emitterLengthZ*2.0f * lRandPoint - lHalfWidth);
			}
			else if(lRandEdge == 7)
			{
				lCubePosition = vec3(lHalfLength, lHalfHeight, pEmitter->m_emitterLengthZ*2.0f * lRandPoint - lHalfWidth);
			}
			else if(lRandEdge == 8)
			{
				lCubePosition = vec3(-lHalfLength, pEmitter->m_emitterLengthY*2.0f * lRandPoint - lHalfHeight, -lHalfWidth);
			}
			else if(lRandEdge == 9)
			{
				lCubePosition = vec3(-lHalfLength, pEmitter->m_emitterLengthY*2.0f * lRandPoint - lHalfHeight, lHalfWidth);
			}
			else if(lRandEdge == 10)
			{
				lCubePosition = vec3(lHalfLength, pEmitter->m_emitterLengthY*2.0f * lRandPoint - lHalfHeight, -lHalfWidth);
			}
			else if(lRandEdge == 11)
			{
				lCubePosition = vec3(lHalfLength, pEmitter->m_emitterLengthY*2.0f * lRandPoint - lHalfHeight, lHalfWidth);
			}

			posOffset = lCubePosition;
		}
		else
		{
			posOffset = vec3(GetRandomNumber(-1, 1, 2)*pEmitter->m_emitterLengthX, GetRandomNumber(-1, 1, 2)*pEmitter->m_emitterLengthY, GetRandomNumber(-1, 1, 2)*pEmitter->m_emitterLengthZ);
		}
	}
	else if(pEmitter->m_emitterType == EmitterType_Circle)
	{
		// Get a random point int the circle
		float lRandPoint = float((rand()%100)/100.0f);
		float lAngle = DegToRad(360 * lRandPoint);

		if(pEmitter->m_spawnOutline)
		{
			posOffset = vec3(cos(lAngle) * pEmitter->m_emitterRadius, 0.0f, sin(lAngle) * pEmitter->m_emitterRadius);
		}
		else
		{
			float lRandDistance = pEmitter->m_emitterRadius * (float((rand()%100)/100.0f));
			posOffset = vec3(cos(lAngle) * lRandDistance, 0.0f, sin(lAngle) * lRandDistance);
		}
	}
	else if(pEmitter->m_emitterType == EmitterType_Sphere)
	{
		// Get a random point around the sphere
		float z = 2.0f * float((rand()%1000)/1000.0f) - 1.0f;
		float t = 2.0f * PI * float((rand()%1000)/1000.0f);
		float w = sqrt( 1.0f - z*z );
		float x = w * cos( t );
		float y = w * sin( t );
		vec3 outlinePoint = vec3(x, y, z);

		if(pEmitter->m_spawnOutline)
		{
			posOffset = outlinePoint * pEmitter->m_emitterRadius;
		}
		else
		{
			float randomDist = GetRandomNumber(0, 1, 2);
			posOffset = outlinePoint * pEmitter->m_emitterRadius * randomDist;
		}
	}
	else if(pEmitter->m_emitterType == EmitterType_Mesh)
	{
	}

	posToSpawn += posOffset;

	// Get the create emitter
	BlockParticleEmitter* pCreateEmitterParam = NULL;
	BlockParticleEmitter* pCreatedEmitter = NULL;
	if(pEmitter->m_createEmitters)
	{
		pCreateEmitterParam = pEmitter->m_pParent->GetEmitter(pEmitter->m_createEmitterName);

		pCreatedEmitter = CreateBlockParticleEmitter("CreatedEmitter", vec3(0.0f, 0.0f, 0.0f));
		pCreatedEmitter->CopyParams(pCreateEmitterParam);
	}

	BlockParticle* pBlockParticle = CreateBlockParticle(posToSpawn, pEmitter->m_gravityDirection, pEmitter->m_gravityMultiplier, pEmitter->m_pointOrigin,
		pEmitter->m_startScale, pEmitter->m_startScaleVariance, pEmitter->m_endScale, pEmitter->m_endScaleVariance,
		pEmitter->m_startRed, pEmitter->m_startGreen, pEmitter->m_startBlue, pEmitter->m_startAlpha,
		pEmitter->m_startRedVariance, pEmitter->m_startGreenVariance, pEmitter->m_startBlueVariance, pEmitter->m_startAlphaVariance,
		pEmitter->m_endRed, pEmitter->m_endGreen, pEmitter->m_endBlue, pEmitter->m_endAlpha,
		pEmitter->m_endRedVariance, pEmitter->m_endGreenVariance, pEmitter->m_endBlueVariance, pEmitter->m_endAlphaVariance,
		pEmitter->m_lifeTime, pEmitter->m_lifeTimeVariance,
		pEmitter->m_velocityTowardsPoint, pEmitter->m_accelerationTowardsPoint,
		pEmitter->m_startVelocity, pEmitter->m_startVelocityVariance,
		pEmitter->m_startAngularVelocity, pEmitter->m_startAngularVelocityVariance,
		pEmitter->m_tangentialVelocityXY, pEmitter->m_tangentialAccelerationXY, pEmitter->m_tangentialVelocityXZ, pEmitter->m_tangentialAccelerationXZ, pEmitter->m_tangentialVelocityYZ, pEmitter->m_tangentialAccelerationYZ,
		pEmitter->m_randomStartRotation, pEmitter->m_startRotation, pEmitter->m_checkWorldCollisions, pEmitter->m_destoryOnCollision, pEmitter->m_startLifeDecayOnCollision,
		pEmitter->m_createEmitters, pCreatedEmitter);

	if(pBlockParticle != NULL)
	{
		// Set parent to emitter
		pBlockParticle->m_pParent = pEmitter;
	}

	return pBlockParticle;
}

BlockParticle* BlockParticleManager::CreateBlockParticle(vec3 pos, vec3 gravityDir, float gravityMultiplier, vec3 pointOrigin,
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
	bool randomStartRotation, vec3 startRotation,  bool worldCollision, bool destoryOnCollision, bool startLifeDecayOnCollision,
	bool createEmitters, BlockParticleEmitter* pCreatedEmitter)
{
	BlockParticle* pBlockParticle = new BlockParticle();

	pBlockParticle->m_position = pos;
	pBlockParticle->m_gravityDirection = gravityDir;
	pBlockParticle->m_gravityMultiplier = gravityMultiplier;

	pBlockParticle->m_startScale = startScale;
	pBlockParticle->m_startScaleVariance = startScaleVariance;
	pBlockParticle->m_endScale = endScale;
	pBlockParticle->m_endScaleVariance = endScaleVariance;

	pBlockParticle->m_startRed = startR;
	pBlockParticle->m_startRedVariance = startRVariance;
	pBlockParticle->m_startGreen = startG;
	pBlockParticle->m_startGreenVariance = startGVariance;
	pBlockParticle->m_startBlue = startB;
	pBlockParticle->m_startBlueVariance = startBVariance;
	pBlockParticle->m_startAlpha = startA;
	pBlockParticle->m_startAlphaVariance = startAVariance;
	pBlockParticle->m_endRed = endR;
	pBlockParticle->m_endRedVariance = endRVariance;
	pBlockParticle->m_endGreen = endG;
	pBlockParticle->m_endGreenVariance = endGVariance;
	pBlockParticle->m_endBlue = endB;
	pBlockParticle->m_endBlueVariance = endBVariance;
	pBlockParticle->m_endAlpha = endA;
	pBlockParticle->m_endAlphaVariance = endAVariance;

	pBlockParticle->m_pointOrigin = pointOrigin;
	pBlockParticle->m_velocityTowardsPoint = velocityTowardPoint;
	pBlockParticle->m_accelerationTowardsPoint = accelerationTowardsPoint;

	pBlockParticle->m_tangentialVelocityXY = tangentialVelocityXY;
	pBlockParticle->m_tangentialAccelerationXY = tangentialAccelerationXY;
	pBlockParticle->m_tangentialVelocityXZ = tangentialVelocityXZ;
	pBlockParticle->m_tangentialAccelerationXZ = tangentialAccelerationXZ;
	pBlockParticle->m_tangentialVelocityYZ = tangentialVelocityYZ;
	pBlockParticle->m_tangentialAccelerationYZ = tangentialAccelerationYZ;

	pBlockParticle->m_velocity = startVelocity;
	pBlockParticle->m_startVelocityVariance = startVelocityVariance;

	pBlockParticle->m_angularVelocity = startAngularVelocity;
	pBlockParticle->m_startAngularVelocityVariance = startAngularVelocityVariance;

	pBlockParticle->m_lifeTime = lifetime;
	pBlockParticle->m_maxLifeTime = lifetime;
	pBlockParticle->m_lifeTimeVariance = lifetimeVariance;

	pBlockParticle->m_checkWorldCollisions = worldCollision;
	pBlockParticle->m_destoryOnCollision = destoryOnCollision;
	pBlockParticle->m_startLifeDecayOnCollision = startLifeDecayOnCollision;

	pBlockParticle->m_startRotation = startRotation;
	pBlockParticle->m_randomStartRotation = randomStartRotation;

	pBlockParticle->m_createEmitters = createEmitters;
	pBlockParticle->m_pCreatedEmitter = pCreatedEmitter;

	pBlockParticle->m_erase = false;

	pBlockParticle->CreateStartingParams();

	m_vpBlockParticlesList.push_back(pBlockParticle);

	return pBlockParticle;
}

BlockParticleEmitter* BlockParticleManager::CreateBlockParticleEmitter(string name, vec3 pos)
{
	BlockParticleEmitter* pBlockParticleEmitter = new BlockParticleEmitter(m_pRenderer, this);

	pBlockParticleEmitter->m_emitterName = name;
	pBlockParticleEmitter->m_startingPosition = pos;
	pBlockParticleEmitter->m_position = pos;

	pBlockParticleEmitter->m_erase = false;

	m_vpBlockParticleEmittersAddList.push_back(pBlockParticleEmitter);

	return pBlockParticleEmitter;
}

BlockParticleEffect* BlockParticleManager::ImportParticleEffect(string fileName, vec3 pos, unsigned int* particleEffectId)
{
	BlockParticleEffect* pBlockParticleEffect = new BlockParticleEffect(m_pRenderer, this);

	pBlockParticleEffect->Import(fileName.c_str());

	pBlockParticleEffect->m_effectName = fileName;
	pBlockParticleEffect->m_position = pos;

	pBlockParticleEffect->m_particleEffectId = m_particleEffectCounter;
	*particleEffectId = m_particleEffectCounter;
	m_particleEffectCounter++;

	pBlockParticleEffect->m_erase = false;

	m_vpBlockParticleEffectsList.push_back(pBlockParticleEffect);

	pBlockParticleEffect->PlayEffect();

	return pBlockParticleEffect;
}

void BlockParticleManager::DestroyParticleEffect(unsigned int particleEffectId)
{
	for(unsigned int i = 0; i < m_vpBlockParticleEffectsList.size(); i++)
	{
		if(m_vpBlockParticleEffectsList[i]->m_particleEffectId == particleEffectId)
		{
			m_vpBlockParticleEffectsList[i]->ClearEmitters();
			m_vpBlockParticleEffectsList[i]->m_erase = true;
		}
	}
}

void BlockParticleManager::UpdateParticleEffectPosition(unsigned int particleEffectId, vec3 position)
{
	for(unsigned int i = 0; i < m_vpBlockParticleEffectsList.size(); i++)
	{
		if(m_vpBlockParticleEffectsList[i]->m_particleEffectId == particleEffectId)
		{
			m_vpBlockParticleEffectsList[i]->m_position = position;

			return;
		}
	}
}

void BlockParticleManager::ExplodeQubicleBinary(QubicleBinary* pQubicleBinary, float scale, int particleSpawnChance)
{
	if(pQubicleBinary != NULL)
	{
		for (int i = 0; i < pQubicleBinary->GetNumMatrices(); i++)
		{
			QubicleMatrix* pMatrix = pQubicleBinary->GetQubicleMatrix(i);

			float r = 1.0f;
			float g = 1.0f;
			float b = 1.0f;
			float a = 1.0f;	
			bool singleMeshColour = pQubicleBinary->GetSingleMeshColour(&r, &g, &b, &a);
			ExplodeQubicleMatrix(pMatrix, scale, particleSpawnChance, singleMeshColour, r, g, b, a);
		}
	}
}

void BlockParticleManager::ExplodeQubicleMatrix(QubicleMatrix* pMatrix, float scale, int particleSpawnChance, bool allSameColour, float sameR, float sameG, float sameB, float sameA)
{
	if(pMatrix != NULL)
	{
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;	

		for(unsigned int x = 0; x < pMatrix->m_matrixSizeX; x++)
		{
			for(unsigned int y = 0; y < pMatrix->m_matrixSizeY; y++)
			{
				for(unsigned int z = 0; z < pMatrix->m_matrixSizeZ; z++)
				{
					if(pMatrix->GetActive(x, y, z) == false)
					{
						continue;
					}
					else
					{
						if(GetRandomNumber(0, 100) > particleSpawnChance)
						{
							// Don't ALWAYS spawn ALL blocks.
							continue;
						}

						if(allSameColour)
						{
							r = sameR;
							g = sameG;
							b = sameB;
							a = sameA;	
						}
						else
						{
							pMatrix->GetColour(x, y, z, &r, &g, &b, &a);
						}						

						a = 1.0f;

						vec3 blockPosition = vec3((float)x, (float)y, (float)z);

						float startScale = scale;
						float endScale = scale;
						startScale *= GetRandomNumber(90, 100, 2) * 0.01f;
						endScale *= GetRandomNumber(25, 75, 2) * 0.01f;

						vec3 new_blockPosition;
						Matrix4x4::Multiply(pMatrix->m_modelMatrix, blockPosition, new_blockPosition);
						blockPosition = new_blockPosition;

						float rotX; float rotY; float rotZ;
						pMatrix->m_modelMatrix.GetEuler(&rotX, &rotY, &rotZ);

						vec3 center = vec3((float)pMatrix->m_matrixSizeX*0.5f, (float)pMatrix->m_matrixSizeY*0.5f, (float)pMatrix->m_matrixSizeZ*0.5f);

						vec3 new_center;
						Matrix4x4::Multiply(pMatrix->m_modelMatrix, center, new_center);
						center = new_center;

						vec3 toOrigin = normalize(center - blockPosition);

						float lifeTime = 4.0f + GetRandomNumber(-100, 200, 1) * 0.0075f;

						vec3 gravity = vec3(0.0f, -1.0f, 0.0f);
						vec3 pointOrigin = vec3(0.0f, 0.0f, 0.0f);
						BlockParticle* pParticle = CreateBlockParticle(blockPosition, gravity, 1.5f, pointOrigin, startScale, 0.0f, endScale, 0.0f, r, g, b, a, 0.0f, 0.0f, 0.0f, 0.0f, r, g, b, a, 0.0f, 0.0f, 0.0f, 0.0f, lifeTime, 0.0f, 0.0f, 0.0f, -toOrigin+ vec3(0.0f, 2.0f, 0.0f), vec3(0.85f, 2.0f, 0.85f), vec3(0.0f, 0.0f, 0.0f), vec3(180.0f, 180.0f, 180.0f), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, vec3(rotX, rotY, rotZ), true, false, false, false, NULL);
						if(pParticle != NULL)
						{
							pParticle->m_allowFloorSliding = true;
						}
					}
				}
			}
		}
	}
}

bool needs_erasing_blockparticle_effect(BlockParticleEffect* aB)
{
	bool needsErase = aB->m_erase;

	if(needsErase == true)
	{
		delete aB;
	}

	return needsErase;
}

bool needs_erasing_blockparticle_emitter(BlockParticleEmitter* aB)
{
	bool needsErase = aB->m_erase;

	if(needsErase == true)
	{
		delete aB;
	}

	return needsErase;
}

bool needs_erasing_blockparticle(BlockParticle* aB)
{
	bool needsErase = aB->m_erase;

	if(needsErase == true)
	{
		delete aB;
	}

	return needsErase;
}

// Rendering modes
void BlockParticleManager::SetWireFrameRender(bool wireframe)
{
	m_renderWireFrame = wireframe;
}

// Update
void BlockParticleManager::Update(float dt)
{
	// Update block particle emitters
	m_vpBlockParticleEmittersList.erase( remove_if(m_vpBlockParticleEmittersList.begin(), m_vpBlockParticleEmittersList.end(), needs_erasing_blockparticle_emitter), m_vpBlockParticleEmittersList.end() );

	// Add any new emitters
	for(unsigned int i = 0; i < m_vpBlockParticleEmittersAddList.size(); i++)
	{
		BlockParticleEmitter* lpAddedBlockParticleEmitter = m_vpBlockParticleEmittersAddList[i];
		m_vpBlockParticleEmittersList.push_back(lpAddedBlockParticleEmitter);
	}
	m_vpBlockParticleEmittersAddList.clear();

	for(unsigned int i = 0; i < m_vpBlockParticleEmittersList.size(); i++)
	{
		BlockParticleEmitter* lpBlockParticleEmitter = m_vpBlockParticleEmittersList[i];

		lpBlockParticleEmitter->Update(dt);
	}


	// Update particle effects
	m_vpBlockParticleEffectsList.erase( remove_if(m_vpBlockParticleEffectsList.begin(), m_vpBlockParticleEffectsList.end(), needs_erasing_blockparticle_effect), m_vpBlockParticleEffectsList.end() );

	for(unsigned int i = 0; i < m_vpBlockParticleEffectsList.size(); i++)
	{
		BlockParticleEffect* lpBlockParticleEffect = m_vpBlockParticleEffectsList[i];

		lpBlockParticleEffect->Update(dt);
	}


	// Update block particles
	for(unsigned int i = 0; i < m_vpBlockParticlesList.size(); i++)
	{
		BlockParticle* lpBlockParticle = m_vpBlockParticlesList[i];

		if(lpBlockParticle->m_lifeTime <= 0.0f)
		{
			if(lpBlockParticle->m_waitAfterUpdateCompleteTimer <= 0.0f)
			{
				// If we have elapsed our timer, then erase the effect and continue
				lpBlockParticle->m_erase = true;

				continue;
			}
		}

		lpBlockParticle->Update(dt);
	}

	m_vpBlockParticlesList.erase( remove_if(m_vpBlockParticlesList.begin(), m_vpBlockParticlesList.end(), needs_erasing_blockparticle), m_vpBlockParticlesList.end() );
}

// Rendering
void BlockParticleManager::Render()
{
	glShader* pShader = m_pRenderer->GetShader(m_instanceShader);

	GLint in_position = glGetAttribLocation(pShader->GetProgramObject(), "in_position");
	GLint in_color = glGetAttribLocation(pShader->GetProgramObject(), "in_color");
	GLint in_model_matrix = glGetAttribLocation(pShader->GetProgramObject(), "in_model_matrix");

	int numBlockParticles = (int)m_vpBlockParticlesList.size();
	int numBlockParticlesRender = GetNumRenderableParticles();
	if(numBlockParticlesRender > 0)
	{
		float* newMatrices = new float[16 * numBlockParticlesRender];
		float* newColors = new float[4 * numBlockParticlesRender];

		int counter = 0;
		for(int i = 0; i < numBlockParticles; i++)
		{
			if(m_vpBlockParticlesList[i]->m_createEmitters == true)
			{
				continue;
			}

			if(m_vpBlockParticlesList[i]->m_erase == true)
			{
				continue;
			}

			newColors[counter+0] = m_vpBlockParticlesList[i]->m_currentRed;
			newColors[counter+1] = m_vpBlockParticlesList[i]->m_currentGreen;
			newColors[counter+2] = m_vpBlockParticlesList[i]->m_currentBlue;
			newColors[counter+3] = m_vpBlockParticlesList[i]->m_currentAlpha;
			counter+=4;
		}
		counter = 0;
		for(int i = 0; i < numBlockParticles; i++)
		{
			if(m_vpBlockParticlesList[i]->m_createEmitters == true)
			{
				continue;
			}

			m_vpBlockParticlesList[i]->CalculateWorldTransformMatrix();

			newMatrices[counter+0] = m_vpBlockParticlesList[i]->m_worldMatrix.m[0];
			newMatrices[counter+1] = m_vpBlockParticlesList[i]->m_worldMatrix.m[1];
			newMatrices[counter+2] = m_vpBlockParticlesList[i]->m_worldMatrix.m[2];
			newMatrices[counter+3] = m_vpBlockParticlesList[i]->m_worldMatrix.m[3];
			newMatrices[counter+4] = m_vpBlockParticlesList[i]->m_worldMatrix.m[4];
			newMatrices[counter+5] = m_vpBlockParticlesList[i]->m_worldMatrix.m[5];
			newMatrices[counter+6] = m_vpBlockParticlesList[i]->m_worldMatrix.m[6];
			newMatrices[counter+7] = m_vpBlockParticlesList[i]->m_worldMatrix.m[7];
			newMatrices[counter+8] = m_vpBlockParticlesList[i]->m_worldMatrix.m[8];
			newMatrices[counter+9] = m_vpBlockParticlesList[i]->m_worldMatrix.m[9];
			newMatrices[counter+10] = m_vpBlockParticlesList[i]->m_worldMatrix.m[10];
			newMatrices[counter+11] = m_vpBlockParticlesList[i]->m_worldMatrix.m[11];
			newMatrices[counter+12] = m_vpBlockParticlesList[i]->m_worldMatrix.m[12];
			newMatrices[counter+13] = m_vpBlockParticlesList[i]->m_worldMatrix.m[13];
			newMatrices[counter+14] = m_vpBlockParticlesList[i]->m_worldMatrix.m[14];
			newMatrices[counter+15] = m_vpBlockParticlesList[i]->m_worldMatrix.m[15];
			counter+=16;
		}

		glBindVertexArray(m_vertexArray);

		if(m_colourBuffer != -1)
		{
			glDeleteBuffers(1, &m_colourBuffer);
		}
		// Bind buffer for colors and copy data into buffer
		glGenBuffers(1, &m_colourBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_colourBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*numBlockParticlesRender, newColors, GL_STATIC_READ);
		glEnableVertexAttribArray(in_color);
		glVertexAttribPointer(in_color, 4, GL_FLOAT, GL_FALSE, 4*4, 0);
		glVertexAttribDivisor(in_color, 1);

		if(m_matrixBuffer != -1)
		{
			glDeleteBuffers(1, &m_matrixBuffer);
		}
		// Bind buffer for matrix and copy data into buffer
		glGenBuffers(1, &m_matrixBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_matrixBuffer);
		for (int i = 0; i < 4; i++)
		{
			glVertexAttribPointer(in_model_matrix + i,		// Location
								  4, GL_FLOAT, GL_FALSE,	// vec4
								  4*16,						// Stride
								  (void *)(16 * i));		// Start offset

			glEnableVertexAttribArray(in_model_matrix + i);
			glVertexAttribDivisor(in_model_matrix + i, 1);
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*16*numBlockParticlesRender, newMatrices, GL_STATIC_READ);

		delete newColors;
		delete newMatrices;
	}

	// Render the block particle instances
	m_pRenderer->BeginGLSLShader(m_instanceShader);

	GLint projMatrixLoc = glGetUniformLocation(pShader->GetProgramObject(), "projMatrix");
	GLint viewMatrixLoc = glGetUniformLocation(pShader->GetProgramObject(), "viewMatrix");
	
	Matrix4x4 projMat;
	Matrix4x4 viewMat;
	m_pRenderer->GetProjectionMatrix(&projMat);
	m_pRenderer->GetModelViewMatrix(&viewMat);

	glUniformMatrix4fv(projMatrixLoc,  1, false, projMat.m);
	glUniformMatrix4fv(viewMatrixLoc,  1, false, viewMat.m);

	GLint in_light_position = glGetUniformLocation(pShader->GetProgramObject(), "in_light_position");
	GLint in_light_const_a = glGetUniformLocation(pShader->GetProgramObject(), "in_light_const_a");
	GLint in_light_linear_a = glGetUniformLocation(pShader->GetProgramObject(), "in_light_linear_a");
	GLint in_light_quad_a = glGetUniformLocation(pShader->GetProgramObject(), "in_light_quad_a");
	GLint in_light_ambient = glGetUniformLocation(pShader->GetProgramObject(), "in_light_ambient");
	GLint in_light_diffuse = glGetUniformLocation(pShader->GetProgramObject(), "in_light_diffuse");

	//vec3 position = m_pRenderer->GetLightPosition(m_pGameWindow->GetMainLightId());
	//Colour ambient = m_pRenderer->GetLightAmbient(m_pGameWindow->GetMainLightId());
	//Colour diffuse = m_pRenderer->GetLightDiffuse(m_pGameWindow->GetMainLightId());
	//float constantA = m_pRenderer->GetConstantAttenuation(m_pGameWindow->GetMainLightId());
	//float linearA = m_pRenderer->GetLinearAttenuation(m_pGameWindow->GetMainLightId());
	//float quadA = m_pRenderer->GetQuadraticAttenuation(m_pGameWindow->GetMainLightId());
	//glUniform4f(in_light_position, position.x, position.y, position.z, 1.0f);
	//glUniform4f(in_light_diffuse, diffuse.GetRed(), diffuse.GetGreen(), diffuse.GetBlue(), 1.0);
	//glUniform4f(in_light_ambient, ambient.GetRed(), ambient.GetGreen(), ambient.GetBlue(), 1.0);
	//glUniform1f(in_light_const_a, constantA*0.5f);
	//glUniform1f(in_light_linear_a, linearA*0.5f);
	//glUniform1f(in_light_quad_a, quadA*0.5f);

	if (m_renderWireFrame)
	{
		m_pRenderer->SetLineWidth(1.0f);
		m_pRenderer->SetRenderMode(RM_WIREFRAME);
		m_pRenderer->SetCullMode(CM_NOCULL);
	}
	else
	{
		m_pRenderer->SetCullMode(CM_BACK);
		m_pRenderer->SetRenderMode(RM_SOLID);
	}

	m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);

	glDrawElementsInstanced(GL_QUADS, 24, GL_UNSIGNED_INT, indices, numBlockParticlesRender);

	m_pRenderer->DisableTransparency();

	m_pRenderer->EndGLSLShader(m_instanceShader);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BlockParticleManager::RenderDebug()
{
	RenderEmitters();
	RenderEffects();
}

void BlockParticleManager::RenderEmitters()
{
	for(unsigned int i = 0; i < m_vpBlockParticleEmittersList.size(); i++)
	{
		BlockParticleEmitter* lpBlockParticleEmitter = m_vpBlockParticleEmittersList[i];

		lpBlockParticleEmitter->Render();
	}
}

void BlockParticleManager::RenderEffects()
{
	for(unsigned int i = 0; i < m_vpBlockParticleEffectsList.size(); i++)
	{
		BlockParticleEffect* lpBlockParticleEffect = m_vpBlockParticleEffectsList[i];

		lpBlockParticleEffect->Render();
	}
}