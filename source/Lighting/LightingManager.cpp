// ******************************************************************************
//
// Filename:	LightingManager.cpp
// Project:		Game
// Author:		Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 20/01/13
//
// Copyright (c) 2005-2011, Steven Ball
//
// ******************************************************************************

#include "LightingManager.h"

#include <algorithm>


LightingManager::LightingManager(Renderer* pRenderer)
{
	m_pRenderer = pRenderer;

	m_lightIndexCounter = 0;
}

LightingManager::~LightingManager()
{
	ClearLights();
}

int LightingManager::GetNumLights()
{
	int numLights = (int)m_vpDynamicLightList.size();

	return numLights;
}

DynamicLight* LightingManager::GetLight(int index)
{
	DynamicLight* pLight = m_vpDynamicLightList[index];

	return pLight;
}

void LightingManager::ClearLights()
{
	for(unsigned int i = 0; i < m_vpDynamicLightList.size(); i++)
	{
		delete m_vpDynamicLightList[i];
		m_vpDynamicLightList[i] = 0;
	}
	m_vpDynamicLightList.clear();
}

void LightingManager::AddLight(vec3 position, float radius, float diffuseModifier, Colour colour, unsigned int *pID)
{
	DynamicLight* pNewLight = new DynamicLight();

	pNewLight->m_position = position;
	pNewLight->m_radius = radius;
	pNewLight->m_diffuseScale = diffuseModifier;
	pNewLight->m_colour = colour;
	pNewLight->m_lightId = m_lightIndexCounter;

	*pID = m_lightIndexCounter;

	m_lightIndexCounter++;

	m_vpDynamicLightList.push_back(pNewLight);
}

void LightingManager::AddDyingLight(vec3 position, float radius, float diffuseModifier, Colour colour, float lifeTime, unsigned int *pID)
{
	DynamicLight* pNewLight = new DynamicLight();

	pNewLight->m_position = position;
	pNewLight->m_radius = radius;
	pNewLight->m_diffuseScale = diffuseModifier;
	pNewLight->m_colour = colour;
	pNewLight->m_lightId = m_lightIndexCounter;

	pNewLight->m_lifeTime = lifeTime;
	pNewLight->m_maxLifeTime = lifeTime;
	pNewLight->m_dyingLight = true;

	*pID = m_lightIndexCounter;

	m_lightIndexCounter++;

	m_vpDynamicLightList.push_back(pNewLight);
}

bool needs_erasing(DynamicLight* aL)
{
	bool needsErase = aL->NeedsErasing();

	if(needsErase == true)
	{
		delete aL;
	}

	return needsErase;
}

void LightingManager::RemoveLight(unsigned int lightId)
{
	for(unsigned int i = 0; i < m_vpDynamicLightList.size(); i++)
	{
		if(m_vpDynamicLightList[i]->m_lightId == lightId)
		{
			m_vpDynamicLightList[i]->SetErase(true);
		}
	}

	// Remove any lights that need to be erased
	m_vpDynamicLightList.erase( remove_if(m_vpDynamicLightList.begin(), m_vpDynamicLightList.end(), needs_erasing), m_vpDynamicLightList.end() );
}

void LightingManager::UpdateLight(unsigned int lightId, vec3 position, float radius, float diffuseModifier, Colour colour)
{
	for(unsigned int i = 0; i < m_vpDynamicLightList.size(); i++)
	{
		if(m_vpDynamicLightList[i]->m_lightId == lightId)
		{
			m_vpDynamicLightList[i]->m_position = position;
			m_vpDynamicLightList[i]->m_radius = radius;
			m_vpDynamicLightList[i]->m_diffuseScale = diffuseModifier;
			m_vpDynamicLightList[i]->m_colour = colour;

			return;
		}
	}
}

void LightingManager::UpdateLightRadius(unsigned int lightId, float radius)
{
	for(unsigned int i = 0; i < m_vpDynamicLightList.size(); i++)
	{
		if(m_vpDynamicLightList[i]->m_lightId == lightId)
		{
			m_vpDynamicLightList[i]->m_radius = radius;

			return;
		}
	}
}

void LightingManager::UpdateLightDiffuseMultiplier(unsigned int lightId, float diffuseMultiplier)
{
	for(unsigned int i = 0; i < m_vpDynamicLightList.size(); i++)
	{
		if(m_vpDynamicLightList[i]->m_lightId == lightId)
		{
			m_vpDynamicLightList[i]->m_diffuseScale = diffuseMultiplier;

			return;
		}
	}
}

void LightingManager::UpdateLightPosition(unsigned int lightId, vec3 position)
{
	for(unsigned int i = 0; i < m_vpDynamicLightList.size(); i++)
	{
		if(m_vpDynamicLightList[i]->m_lightId == lightId)
		{
			m_vpDynamicLightList[i]->m_position = position;

			return;
		}
	}
}

void LightingManager::UpdateLightColour(unsigned int lightId, Colour colour)
{
	for(unsigned int i = 0; i < m_vpDynamicLightList.size(); i++)
	{
		if(m_vpDynamicLightList[i]->m_lightId == lightId)
		{
			m_vpDynamicLightList[i]->m_colour = colour;

			return;
		}
	}
}

void LightingManager::Update(float dt)
{
	// Remove any lights that need to be erased
	m_vpDynamicLightList.erase( remove_if(m_vpDynamicLightList.begin(), m_vpDynamicLightList.end(), needs_erasing), m_vpDynamicLightList.end() );

	for(unsigned int i = 0; i < m_vpDynamicLightList.size(); i++)
	{
		m_vpDynamicLightList[i]->Update(dt);
	}
}

void LightingManager::DebugRender()
{
	for(unsigned int i = 0; i < m_vpDynamicLightList.size(); i++)
	{
		DynamicLight* lpLight = m_vpDynamicLightList[i];

		float lightRadius = lpLight->m_radius;
		float r = lpLight->m_colour.GetRed();
		float g = lpLight->m_colour.GetGreen();
		float b = lpLight->m_colour.GetBlue();
		float a = lpLight->m_colour.GetAlpha();

		m_pRenderer->SetLineWidth(1.0f);
		
		m_pRenderer->PushMatrix();
			m_pRenderer->SetRenderMode(RM_WIREFRAME);
			m_pRenderer->TranslateWorldMatrix(lpLight->m_position.x, lpLight->m_position.y, lpLight->m_position.z);
			m_pRenderer->ImmediateColourAlpha(r, g, b, a);
			m_pRenderer->DrawSphere(lightRadius, 30, 30);
		m_pRenderer->PopMatrix();
	}
}