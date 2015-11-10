// ******************************************************************************
// Filename:	VoxGame.cpp
// Project:		Vox
// Author:		Steven Ball
//
// Revision History:
//   Initial Revision - 27/10/15
//
// Copyright (c) 2005-2015, Steven Ball
// ******************************************************************************

#include "glew/include/GL/glew.h"

#include "VoxGame.h"

#if defined(__linux__) || defined(__MACH__)
#include <sys/time.h>
#endif //__linux__ || __MACH__


// Initialize the singleton instance
VoxGame *VoxGame::c_instance = 0;

VoxGame* VoxGame::GetInstance()
{
	if (c_instance == 0)
		c_instance = new VoxGame;

	return c_instance;
}

// Creation
void VoxGame::Create()
{
	m_pRenderer = NULL;
	m_pGameCamera = NULL;
	m_pQubicleBinaryManager = NULL;
	m_pPlayer = NULL;
	m_pChunkManager = NULL;

	m_pVoxApplication = new VoxApplication();
	m_pVoxWindow = new VoxWindow();

	// Create application and window
	m_pVoxApplication->Create();
	m_pVoxWindow->Create();

	/* Setup the FPS and deltatime counters */
#ifdef _WIN32
	QueryPerformanceCounter(&m_fpsPreviousTicks);
	QueryPerformanceCounter(&m_fpsCurrentTicks);
	QueryPerformanceFrequency(&m_fpsTicksPerSecond);
#else
    struct timeval tm;
    gettimeofday(&tm, NULL);
    m_fpsCurrentTicks = (double)tm.tv_sec + (double)tm.tv_usec / 1000000.0;
    m_fpsPreviousTicks = (double)tm.tv_sec + (double)tm.tv_usec / 1000000.0;
#endif //_WIN32
	m_deltaTime = 0.0f;
	m_fps = 0.0f;

	/* Create the renderer */
	m_windowWidth = m_pVoxWindow->GetWindowWidth();
	m_windowHeight = m_pVoxWindow->GetWindowHeight();
	m_pRenderer = new Renderer(m_windowWidth, m_windowHeight, 32, 8);

	/* Create the GUI */
	m_pGUI = new OpenGLGUI(m_pRenderer);

	/* Create cameras */
	m_pGameCamera = new Camera(m_pRenderer);
	m_pGameCamera->SetPosition(vec3(0.0f, 1.25f, 5.0f));
	m_pGameCamera->SetFacing(vec3(0.0f, 0.0f, -1.0f));
	m_pGameCamera->SetUp(vec3(0.0f, 1.0f, 0.0f));
	m_pGameCamera->SetRight(vec3(1.0f, 0.0f, 0.0f));

	/* Create viewports */
	m_pRenderer->CreateViewport(0, 0, m_windowWidth, m_windowHeight, 60.0f, &m_defaultViewport);

	/* Create fonts */
	m_pRenderer->CreateFreeTypeFont("media/fonts/arial.ttf", 12, &m_defaultFont);

	/* Create lights */
	m_defaultLightPosition = vec3(3.0f, 5.0f, 3.0f);
	m_defaultLightView = vec3(0.0f, 0.0f, 0.0f);
	vec3 lightDirection = m_defaultLightView - m_defaultLightPosition;
	m_pRenderer->CreateLight(Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f),
							 m_defaultLightPosition, lightDirection, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, true, false, &m_defaultLight);

	/* Create materials */
	m_pRenderer->CreateMaterial(Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f), 64, &m_defaultMaterial);

	/* Create the frame buffers */
	bool frameBufferCreated = false;
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "SSAO", &m_SSAOFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 5.0f, "Shadow", &m_shadowFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "Deferred Lighting", &m_lightingFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "Transparency", &m_transparencyFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FXAA", &m_FXAAFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FullScreen 1st Pass", &m_firstPassFullscreenBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FullScreen 2nd Pass", &m_secondPassFullscreenBuffer);

	/* Create the shaders */
	bool shaderLoaded = false;
	m_defaultShader = -1;
	m_phongShader = -1;
	m_SSAOShader = -1;
	m_shadowShader = -1;
	m_lightingShader = -1;
	m_textureShader = -1;
	m_fxaaShader = -1;
	m_blurVerticalShader = -1;
	m_blurHorizontalShader = -1;
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/default.vertex", "media/shaders/default.pixel", &m_defaultShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/phong.vertex", "media/shaders/phong.pixel", &m_phongShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/shadow.vertex", "media/shaders/shadow.pixel", &m_shadowShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/texture.vertex", "media/shaders/texture.pixel", &m_textureShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/SSAO.vertex", "media/shaders/fullscreen/SSAO.pixel", &m_SSAOShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/fxaa.vertex", "media/shaders/fullscreen/fxaa.pixel", &m_fxaaShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/lighting.vertex", "media/shaders/fullscreen/lighting.pixel", &m_lightingShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/blur_vertical.vertex", "media/shaders/fullscreen/blur_vertical.pixel", &m_blurVerticalShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/blur_horizontal.vertex", "media/shaders/fullscreen/blur_horizontal.pixel", &m_blurHorizontalShader);

	/* Create the chunk manager*/
	m_pChunkManager = new ChunkManager(m_pRenderer);

	/* Create the qubicle binary file manager */
	m_pQubicleBinaryManager = new QubicleBinaryManager(m_pRenderer);

	/* Create the lighting manager */
	m_pLightingManager = new LightingManager(m_pRenderer);

	/* Create the block particle manager */
	m_pBlockParticleManager = new BlockParticleManager(m_pRenderer);

	/* Create the player */
	m_pPlayer = new Player(m_pRenderer, m_pQubicleBinaryManager, m_pLightingManager, m_pBlockParticleManager);

	/* Create the frontend manager */
	m_pFrontendManager = new FrontendManager(m_pRenderer);

	/* Create and skin the GUI components */
	CreateGUI();
	SkinGUI();

	// Keyboard movement
	m_bKeyboardForward = false;
	m_bKeyboardBackward = false;
	m_bKeyboardStrafeLeft = false;
	m_bKeyboardStrafeRight = false;
	m_bKeyboardLeft = false;
	m_bKeyboardRight = false;
	m_bKeyboardUp = false;
	m_bKeyboardDown = false;
	m_bKeyboardSpace = false;

	// Camera movement
	m_bCameraRotate = false;
	m_pressedX = 0;
	m_pressedY = 0;
	m_currentX = 0;
	m_currentY = 0;
	m_cameraDistance = 5.0f;
	m_maxCameraDistance = m_cameraDistance;

	// Player movement
	m_keyboardMovement = false;
	m_gamepadMovement = false;
	m_movementSpeed = 0.0f;
	m_movementDragTime = 0.45f;
	m_movementIncreaseTime = 0.25f;
	m_maxMovementSpeed = 10.0f;
	m_movementStopThreshold = 0.05f;

	// Toggle flags
	m_deferredRendering = true;
	m_modelWireframe = false;
	m_modelAnimationIndex = 0;
	m_multiSampling = true;
	m_ssao = true;
	m_blur = false;
	m_shadows = true;
	m_dynamicLighting = true;
	m_animationUpdate = true;
	m_fullscreen = false;
	m_debugRender = false;
	m_instanceRender = true;

	// Camera mode
	m_cameraMode = CameraMode_Debug;
	m_cameraModeBeforePause = CameraMode_Debug;

	// Game mode
	m_gameMode = GameMode_Debug;
	SetGameMode(m_gameMode);
}

// Destruction
void VoxGame::Destroy()
{
	if (c_instance)
	{
		delete m_pLightingManager;
		delete m_pPlayer;
		delete m_pQubicleBinaryManager;
		delete m_pChunkManager;
		delete m_pFrontendManager;
		delete m_pGameCamera;
		DestroyGUI();  // Destroy the GUI components before we delete the GUI manager object.
		delete m_pGUI;
		delete m_pRenderer;

		m_pVoxWindow->Destroy();
		m_pVoxApplication->Destroy();

		delete m_pVoxWindow;
		delete m_pVoxApplication;

		delete c_instance;
	}
}

// Events
void VoxGame::PollEvents()
{
	m_pVoxWindow->PollEvents();
}

bool VoxGame::ShouldClose()
{
	return (m_pVoxWindow->ShouldCloseWindow() == 1) || (m_pVoxApplication->ShouldCloseApplication() == 1);
}

// Window functionality
void VoxGame::ResizeWindow(int width, int height)
{
	m_windowWidth = width;
	m_windowHeight = height;

	m_pVoxWindow->ResizeWindow(m_windowWidth, m_windowHeight);

	if(m_pRenderer)
	{
		// Let the renderer know we have resized the window
		m_pRenderer->ResizeWindow(m_windowWidth, m_windowHeight);

		// Resize the main viewport
		m_pRenderer->ResizeViewport(m_defaultViewport, 0, 0, m_windowWidth, m_windowHeight, 60.0f);

		// Resize the frame buffers
		bool frameBufferResize = false;
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_SSAOFrameBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "SSAO", &m_SSAOFrameBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_shadowFrameBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 5.0f, "Shadow", &m_shadowFrameBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_lightingFrameBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "Deferred Lighting", &m_lightingFrameBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_transparencyFrameBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "Transparency", &m_transparencyFrameBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_FXAAFrameBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FXAA", &m_FXAAFrameBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_firstPassFullscreenBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FullScreen 1st Pass", &m_firstPassFullscreenBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_secondPassFullscreenBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FullScreen 2nd Pass", &m_secondPassFullscreenBuffer);

		// Give the new windows dimensions to the GUI components also
		m_pMainWindow->SetApplicationDimensions(m_windowWidth, m_windowHeight);
		m_pGameWindow->SetApplicationDimensions(m_windowWidth, m_windowHeight);
	}
}

// Game functions
void VoxGame::SetupDataForGame()
{

}

void VoxGame::SetupDataForFrontEnd()
{

}

void VoxGame::StartGameFromFrontEnd()
{

}

void VoxGame::SetGameMode(GameMode mode)
{
	GameMode previousgameMode = m_gameMode;
	m_gameMode = mode;

	if (m_gameMode == GameMode_Debug)
	{
	}

	if (m_gameMode == GameMode_FrontEnd)
	{
		if (previousgameMode == GameMode_Game || previousgameMode == GameMode_Loading)
		{
			// Setup the gamedata since we have just loaded fresh into the frontend.
			SetupDataForFrontEnd();
		}
	}

	if (m_gameMode == GameMode_Game)
	{
		if (previousgameMode == GameMode_FrontEnd || previousgameMode == GameMode_Loading)
		{
			// Setup the gamedata since we have just loaded fresh into a game.
			SetupDataForGame();
		}
	}
}

GameMode VoxGame::GetGameMode()
{
	return m_gameMode;
}
