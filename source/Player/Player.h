// ******************************************************************************
//
// Filename:	Player.h
// Project:		Vox
// Author:		Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 27/10/15
//
// Copyright (c) 2005-2015, Steven Ball
//
// ******************************************************************************

#pragma once

#include "../Renderer/Renderer.h"
#include "../models/VoxelCharacter.h"
#include "../Lighting/LightingManager.h"
#include "../Particles/BlockParticleManager.h"


class Player
{
public:
	/* Public methods */
	Player(Renderer* pRenderer, QubicleBinaryManager* pQubicleBinaryManager, LightingManager* pLightingManager, BlockParticleManager* pBlockParticleManager);
	~Player();

	// Get voxel character pointer
	VoxelCharacter* GetVoxelCharacter();

	// Loading
	void LoadCharacter(string characterName);

	// Unloading
	void UnloadWeapon(bool left);

	// Rendering modes
	void SetWireFrameRender(bool wireframe);

	// Rendering Helpers
	void CalculateWorldTransformMatrix();

	// Updating
	void Update(float dt);
	void UpdateWeaponLights(float dt);
	void UpdateWeaponParticleEffects(float dt);

	// Rendering
	void Render();
	void RenderWeaponTrails();
	void RenderFace();

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
	QubicleBinaryManager* m_pQubicleBinaryManager;
	LightingManager* m_pLightingManager;
	BlockParticleManager* m_pBlockParticleManager;

	// Position
	vec3 m_position;

	// Local axis
	vec3 m_forward;
	vec3 m_right;
	vec3 m_up;

	// Players world matrix
	Matrix4x4 m_worldMatrix;

	// Voxel character
	VoxelCharacter* m_pVoxelCharacter;
};
