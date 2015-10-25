#include "glew/include/GL/glew.h"

#include "VoxGame.h"

#include "utils/Interpolator.h"

// Initialize the singleton instance
VoxGame *VoxGame::c_instance = 0;

VoxGame* VoxGame::GetInstance()
{
	if (c_instance == 0)
		c_instance = new VoxGame;

	return c_instance;
}

void VoxGame::Create()
{
	m_pRenderer = NULL;
	m_pGameCamera = NULL;
	m_pQubicleBinaryManager = NULL;
	m_pVoxelCharacter = NULL;

	m_pVoxApplication = new VoxApplication();
	m_pVoxWindow = new VoxWindow();

	// Create application and window
	m_pVoxApplication->Create();
	m_pVoxWindow->Create();

	/* Setup the FPS and deltatime counters */
	QueryPerformanceCounter(&m_fpsPreviousTicks);
	QueryPerformanceCounter(&m_fpsCurrentTicks);
	QueryPerformanceFrequency(&m_fpsTicksPerSecond);
	m_deltaTime = 0.0f;
	m_fps = 0.0f;

	/* Create the renderer */
	m_windowWidth = 800;
	m_windowHeight = 800;
	m_pRenderer = new Renderer(m_windowWidth, m_windowHeight, 32, 8);

	/* Create cameras */
	m_pGameCamera = new Camera(m_pRenderer);
	m_pGameCamera->SetPosition(Vector3d(0.0f, 1.25f, 3.0f));
	m_pGameCamera->SetFacing(Vector3d(0.0f, 0.0f, -1.0f));
	m_pGameCamera->SetUp(Vector3d(0.0f, 1.0f, 0.0f));
	m_pGameCamera->SetRight(Vector3d(1.0f, 0.0f, 0.0f));

	/* Create viewports */
	m_pRenderer->CreateViewport(0, 0, m_windowWidth, m_windowHeight, 60.0f, &m_defaultViewport);

	/* Create fonts */
	m_pRenderer->CreateFreeTypeFont("media/fonts/arial.ttf", 12, &m_defaultFont);

	/* Create lights */
	m_defaultLightPosition = Vector3d(2.0f, 2.0f, 1.0f);
	m_defaultLightView = Vector3d(0.0f, 0.0f, 0.0f);
	m_pRenderer->CreateLight(Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f),
							 Vector3d(2.0f, 2.0f, 1.0f), Vector3d(0.0f, -1.0f, 0.0f), 0.0f, 0.0f, 0.5f, 0.35f, 0.05f, true, false, &m_defaultLight);

	/* Create materials */
	m_pRenderer->CreateMaterial(Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f), 64, &m_defaultMaterial);

	/* Create the frame buffers */
	bool frameBufferCreated = false;
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "SSAO", &m_SSAOFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 5.0f, "Shadow", &m_shadowFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "Deferred Lighting", &m_lightingFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "Transparency", &m_transparencyFrameBuffer);

	/* Create the shaders */
	m_defaultShader = -1;
	m_phongShader = -1;
	m_SSAOShader = -1;
	m_shadowShader = -1;
	m_lightingShader = -1;
	m_textureShader = -1;
	m_pRenderer->LoadGLSLShader("media/shaders/default.vertex", "media/shaders/default.pixel", &m_defaultShader);
	m_pRenderer->LoadGLSLShader("media/shaders/phong.vertex", "media/shaders/phong.pixel", &m_phongShader);
	m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/SSAO.vertex", "media/shaders/fullscreen/SSAO.pixel", &m_SSAOShader);
	m_pRenderer->LoadGLSLShader("media/shaders/shadow.vertex", "media/shaders/shadow.pixel", &m_shadowShader);
	m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/lighting.vertex", "media/shaders/fullscreen/lighting.pixel", &m_lightingShader);
	m_pRenderer->LoadGLSLShader("media/shaders/texture.vertex", "media/shaders/texture.pixel", &m_textureShader);

	/* Create the qubicle binary file manager */
	m_pQubicleBinaryManager = new QubicleBinaryManager(m_pRenderer);

	/* Create the lighting manager */
	m_pLightingManager = new LightingManager(m_pRenderer);

	/* Create the block particle manager */
	m_pBlockParticleManager = new BlockParticleManager(m_pRenderer);

	/* Create test voxel character */
	m_pVoxelCharacter = new VoxelCharacter(m_pRenderer, m_pQubicleBinaryManager);
	char characterBaseFolder[128];
	char qbFilename[128];
	char ms3dFilename[128];
	char animListFilename[128];
	char facesFilename[128];
	char characterFilename[128];
	string modelName = "Steve";
	string typeName = "Human";
	sprintf_s(characterBaseFolder, 128, "media/gamedata/models");
	sprintf_s(qbFilename, 128, "media/gamedata/models/%s/%s.qb", typeName.c_str(), modelName.c_str());
	sprintf_s(ms3dFilename, 128, "media/gamedata/models/%s/%s.ms3d", typeName.c_str(), typeName.c_str());
	sprintf_s(animListFilename, 128, "media/gamedata/models/%s/%s.animlist", typeName.c_str(), typeName.c_str());
	sprintf_s(facesFilename, 128, "media/gamedata/models/%s/%s.faces", typeName.c_str(), modelName.c_str());
	sprintf_s(characterFilename, 128, "media/gamedata/models/%s/%s.character", typeName.c_str(), modelName.c_str());
	m_pVoxelCharacter->LoadVoxelCharacter(typeName.c_str(), qbFilename, ms3dFilename, animListFilename, facesFilename, characterFilename, characterBaseFolder);
	m_pVoxelCharacter->SetBreathingAnimationEnabled(true);
	m_pVoxelCharacter->SetWinkAnimationEnabled(true);
	m_pVoxelCharacter->SetTalkingAnimationEnabled(false);
	m_pVoxelCharacter->SetRandomMouthSelection(true);
	m_pVoxelCharacter->SetRandomLookDirection(true);
	m_pVoxelCharacter->SetWireFrameRender(false);
	m_pVoxelCharacter->SetCharacterScale(0.08f);

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
	m_bCameraZoom = false;

	m_pressedX = 0;
	m_pressedY = 0;	
	m_currentX = 0;
	m_currentY = 0;

	// Toggle flags
	m_renderModeIndex = 0;
	m_renderModeString = "Shadow";
	m_displayHelpText = true;
	m_modelWireframe = false;
	m_modelTalking = false;
	m_modelAnimationIndex = 0;
	m_multiSampling = true;
	m_ssao = true;
	m_shadows = true;
	m_dynamicLighting = true;
	m_weaponIndex = 0;
	m_weaponString = "NONE";
	m_animationUpdate = true;
	m_fullscreen = false;
}

void VoxGame::Destroy()
{
	if (c_instance)
	{
		delete m_pLightingManager;
		delete m_pVoxelCharacter;
		delete m_pQubicleBinaryManager;
		delete m_pGameCamera;
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
	}
}

// Updating
void VoxGame::Update()
{
	// Update interpolator singleton
	Interpolator::GetInstance()->Update();

	// FPS
	QueryPerformanceCounter(&m_fpsCurrentTicks);
	m_deltaTime = ((float)(m_fpsCurrentTicks.QuadPart - m_fpsPreviousTicks.QuadPart) / (float)m_fpsTicksPerSecond.QuadPart);
	m_fps = 1.0f / m_deltaTime;
	m_fpsPreviousTicks = m_fpsCurrentTicks;

	// Pause the interpolator if animations are paused.
	Interpolator::GetInstance()->SetPaused(m_animationUpdate == false);

	// Animation update
	if (m_animationUpdate)
	{
		// Update the lighting manager
		m_pLightingManager->Update(m_deltaTime);

		// Block particle manager
		m_pBlockParticleManager->Update(m_deltaTime);

		// Update the voxel model
		float animationSpeeds[AnimationSections_NUMSECTIONS] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
		Matrix4x4 worldMatrix;
		m_pVoxelCharacter->Update(m_deltaTime, animationSpeeds);
		m_pVoxelCharacter->UpdateWeaponTrails(m_deltaTime, worldMatrix);
	}

	// Update / Create weapon lights and particle effects
	UpdateWeaponLights(m_deltaTime);
	UpdateWeaponParticleEffects(m_deltaTime);

	// Update controls
	UpdateControls(m_deltaTime);

	// Update lights
	UpdateLights(m_deltaTime);

	// Update the application and window
	m_pVoxApplication->Update(m_deltaTime);
	m_pVoxWindow->Update(m_deltaTime);
}

void VoxGame::UpdateLights(float dt)
{
	m_pRenderer->EditLightPosition(m_defaultLight, m_defaultLightPosition);
}

void VoxGame::UpdateWeaponLights(float dt)
{
	for (int i = 0; i < 2; i++)
	{
		VoxelWeapon* pWeapon = NULL;
		bool isWeaponLoaded = false;
		if (i == 0)  // Right side
		{
			pWeapon = m_pVoxelCharacter->GetRightWeapon();
			isWeaponLoaded = m_pVoxelCharacter->IsRightWeaponLoaded();
		}
		else  // Left side
		{
			pWeapon = m_pVoxelCharacter->GetLeftWeapon();
			isWeaponLoaded = m_pVoxelCharacter->IsLeftWeaponLoaded();
		}

		if (pWeapon != NULL)
		{
			if (isWeaponLoaded)
			{
				for (int i = 0; i < pWeapon->GetNumLights(); i++)
				{
					unsigned int lightId;
					Vector3d lightPos;
					float lightRadius;
					float lightDiffuseMultiplier;
					Colour lightColour;
					bool connectedToSegment;
					pWeapon->GetLightParams(i, &lightId, &lightPos, &lightRadius, &lightDiffuseMultiplier, &lightColour, &connectedToSegment);

					if (lightId == -1)
					{
						m_pLightingManager->AddLight(Vector3d(0.0f, 0.0f, 0.0f), 0.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f, 1.0f), &lightId);
						pWeapon->SetLightingId(i, lightId);
					}

					if (connectedToSegment == false)
					{
						// Rotate due to characters forward vector
						//float rotationAngle = acos(Vector3d::DotProduct(Vector3d(0.0f, 0.0f, 1.0f), m_forward));
						//if (m_forward.x < 0.0f)
						//{
						//	rotationAngle = -rotationAngle;
						//}
						//Matrix4x4 rotationMatrix;
						//rotationMatrix.SetRotation(0.0f, rotationAngle, 0.0f);
						//lightPos = rotationMatrix * lightPos;

						//// Translate to position
						//lightPos += m_position;
					}

					float scale = m_pVoxelCharacter->GetCharacterScale();

					m_pLightingManager->UpdateLightPosition(lightId, lightPos);
					m_pLightingManager->UpdateLightRadius(lightId, lightRadius * scale);
					m_pLightingManager->UpdateLightDiffuseMultiplier(lightId, lightDiffuseMultiplier);
					m_pLightingManager->UpdateLightColour(lightId, lightColour);
				}
			}
		}
	}
}

void VoxGame::UpdateWeaponParticleEffects(float dt)
{
	// Create/update
	for (int i = 0; i < 2; i++)
	{
		VoxelWeapon* pWeapon = NULL;
		bool isWeaponLoaded = false;
		if (i == 0)  // Right side
		{
			pWeapon = m_pVoxelCharacter->GetRightWeapon();
			isWeaponLoaded = m_pVoxelCharacter->IsRightWeaponLoaded();
		}
		else  // Left side
		{
			pWeapon = m_pVoxelCharacter->GetLeftWeapon();
			isWeaponLoaded = m_pVoxelCharacter->IsLeftWeaponLoaded();
		}

		if (pWeapon != NULL)
		{
			if (isWeaponLoaded)
			{
				for (int i = 0; i < pWeapon->GetNumParticleEffects(); i++)
				{
					unsigned int particleEffectId;
					Vector3d ParticleEffectPos;
					string effectName;
					bool connectedToSegment;
					pWeapon->GetParticleEffectParams(i, &particleEffectId, &ParticleEffectPos, &effectName, &connectedToSegment);

					if (particleEffectId == -1)
					{
						m_pBlockParticleManager->ImportParticleEffect(effectName, ParticleEffectPos, &particleEffectId);
						pWeapon->SetParticleEffectId(i, particleEffectId);
					}

					if (connectedToSegment == false)
					{
						// Rotate due to characters forward vector
						//float rotationAngle = acos(Vector3d::DotProduct(Vector3d(0.0f, 0.0f, 1.0f), m_forward));
						//if (m_forward.x < 0.0f)
						//{
						//	rotationAngle = -rotationAngle;
						//}
						//Matrix4x4 rotationMatrix;
						//rotationMatrix.SetRotation(0.0f, rotationAngle, 0.0f);
						//ParticleEffectPos = rotationMatrix * ParticleEffectPos;

						//// Translate to position
						//ParticleEffectPos += m_position;
					}

					m_pBlockParticleManager->UpdateParticleEffectPosition(particleEffectId, ParticleEffectPos);
				}
			}
		}
	}
}

void VoxGame::UnloadWeapon(bool left)
{
	VoxelWeapon* pWeapon = NULL;
	bool isWeaponLoaded = false;
	if (left)  // Left side
	{
		pWeapon = m_pVoxelCharacter->GetLeftWeapon();
		isWeaponLoaded = m_pVoxelCharacter->IsLeftWeaponLoaded();
	}
	else  // Right side
	{
		pWeapon = m_pVoxelCharacter->GetRightWeapon();
		isWeaponLoaded = m_pVoxelCharacter->IsRightWeaponLoaded();
	}

	if (pWeapon != NULL)
	{
		if (isWeaponLoaded)
		{
			// Lights
			for (int i = 0; i < pWeapon->GetNumLights(); i++)
			{
				unsigned int lightId;
				Vector3d lightPos;
				float lightRadius;
				float lightDiffuseMultiplier;
				Colour lightColour;
				bool connectedToSegment;
				pWeapon->GetLightParams(i, &lightId, &lightPos, &lightRadius, &lightDiffuseMultiplier, &lightColour, &connectedToSegment);

				if (lightId != -1)
				{
					m_pLightingManager->RemoveLight(lightId);
					pWeapon->SetLightingId(i, -1);

					if (connectedToSegment == false)
					{
						// Rotate due to characters forward vector
						//float rotationAngle = acos(Vector3d::DotProduct(Vector3d(0.0f, 0.0f, 1.0f), m_forward));
						//if (m_forward.x < 0.0f)
						//{
						//	rotationAngle = -rotationAngle;
						//}
						//Matrix4x4 rotationMatrix;
						//rotationMatrix.SetRotation(0.0f, rotationAngle, 0.0f);
						//lightPos = rotationMatrix * lightPos;

						//// Translate to position
						//lightPos += m_position;
					}

					float scale = m_pVoxelCharacter->GetCharacterScale();
					unsigned int lId;
					m_pLightingManager->AddDyingLight(lightPos, lightRadius * scale, lightDiffuseMultiplier, lightColour, 2.0f, &lId);
				}
			}

			// Particle Effects
			for (int i = 0; i < pWeapon->GetNumParticleEffects(); i++)
			{
				unsigned int particleEffectId;
				Vector3d ParticleEffectPos;
				string effectName;
				bool connectedToSegment;
				pWeapon->GetParticleEffectParams(i, &particleEffectId, &ParticleEffectPos, &effectName, &connectedToSegment);

				if (particleEffectId != -1)
				{
					m_pBlockParticleManager->DestroyParticleEffect(particleEffectId);
					pWeapon->SetParticleEffectId(i, -1);
				}
			}
		}

		pWeapon->UnloadWeapon();

		if (left)  // Left side
		{
			m_pVoxelCharacter->UnloadLeftWeapon();
		}
		else  // Right side
		{
			m_pVoxelCharacter->UnloadRightWeapon();
		}		
	}
}

// Rendering
void VoxGame::Render()
{
	if (m_pVoxWindow->GetMinimized())
	{
		// Don't call any render functions if minimized
		return;
	}

	Matrix4x4 worldMatrix;
	glShader* pShader = NULL;

	// Begin rendering
	m_pRenderer->BeginScene(true, true, true);

		//glEnable(GL_COLOR_MATERIAL);
		//glEnable(GL_NORMALIZE);

		// Shadow rendering to the shadow frame buffer
		if (m_renderModeIndex == 0 && m_shadows)
		{
			m_pRenderer->PushMatrix();
			m_pRenderer->StartRenderingToFrameBuffer(m_shadowFrameBuffer);
			glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, 0.01f, 1000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(m_defaultLightPosition.x, m_defaultLightPosition.y, m_defaultLightPosition.z, m_defaultLightView.x, m_defaultLightView.y, m_defaultLightView.z, 0.0f, 1.0f, 0.0f);

			m_pRenderer->PushMatrix();
				m_pRenderer->SetCullMode(CM_FRONT);

				// Render the voxel character
				Colour OulineColour(1.0f, 1.0f, 0.0f, 1.0f);
				m_pRenderer->PushMatrix();
					m_pRenderer->MultiplyWorldMatrix(worldMatrix);
					m_pVoxelCharacter->RenderWeapons(false, false, false, OulineColour);
					m_pVoxelCharacter->Render(false, false, false, OulineColour, false);
				m_pRenderer->PopMatrix();

				// Render the block particles
				m_pBlockParticleManager->Render();

				m_pRenderer->SetTextureMatrix();
				m_pRenderer->SetCullMode(CM_BACK);
			m_pRenderer->PopMatrix();

			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			m_pRenderer->StopRenderingToFrameBuffer(m_shadowFrameBuffer);
			m_pRenderer->PopMatrix();
		}

		// SSAO frame buffer rendering start
		//if (m_ssao)
		{
			m_pRenderer->StartRenderingToFrameBuffer(m_SSAOFrameBuffer);
		}

		// ---------------------------------------
		// Render 3d
		// ---------------------------------------
		m_pRenderer->PushMatrix();
			// Set the default projection mode
			m_pRenderer->SetProjectionMode(PM_PERSPECTIVE, m_defaultViewport);

			// Set back culling as default
			m_pRenderer->SetCullMode(CM_BACK);

			// Set the lookat camera
			m_pGameCamera->Look();

			// Enable the lights
			m_pRenderer->PushMatrix();
				m_pRenderer->EnableLight(m_defaultLight, 0);
			m_pRenderer->PopMatrix();

			// Render the lights (DEBUG)
			m_pRenderer->PushMatrix();
				m_pRenderer->SetCullMode(CM_BACK);
				m_pRenderer->SetRenderMode(RM_SOLID);
				m_pRenderer->RenderLight(m_defaultLight);
			m_pRenderer->PopMatrix();

			// Multisampling MSAA
			if (m_multiSampling)
			{
				m_pRenderer->EnableMultiSampling();
			}
			else
			{
				m_pRenderer->DisableMultiSampling();
			}

			// Get the selected shader index
			unsigned int shaderIndex = m_shadowShader;
			if (m_renderModeIndex == 1)
			{
				shaderIndex = m_phongShader;
			}
			else if (m_renderModeIndex == 2)
			{
				shaderIndex = m_defaultShader;
			}

			m_pRenderer->BeginGLSLShader(shaderIndex);

			if (m_renderModeIndex == 0)
			{
				pShader = m_pRenderer->GetShader(shaderIndex);
				GLuint shadowMapUniform = glGetUniformLocationARB(pShader->GetProgramObject(), "ShadowMap");
				m_pRenderer->PrepareShaderTexture(7, shadowMapUniform);
				m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_shadowFrameBuffer));
				glUniform1iARB(glGetUniformLocationARB(pShader->GetProgramObject(), "renderShadow"), m_shadows);
				glUniform1iARB(glGetUniformLocationARB(pShader->GetProgramObject(), "alwaysShadow"), false);
			}

			// Render world
			RenderWorld();

			// Render the voxel character
			Colour OulineColour(1.0f, 1.0f, 0.0f, 1.0f);
			m_pRenderer->PushMatrix();
				m_pRenderer->MultiplyWorldMatrix(worldMatrix);
				m_pVoxelCharacter->RenderWeapons(false, false, false, OulineColour);
				m_pVoxelCharacter->Render(false, false, false, OulineColour, false);
			m_pRenderer->PopMatrix();

			// Render the block particles
			m_pBlockParticleManager->Render();

			m_pRenderer->EndGLSLShader(shaderIndex);

			// Render the voxel character weapon trails
			m_pRenderer->PushMatrix();
				m_pVoxelCharacter->RenderWeaponTrails();
			m_pRenderer->PopMatrix();

			// Debug rendering
			//m_pLightingManager->DebugRender();
		m_pRenderer->PopMatrix();

		// Render the deferred lighting pass
		if (m_dynamicLighting)
		{
			RenderDeferredLighting();
		}

		// ---------------------------------------
		// Render 2d
		// ---------------------------------------
		m_pRenderer->PushMatrix();
		m_pRenderer->PopMatrix();

		// SSAO frame buffer rendering stop
		//if (m_ssao)
		{
			m_pRenderer->StopRenderingToFrameBuffer(m_SSAOFrameBuffer);
		}

		// ---------------------------------------
		// Render transparency
		// ---------------------------------------
		RenderTransparency();

		// Render the SSAO texture
		//if (m_ssao)
		{
			RenderSSAOTexture();
		}

		// Render debug information and text
		RenderDebugInformation();

	// End rendering
	m_pRenderer->EndScene();


	// Render the window
	m_pVoxWindow->Render();
}

void VoxGame::RenderWorld()
{
	float floorY = 0.0f;
	float floorLength = 5.0f;

	m_pRenderer->EnableMaterial(m_defaultMaterial);

	m_pRenderer->SetRenderMode(RM_SHADED);
		m_pRenderer->EnableImmediateMode(IM_QUADS);
		m_pRenderer->ImmediateColourAlpha(0.227f, 1.0f, 0.419f, 1.0f);

		m_pRenderer->ImmediateTextureCoordinate(0.0f, 0.0f);
		m_pRenderer->ImmediateVertex(-floorLength, floorY, -floorLength);
		m_pRenderer->ImmediateNormal(0.0f, 1.0f, 0.0f);

		m_pRenderer->ImmediateTextureCoordinate(0.0f, 1.0f);
		m_pRenderer->ImmediateVertex(-floorLength, floorY, floorLength);
		m_pRenderer->ImmediateNormal(0.0f, 1.0f, 0.0f);

		m_pRenderer->ImmediateTextureCoordinate(1.0f, 1.0f);
		m_pRenderer->ImmediateVertex(floorLength, floorY, floorLength);
		m_pRenderer->ImmediateNormal(0.0f, 1.0f, 0.0f);

		m_pRenderer->ImmediateTextureCoordinate(1.0f, 0.0f);
		m_pRenderer->ImmediateVertex(floorLength, floorY, -floorLength);
		m_pRenderer->ImmediateNormal(0.0f, 1.0f, 0.0f);
	m_pRenderer->DisableImmediateMode();
}

void VoxGame::RenderDeferredLighting()
{
	// Render deferred lighting to light frame buffer
	m_pRenderer->PushMatrix();
		m_pRenderer->StartRenderingToFrameBuffer(m_lightingFrameBuffer);

		m_pRenderer->SetFrontFaceDirection(FrontFaceDirection_CW);
		m_pRenderer->EnableTransparency(BF_ONE, BF_ONE);
		m_pRenderer->DisableDepthTest();

		// Set the default projection mode
		m_pRenderer->SetProjectionMode(PM_PERSPECTIVE, m_defaultViewport);

		// Set the lookat camera
		m_pGameCamera->Look();

		m_pRenderer->PushMatrix();
			m_pRenderer->BeginGLSLShader(m_lightingShader);

			glShader* pLightShader = m_pRenderer->GetShader(m_lightingShader);
			unsigned NormalsID = glGetUniformLocationARB(pLightShader->GetProgramObject(), "normals");
			unsigned PositionssID = glGetUniformLocationARB(pLightShader->GetProgramObject(), "positions");

			m_pRenderer->PrepareShaderTexture(0, NormalsID);
			m_pRenderer->BindRawTextureId(m_pRenderer->GetNormalTextureFromFrameBuffer(m_SSAOFrameBuffer));

			m_pRenderer->PrepareShaderTexture(1, PositionssID);
			m_pRenderer->BindRawTextureId(m_pRenderer->GetPositionTextureFromFrameBuffer(m_SSAOFrameBuffer));

			pLightShader->setUniform1i("screenWidth", m_windowWidth);
			pLightShader->setUniform1i("screenHeight", m_windowHeight);

			for (int i = 0; i < m_pLightingManager->GetNumLights(); i++)
			{
				DynamicLight* lpLight = m_pLightingManager->GetLight(i);
				float lightRadius = lpLight->m_radius;

				if ((m_pGameCamera->GetPosition() - lpLight->m_position).GetLength() < lightRadius + 0.5f) // Small change to account for differences in circle render (with slices) and circle radius
				{
					m_pRenderer->SetCullMode(CM_BACK);
				}
				else
				{
					m_pRenderer->SetCullMode(CM_FRONT);
				}

				pLightShader->setUniform1f("radius", lightRadius);
				pLightShader->setUniform1f("diffuseScale", lpLight->m_diffuseScale);

				float r = lpLight->m_colour.GetRed();
				float g = lpLight->m_colour.GetGreen();
				float b = lpLight->m_colour.GetBlue();
				float a = lpLight->m_colour.GetAlpha();
				pLightShader->setUniform4f("diffuseLightColor", r, g, b, a);

				m_pRenderer->PushMatrix();
					m_pRenderer->SetRenderMode(RM_SOLID);
					m_pRenderer->TranslateWorldMatrix(lpLight->m_position.x, lpLight->m_position.y + 0.5f, lpLight->m_position.z);
					m_pRenderer->DrawSphere(lightRadius, 30, 30);
				m_pRenderer->PopMatrix();
			}

			m_pRenderer->EmptyTextureIndex(1);
			m_pRenderer->EmptyTextureIndex(0);

			m_pRenderer->EndGLSLShader(m_lightingShader);

		m_pRenderer->PopMatrix();

		m_pRenderer->SetFrontFaceDirection(FrontFaceDirection_CCW);
		m_pRenderer->DisableTransparency();
		m_pRenderer->SetCullMode(CM_BACK);
		m_pRenderer->EnableDepthTest(DT_LESS);

		m_pRenderer->StopRenderingToFrameBuffer(m_lightingFrameBuffer);

	m_pRenderer->PopMatrix();
}

void VoxGame::RenderTransparency()
{
	Matrix4x4 worldMatrix;

	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_PERSPECTIVE, m_defaultViewport);
		m_pRenderer->SetCullMode(CM_BACK);

		// Set the lookat camera
		m_pGameCamera->Look();

		m_pRenderer->StartRenderingToFrameBuffer(m_transparencyFrameBuffer);

		// Render the voxel character face
		m_pRenderer->PushMatrix();
			m_pRenderer->MultiplyWorldMatrix(worldMatrix);
			m_pRenderer->EmptyTextureIndex(0);
			m_pVoxelCharacter->RenderFace();
		m_pRenderer->PopMatrix();

		m_pRenderer->StopRenderingToFrameBuffer(m_transparencyFrameBuffer);
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderSSAOTexture()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);

		m_pRenderer->SetLookAtCamera(Vector3d(0.0f, 0.0f, 250.0f), Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 1.0f, 0.0f));

		// SSAO shader
		m_pRenderer->BeginGLSLShader(m_SSAOShader);
		glShader* pShader = m_pRenderer->GetShader(m_SSAOShader);

		unsigned int textureId0 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_DepthTexture");
		m_pRenderer->PrepareShaderTexture(0, textureId0);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_SSAOFrameBuffer));

		unsigned int textureId1 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_RenderedTexture");
		m_pRenderer->PrepareShaderTexture(1, textureId1);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_SSAOFrameBuffer));

		unsigned int textureId2 = glGetUniformLocationARB(pShader->GetProgramObject(), "light");
		m_pRenderer->PrepareShaderTexture(2, textureId2);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_lightingFrameBuffer));

		unsigned int textureId3 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_TransparentTexture");
		m_pRenderer->PrepareShaderTexture(3, textureId3);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_transparencyFrameBuffer));

		unsigned int textureId4 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_TransparentDepthTexture");
		m_pRenderer->PrepareShaderTexture(4, textureId4);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_transparencyFrameBuffer));
		

		pShader->setUniform1i("screenWidth", m_windowWidth);
		pShader->setUniform1i("screenHeight", m_windowHeight);
		pShader->setUniform1f("nearZ", 0.01f);
		pShader->setUniform1f("farZ", 1000.0f);

		pShader->setUniform1f("samplingMultiplier", 0.5f);

		pShader->setUniform1i("lighting_enabled", m_dynamicLighting);
		pShader->setUniform1i("ssao_enabled", m_ssao);

		m_pRenderer->SetRenderMode(RM_TEXTURED);
			m_pRenderer->EnableImmediateMode(IM_QUADS);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 0.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 1.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, (float)m_windowHeight, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 1.0f);
			m_pRenderer->ImmediateVertex(0.0f, (float)m_windowHeight, 1.0f);
		m_pRenderer->DisableImmediateMode();

		m_pRenderer->EmptyTextureIndex(4);
		m_pRenderer->EmptyTextureIndex(3);
		m_pRenderer->EmptyTextureIndex(2);
		m_pRenderer->EmptyTextureIndex(1);
		m_pRenderer->EmptyTextureIndex(0);

		m_pRenderer->EndGLSLShader(m_SSAOShader);
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderDebugInformation()
{
	char lCameraBuff[256];
	sprintf_s(lCameraBuff, 256, "Pos(%.2f, %.2f, %.2f), Facing(%.2f, %.2f, %.2f) = %.2f, Up(%.2f, %.2f, %.2f) = %.2f, Right(%.2f, %.2f, %.2f) = %.2f, Zoom=%.2f",
		m_pGameCamera->GetPosition().x, m_pGameCamera->GetPosition().y, m_pGameCamera->GetPosition().z,
		m_pGameCamera->GetFacing().x, m_pGameCamera->GetFacing().y, m_pGameCamera->GetFacing().z, m_pGameCamera->GetFacing().GetLength(),
		m_pGameCamera->GetUp().x, m_pGameCamera->GetUp().y, m_pGameCamera->GetUp().z, m_pGameCamera->GetUp().GetLength(),
		m_pGameCamera->GetRight().x, m_pGameCamera->GetRight().y, m_pGameCamera->GetRight().z, m_pGameCamera->GetRight().GetLength(),
		m_pGameCamera->GetZoomAmount());
	char lFPSBuff[128];
	sprintf_s(lFPSBuff, "FPS: %.0f  Delta: %.4f", m_fps, m_deltaTime);
	char lAnimationBuff[128];
	sprintf_s(lAnimationBuff, "Animation [%i/%i]: %s", m_modelAnimationIndex, m_pVoxelCharacter->GetNumAnimations() - 1, m_pVoxelCharacter->GetAnimationName(m_modelAnimationIndex));
	char lWeaponBuff[128];
	sprintf_s(lWeaponBuff, "Weapon: %s", m_weaponString.c_str());

	int l_nTextHeight = m_pRenderer->GetFreeTypeTextHeight(m_defaultFont, "a");

	m_pRenderer->PushMatrix();
		m_pRenderer->EmptyTextureIndex(0);

		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);
		m_pRenderer->SetLookAtCamera(Vector3d(0.0f, 0.0f, 250.0f), Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 1.0f, 0.0f));

		m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, 15.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lFPSBuff);

		if (m_displayHelpText)
		{
			m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, m_windowHeight - l_nTextHeight - 10.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lCameraBuff);

			m_pRenderer->RenderFreeTypeText(m_defaultFont, (int)(m_windowWidth * 0.5f) - 75.0f, 35.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lAnimationBuff);
			m_pRenderer->RenderFreeTypeText(m_defaultFont, (int)(m_windowWidth * 0.5f) - 75.0f, 15.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lWeaponBuff);

			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 255.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "F - Fullscreen [%s]", m_fullscreen ? "On" : "Off");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 235.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "I - Dynamic Lighting [%s]", m_dynamicLighting ? "On" : "Off");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 215.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "U - Shadows [%s]", m_shadows ? "On" : "Off");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 195.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "Y - SSAO [%s]", m_ssao ? "On" : "Off");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 175.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "T - Render Mode [%s]", m_renderModeString.c_str());
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 155.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "R - Toggle MSAA [%s]", m_multiSampling ? "On" : "Off");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 135.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "E - Toggle Talking [%s]", m_modelTalking ? "On" : "Off");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 115.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "L - Toggle Animation [%s]", m_animationUpdate ? "On" : "Off");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 95.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "H - Toggle HelpText");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 75.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "W - Toggle Wireframe");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 55.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "Q - Cycle Animations");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 35.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "A - Cycle Weapons");
			m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth - 150.0f, 15.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, "Z - Play Animation");
		}
	m_pRenderer->PopMatrix();
}