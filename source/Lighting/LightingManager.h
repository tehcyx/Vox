// ******************************************************************************
//
// Filename:	LightingManager.h
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

#pragma once

#include "DynamicLight.h"
#include "../Renderer/Renderer.h"

#include <vector>
using namespace std;


typedef vector<DynamicLight*> DynamicLightList;


class LightingManager
{
public:
	/* Public methods */
	LightingManager(Renderer* pRenderer);
	~LightingManager();

	int GetNumLights();
	DynamicLight* GetLight(int index);

	void ClearLights();

	void AddLight(vec3 position, float radius, float diffuseModifier, Colour colour , unsigned int *pID);
	void AddDyingLight(vec3 position, float radius, float diffuseModifier, Colour colour, float lifeTime, unsigned int *pID);
	void RemoveLight(unsigned int lightId);

	void UpdateLight(unsigned int lightId, vec3 position, float radius, float diffuseModifier, Colour colour);
	void UpdateLightRadius(unsigned int lightId, float radius);
	void UpdateLightDiffuseMultiplier(unsigned int lightId, float diffuseMultiplier);
	void UpdateLightPosition(unsigned int lightId, vec3 position);
	void UpdateLightColour(unsigned int lightId, Colour colour);

	void Update(float dt);

	void DebugRender();

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

	DynamicLightList m_vpDynamicLightList;

	unsigned int m_lightIndexCounter;
};
