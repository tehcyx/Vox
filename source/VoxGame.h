// ******************************************************************************
// Filename:	VoxGame.h
// Project:		Vox
// Author:		Steven Ball
//
// Purpose:
//   Vox game class.
// 
// Revision History:
//   Initial Revision - 27/10/15
//
// Copyright (c) 2005-2015, Steven Ball
// ******************************************************************************

#pragma once

#include "Renderer/Renderer.h"
#include "gui/openglgui.h"
#include "Renderer/camera.h"
#include "Lighting/LightingManager.h"
#include "Particles/BlockParticleManager.h"
#include "Player/Player.h"

#include "blocks/ChunkManager.h"
#include "frontend/FrontendManager.h"

#include "VoxApplication.h"
#include "VoxWindow.h"

enum GameMode
{
	GameMode_Debug = 0,
	GameMode_Loading,
	GameMode_FrontEnd,
	GameMode_Game,
};

enum CameraMode
{
	CameraMode_Debug = 0,
	CameraMode_MouseRotate,
	CameraMode_AutoCamera,
	CameraMode_FirstPerson,
};

class VoxGame
{
public:
	/* Public methods */
	static VoxGame* GetInstance();

	// Creation
	void Create();
	void CreateGUI();
	void SkinGUI();
	void UnSkinGUI();

	// Destruction
	void Destroy();
	void DestroyGUI();

	// Events
	void PollEvents();
	bool ShouldClose();

	// Window functionality
	void ResizeWindow(int width, int height);

	// Controls
	void UpdateControls(float dt);
	void UpdateKeyboardControls(float dt);
	void UpdateMouseControls(float dt);
	void UpdateGamePadControls(float dt);

	// Camera controls
	void UpdateCamera(float dt);
	void UpdateCameraMouseRotate(float dt);
	void SetupCameraAutoCamera();
	void UpdateCameraAutoCamera(float dt);
	void UpdateCameraFirstPerson(float dt);
	void UpdateCameraClipping(float dt);
	void UpdateCameraZoom(float dt);

	// Input
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

	// Game functions
	void SetupDataForGame();
	void SetupDataForFrontEnd();
	void StartGameFromFrontEnd();
	void SetGameMode(GameMode mode);
	GameMode GetGameMode();
	void SetCameraMode(CameraMode mode);
	CameraMode GetCameraMode();

	// Updating
	void Update();
	void UpdateLights(float dt);
	void UpdateGUI(float dt);

	// Rendering
	void PreRender();
	void Render();
	void RenderWorld();
	void RenderShadows();
	void RenderDeferredLighting();
	void RenderTransparency();
	void RenderSSAOTexture();
	void RenderFXAATexture();
	void RenderFirstPassFullScreen();
	void RenderSecondPassFullScreen();
	void RenderGUI();
	void RenderDebugInformation();

	// GUI
	void UpdateAnimationsPulldown();
	void UpdateGUIThemePulldown();

protected:
	/* Protected methods */
	VoxGame() {};
	VoxGame(const VoxGame&) {};
	VoxGame &operator=(const VoxGame&) {};

	// GUI callbacks
	static void _ToggleFullScreenPressed(void *apData);
	void ToggleFullScreenPressed();	

	static void _PlayAnimationPressed(void *apData);
	void PlayAnimationPressed();

	static void _AnimationPullDownChanged(void *apData);
	void AnimationPullDownChanged();
	
	static void _WeaponPullDownChanged(void *apData);
	void WeaponPullDownChanged();

	static void _CharacterPullDownChanged(void *apData);
	void CharacterPullDownChanged();

	static void _GameModeChanged(void *apData);
	void GameModeChanged();

	static void _CameraModeChanged(void *apData);
	void CameraModeChanged();

	static void _GUIThemePullDownChanged(void *apData);
	void GUIThemePullDownChanged();

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
	
	// GUI
	OpenGLGUI* m_pGUI;

	// Game camera
	Camera* m_pGameCamera;

	// Qubicle binary manager
	QubicleBinaryManager* m_pQubicleBinaryManager;
	
	// Player
	Player* m_pPlayer;

	// Chunk manager
	ChunkManager* m_pChunkManager;

	// Lighting manager
	LightingManager* m_pLightingManager;

	// Block particle manager
	BlockParticleManager* m_pBlockParticleManager;

	// Frontend manager
	FrontendManager* m_pFrontendManager;

	// Game mode
	GameMode m_gameMode;

	// Camera mode
	CameraMode m_cameraMode;
	CameraMode m_cameraModeBeforePause;

	// Window width and height
	int m_windowWidth;
	int m_windowHeight;

	// View ports
	unsigned int m_defaultViewport;

	// Fonts
	unsigned int m_defaultFont;

	// Lights
	unsigned int m_defaultLight;
	vec3 m_defaultLightPosition;
	vec3 m_defaultLightView;

	// Materials
	unsigned int m_defaultMaterial;

	// Frame buffers
	unsigned int m_SSAOFrameBuffer;
	unsigned int m_shadowFrameBuffer;
	unsigned int m_lightingFrameBuffer;
	unsigned int m_transparencyFrameBuffer;
	unsigned int m_FXAAFrameBuffer;
	unsigned int m_firstPassFullscreenBuffer;
	unsigned int m_secondPassFullscreenBuffer;

	// Shaders
	unsigned int m_defaultShader;
	unsigned int m_phongShader;
	unsigned int m_SSAOShader;
	unsigned int m_shadowShader;
	unsigned int m_lightingShader;
	unsigned int m_textureShader;
	unsigned int m_fxaaShader;
	unsigned int m_blurVerticalShader;
	unsigned int m_blurHorizontalShader;

	// FPS and deltatime
#ifdef _WIN32
	LARGE_INTEGER m_fpsPreviousTicks;
	LARGE_INTEGER m_fpsCurrentTicks;
	LARGE_INTEGER m_fpsTicksPerSecond;
#else
	struct timeval m_fpsPreviousTicks;
	struct timeval m_fpsCurrentTicks;
	struct timespec m_fpsTicksPerSecond;
#endif //_WIN32
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
	int m_pressedX;
	int m_pressedY;
	int m_currentX;
	int m_currentY;
	float m_cameraDistance;
	float m_maxCameraDistance;

	// Auto camera mode
	vec3 m_targetCameraPosition_AutoModeCached;
	vec3 m_targetCameraUp_AutoModeCached;
	vec3 m_targetCameraFacing_AutoModeCached;
	vec3 m_targetCameraPosition_AutoMode;
	vec3 m_targetCameraUp_AutoMode;
	vec3 m_targetCameraFacing_AutoMode;
	vec3 m_targetCameraBehindPlayerPosition;
	float m_targetCameraBehindPlayerRightAmount;
	float m_targetCameraBehindPlayerForwardAmount;
	float m_targetCameraBehindPlayerUpAmount;

	// Player movement
	bool m_keyboardMovement;
	bool m_gamepadMovement;
	vec3 m_movementDirection;
	float m_movementSpeed;
	float m_movementDragTime;
	float m_movementIncreaseTime;
	float m_maxMovementSpeed;
	float m_movementStopThreshold;

	// GUI Components
	GUIWindow* m_pMainWindow;
	CheckBox* m_pShadowsCheckBox;
	CheckBox* m_pSSAOCheckBox;
	CheckBox* m_pDynamicLightingCheckBox;
	CheckBox* m_pWireframeCheckBox;
	CheckBox* m_pMSAACheckBox;
	CheckBox* m_pDeferredCheckBox;
	CheckBox* m_pUpdateCheckBox;
	CheckBox* m_pBlurCheckBox;
	CheckBox* m_pDebugRenderCheckBox;
	Button* m_pFullscreenButton;
	Button* m_pPlayAnimationButton;
	PulldownMenu* m_pAnimationsPulldown;
	PulldownMenu* m_pWeaponsPulldown;
	PulldownMenu* m_pCharacterPulldown;
	GUIWindow* m_pGameWindow;
	OptionBox* m_pGameOptionBox;
	OptionBox* m_pDebugOptionBox;
	OptionBox* m_pFrontEndOptionBox;
	OptionController* m_pGameModeOptionController;
	PulldownMenu* m_pGUIThemePulldown;
	OptionBox* m_pDebugCameraOptionBox;
	OptionBox* m_pMouseRotateCameraOptionBox;
	OptionBox* m_pAutoCameraOptionBox;
	OptionBox* m_pFirstPersonCameraOptionBox;
	OptionController* m_pCameraModeOptionController;

	// Toggle flags
	bool m_deferredRendering;
	bool m_modelWireframe;
	int m_modelAnimationIndex;
	bool m_multiSampling;
	bool m_ssao;
	bool m_blur;
	bool m_shadows;
	bool m_dynamicLighting;
	bool m_animationUpdate;
	bool m_fullscreen;
	bool m_debugRender;

	// Singleton instance
	static VoxGame *c_instance;
};