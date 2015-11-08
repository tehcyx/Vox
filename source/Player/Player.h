// ******************************************************************************
// Filename:	Player.h
// Project:		Vox
// Author:		Steven Ball
//
// Purpose:
//   The player class contains all the functioanlity of a player, an entity that
//   is controlled and can act within the world and game.
// 
// Revision History:
//   Initial Revision - 27/10/15
//
// Copyright (c) 2005-2015, Steven Ball
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

	// Accessors / Setters
	vec3 GetCenter();
	vec3 GetForwardVector();
	vec3 GetRightVector();
	vec3 GetUpVector();
	float GetRadius();
	void UpdateRadius();

	// Loading
	void LoadCharacter(string characterName);

	// Unloading
	void UnloadWeapon(bool left);

	// Collision
	bool CheckCollisions(vec3 positionCheck, vec3 previousPosition, vec3 *pNormal, vec3 *pMovement);

	// Movement
	void MoveAbsolute(vec3 direction, const float speed, bool shouldChangeForward = true);
	void Move(const float speed);
	void Strafe(const float speed);
	void Levitate(const float speed);
	void StopMoving();
	void Jump();
	bool CanJump();

	// Rendering modes
	void SetWireFrameRender(bool wireframe);

	// Rendering Helpers
	void CalculateWorldTransformMatrix();

	// Updating
	void Update(float dt);
	void UpdatePhysics(float dt);
	void UpdateTimers(float dt);
	void UpdateWeaponLights(float dt);
	void UpdateWeaponParticleEffects(float dt);

	// Rendering
	void Render();
	void RenderFirstPerson();
	void RenderWeaponTrails();
	void RenderFace();
	void RenderDebug();

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */
	static const vec3 PLAYER_CENTER_OFFSET;

protected:
	/* Protected members */

private:
	/* Private members */
	Renderer* m_pRenderer;
	QubicleBinaryManager* m_pQubicleBinaryManager;
	LightingManager* m_pLightingManager;
	BlockParticleManager* m_pBlockParticleManager;

	// Player position and movement variables
	vec3 m_position;
	vec3 m_velocity;
	vec3 m_force;
	vec3 m_movementVelocity;

	// Store previous position each frame after we have worked out the new position
	// Used for collision and other movement calculations
	vec3 m_previousPosition;

	// The direction of gravity for the player
	vec3 m_gravityDirection;

	// Flag to control if we are allowed to jump or not, reset when landing
	bool m_bCanJump;
	float m_jumpTimer;

	// Idle flag
	bool m_bIsIdle;

	// Player radius
	float m_radius;

	// Local axis
	vec3 m_forward;
	vec3 m_right;
	vec3 m_up;

	// Target forward / looking vector
	vec3 m_targetForward;

	// Players world matrix
	Matrix4x4 m_worldMatrix;

	// Voxel character
	VoxelCharacter* m_pVoxelCharacter;
};
