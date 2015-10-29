// ******************************************************************************
//
// Filename:	BlockParticle.cpp
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

#include "BlockParticle.h"
#include "BlockParticleEmitter.h"
#include "BlockParticleEffect.h"

#include "../utils/Random.h"


BlockParticle::BlockParticle()
{
	m_erase = false;

	m_allowFloorSliding = false;

	m_gridPositionX = 0;
	m_gridPositionY = 0;
	m_gridPositionZ = 0;

	m_pParent = NULL;

	m_hasCollided = false;

	m_createEmitters = false;
	m_pCreatedEmitter = NULL;

	m_freezeUpdateTimer = 0.0f;
	m_waitAfterUpdateCompleteTimer = 0.0f;
}

BlockParticle::~BlockParticle()
{
	if(m_createEmitters == true && m_pCreatedEmitter != NULL)
	{
		m_pCreatedEmitter->m_pParentParticle = NULL;
		m_pCreatedEmitter->m_erase = true;
	}
}


void BlockParticle::CreateStartingParams()
{
	m_startScale = m_startScale + ((GetRandomNumber(-1, 1, 2) * m_startScaleVariance) * m_startScale);
	m_endScale = m_endScale + ((GetRandomNumber(-1, 1, 2) * m_endScaleVariance) * m_endScale);
	m_currentScale = m_startScale;

	m_startRed = m_startRed + (GetRandomNumber(-1, 1, 2) * m_startRedVariance);
	m_endRed = m_endRed + (GetRandomNumber(-1, 1, 2) * m_endRedVariance);
	m_currentRed = m_startRed;

	m_startGreen = m_startGreen + (GetRandomNumber(-1, 1, 2) * m_startGreenVariance);
	m_endGreen = m_endGreen + (GetRandomNumber(-1, 1, 2) * m_endGreenVariance);
	m_currentGreen = m_startGreen;

	m_startBlue = m_startBlue + (GetRandomNumber(-1, 1, 2) * m_startBlueVariance);
	m_endBlue = m_endBlue + (GetRandomNumber(-1, 1, 2) * m_endBlueVariance);
	m_currentBlue = m_startBlue;

	m_startAlpha = m_startAlpha + (GetRandomNumber(-1, 1, 2) * m_startAlphaVariance);
	m_endAlpha = m_endAlpha + (GetRandomNumber(-1, 1, 2) * m_endAlphaVariance);
	m_currentAlpha = m_startAlpha;

	m_lifeTime = m_lifeTime + ((GetRandomNumber(-1, 1, 2) * m_lifeTimeVariance) * m_lifeTime);
	m_maxLifeTime = m_lifeTime;

	m_velocity = m_velocity + vec3(GetRandomNumber(-100, 100, 2)*0.01f*m_startVelocityVariance.x, GetRandomNumber(-100, 100, 2)*0.01f*m_startVelocityVariance.y, GetRandomNumber(-100, 100, 2)*0.01f*m_startVelocityVariance.z);
	m_angularVelocity = m_angularVelocity + vec3(GetRandomNumber(-100, 100, 2)*0.01f*m_startAngularVelocityVariance.x, GetRandomNumber(-100, 100, 2)*0.01f*m_startAngularVelocityVariance.y, GetRandomNumber(-100, 100, 2)*0.01f*m_startAngularVelocityVariance.z);

	if(m_randomStartRotation)
	{
		m_rotation = vec3(GetRandomNumber(-360, 360, 2), GetRandomNumber(-360, 360, 2), GetRandomNumber(-360, 360, 2));
	}
	else
	{
		m_rotation = m_startRotation;
	}
}

void BlockParticle::CalculateWorldTransformMatrix()
{
	m_worldMatrix.LoadIdentity();
	m_worldMatrix.SetRotation(DegToRad(m_rotation.x), DegToRad(m_rotation.y), DegToRad(m_rotation.z));

	vec3 pos = m_position;
	if(m_pParent != NULL && m_pParent->m_particlesFollowEmitter)
	{
		// If we have a parent and we are locked to their position
		pos += m_pParent->m_position;

		if(m_pParent->m_pParent != NULL)
		{
			// If our emitter's parent effect has a position offset
			pos += m_pParent->m_pParent->m_position;
		}
	}

	m_worldMatrix.SetTranslation(vec3(pos.x, pos.y, pos.z));

	Matrix4x4 scaleMat;
	scaleMat.SetScale(vec3(m_currentScale, m_currentScale, m_currentScale));

	m_worldMatrix = scaleMat * m_worldMatrix;
}

void BlockParticle::SetFreezeDelayTimer(float timer)
{
	m_freezeUpdateTimer = timer;
}

void BlockParticle::SetWaitAfterUpdateCompleteTimer(float timer)
{
	m_waitAfterUpdateCompleteTimer = timer;
}

// Update
void BlockParticle::Update(float dt)
{
	if(m_erase)
	{
		return;
	}

	if(m_pParent != NULL && m_pParent->m_paused == true)
	{
		// If our parent emitter is paused, return
		return;
	}

	// Update particle life
	if(m_startLifeDecayOnCollision == false || m_hasCollided == true)
	{
		m_lifeTime -= dt;

		if(m_lifeTime < 0.0f)
		{
			m_lifeTime = 0.0f;
		}
	}

	// If we are frozen, return and don't do any physics updating
	if(m_freezeUpdateTimer >= 0.0f)
	{
		m_freezeUpdateTimer -= dt;

		return;
	}

	if(m_lifeTime > 0.0f)
	{
		if(m_pParent != NULL)
		{
			// Velocity towards point origin
			vec3 pointOrigin = m_pointOrigin;
			if(m_pParent != NULL && m_pParent->m_particlesFollowEmitter == false)
			{
				if(m_pParent->m_pParent != NULL)
				{
					pointOrigin += m_pParent->m_pParent->m_position; // Add on parent's particle effect position
				}
			}
			vec3 toPoint = pointOrigin - m_position;
			if(length(toPoint) > 0.001f)
			{
				m_velocityTowardsPoint += m_accelerationTowardsPoint * dt;
				vec3 velToPoint = toPoint * m_velocityTowardsPoint;
				m_pointVelocity += (velToPoint) * dt;

				// Tangential velocity
				vec3 x_axis = vec3(m_velocity.y<0.0f?-1.0f:1.0f, 0.0f, 0.0f);
				vec3 cross_x = cross(toPoint, x_axis);
				vec3 y_axis = vec3(0.0f, m_velocity.z<0.0f?-1.0f:1.0f, 0.0f);
				vec3 cross_y = cross(toPoint, y_axis);
				vec3 z_axis = vec3(0.0f, 0.0f, m_velocity.y<0.0f?-1.0f:1.0f);
				vec3 cross_z = cross(toPoint, z_axis);

				m_tangentialVelocityXY += m_tangentialAccelerationXY * dt;
				m_tangentialVelocityXZ += m_tangentialAccelerationXZ * dt;
				m_tangentialVelocityYZ += m_tangentialAccelerationYZ * dt;
				vec3 velTangentXY = (cross_z/* * toPoint.GetLength()*/) * m_tangentialVelocityXY;
				vec3 velTangentXZ = (cross_y/* * toPoint.GetLength()*/) * m_tangentialVelocityXZ;
				vec3 velTangentYZ = (cross_x/* * toPoint.GetLength()*/) * m_tangentialVelocityYZ;
				
				m_tangentialVelocity = velTangentXY+velTangentXZ+velTangentYZ;
			}
		}

		// Position integration
		vec3 acceleration = (m_gravityDirection * 9.81f) * m_gravityMultiplier;
		m_velocity += acceleration * dt;
		m_position += m_velocity * dt;

		// Point origin and tangential velocity
		m_position += m_tangentialVelocity * dt;
		m_position += m_pointVelocity * dt;

		// Rotation integration
		vec3 angularAcceleration(0.0f, 0.0f, 0.0f);
		m_angularVelocity += angularAcceleration * dt;
		m_rotation += m_angularVelocity * dt;

		if(m_checkWorldCollisions)
		{
			if(m_position.y < -2.0f)
			{
				m_erase = true;
			}
		}
	}
	else
	{
		if(m_waitAfterUpdateCompleteTimer > 0.0f)
		{
			m_waitAfterUpdateCompleteTimer -= dt;
		}
	}

	float timeRatio = (m_lifeTime+m_freezeUpdateTimer) / (m_maxLifeTime+m_freezeUpdateTimer);

	// Update colour
	m_currentRed = m_startRed + ((m_endRed - m_startRed) * (1.0f - timeRatio));
	m_currentGreen = m_startGreen + ((m_endGreen - m_startGreen) * (1.0f - timeRatio));
	m_currentBlue = m_startBlue + ((m_endBlue - m_startBlue) * (1.0f - timeRatio));
	m_currentAlpha = m_startAlpha + ((m_endAlpha - m_startAlpha) * (1.0f - timeRatio));

	// Update scale
	m_currentScale = m_startScale + ((m_endScale - m_startScale) * (1.0f - timeRatio));

	if(m_createEmitters == true && m_pCreatedEmitter != NULL)
	{
		m_pCreatedEmitter->m_pParentParticle = this;
		m_pCreatedEmitter->m_position = m_position;
	}
}