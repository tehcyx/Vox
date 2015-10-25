#pragma once

#include "Renderer/Renderer.h"
#include "Renderer/camera.h"
#include "Lighting/LightingManager.h"
#include "Particles/BlockParticleManager.h"
#include "models/VoxelCharacter.h"

#include <windows.h>

#include "VoxApplication.h"
#include "VoxWindow.h"


class VoxGame
{
public:
	/* Public methods */
	static VoxGame* GetInstance();

	void Create();
	void Destroy();

	// Events
	void PollEvents();
	bool ShouldClose();

	// Window functionality
	void ResizeWindow(int width, int height);

	// Controls
	void UpdateControls(float dt);
	void KeyPressed(int key, int scancode, int mods);
	void KeyReleased(int key, int scancode, int mods);
	void MouseLeftPressed();
	void MouseLeftReleased();
	void MouseRightPressed();
	void MouseRightReleased();
	void MouseMiddlePressed();
	void MouseMiddleReleased();
	void MouseScroll(double x, double y);

	// Mouse controls
	void MouseCameraRotate(int x, int y);
	void MouseCameraZoom(int x, int y);

	// Updating
	void Update();
	void UpdateLights(float dt);
	void UpdateWeaponLights(float dt);
	void UpdateWeaponParticleEffects(float dt);
	void UnloadWeapon(bool left);

	// Rendering
	void Render();
	void RenderWorld();
	void RenderDeferredLighting();
	void RenderTransparency();
	void RenderSSAOTexture();
	void RenderDebugInformation();

protected:
	/* Protected methods */
	VoxGame() {};
	VoxGame(const VoxGame&) {};
	VoxGame &operator=(const VoxGame&) {};

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	VoxApplication* m_pVoxApplication;
	VoxWindow* m_pVoxWindow;

	// Renderer
	Renderer* m_pRenderer;
	
	// Game camera
	Camera* m_pGameCamera;

	// Qubicle binary manager
	QubicleBinaryManager* m_pQubicleBinaryManager;

	// Voxel character
	VoxelCharacter* m_pVoxelCharacter;
	
	// Lighting manager
	LightingManager* m_pLightingManager;

	// Block particle manager
	BlockParticleManager* m_pBlockParticleManager;

	// Window width and height
	int m_windowWidth;
	int m_windowHeight;

	// View ports
	unsigned int m_defaultViewport;

	// Fonts
	unsigned int m_defaultFont;

	// Lights
	unsigned int m_defaultLight;
	Vector3d m_defaultLightPosition;
	Vector3d m_defaultLightView;

	// Materials
	unsigned int m_defaultMaterial;

	// Frame buffers
	unsigned int m_SSAOFrameBuffer;
	unsigned int m_shadowFrameBuffer;
	unsigned int m_lightingFrameBuffer;
	unsigned int m_transparencyFrameBuffer;

	// Shaders
	unsigned int m_defaultShader;
	unsigned int m_phongShader;
	unsigned int m_SSAOShader;
	unsigned int m_shadowShader;
	unsigned int m_lightingShader;
	unsigned int m_textureShader;

	// FPS and deltatime
	LARGE_INTEGER m_fpsPreviousTicks;
	LARGE_INTEGER m_fpsTicksPerSecond;
	LARGE_INTEGER m_fpsCurrentTicks;
	float m_deltaTime;
	float m_fps;

	// Keyboard flags
	bool m_bKeyboardForward;
	bool m_bKeyboardBackward;
	bool m_bKeyboardStrafeLeft;
	bool m_bKeyboardStrafeRight;
	bool m_bKeyboardLeft;
	bool m_bKeyboardRight;
	bool m_bKeyboardUp;
	bool m_bKeyboardDown;
	bool m_bKeyboardSpace;

	// Camera movement
	bool m_bCameraRotate;
	bool m_bCameraZoom;
	int m_pressedX;
	int m_pressedY;
	int m_currentX;
	int m_currentY;

	// Toggle flags
	int m_renderModeIndex;
	string m_renderModeString;
	bool m_displayHelpText;
	bool m_modelWireframe;
	bool m_modelTalking;
	int m_modelAnimationIndex;
	bool m_multiSampling;
	bool m_ssao;
	bool m_shadows;
	bool m_dynamicLighting;
	int m_weaponIndex;
	string m_weaponString;
	bool m_animationUpdate;
	bool m_fullscreen;

	// Singleton instance
	static VoxGame *c_instance;
};