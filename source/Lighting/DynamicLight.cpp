// ******************************************************************************
//
// Filename:	DynamicLight.cpp
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

#include "DynamicLight.h"


DynamicLight::DynamicLight()
{
	m_lifeTime = 0.0f;
	m_maxLifeTime = 0.0f;
	m_dyingLight = false;

	m_erase = false;
}

DynamicLight::~DynamicLight()
{

}

void DynamicLight::SetErase(bool erase)
{
	m_erase = erase;
}

bool DynamicLight::NeedsErasing()
{
	return m_erase;
}

void DynamicLight::Update(float dt)
{
	if(m_dyingLight)
	{
		if(m_lifeTime >= 0.0f)
		{
			m_lifeTime -= dt;

			m_diffuseScale = m_lifeTime / m_maxLifeTime;
		}
		else
		{
			SetErase(true);
		}
	}
}