#include "VoxGame.h"

#include "utils/Interpolator.h"
#include "utils/TimeManager.h"

#if defined(__linux__) || defined(__MACH__)
#include <sys/time.h>
#endif //__linux__


// Updating
void VoxGame::Update()
{
	// FPS
#ifdef _WIN32
	QueryPerformanceCounter(&m_fpsCurrentTicks);
	m_deltaTime = ((float)(m_fpsCurrentTicks.QuadPart - m_fpsPreviousTicks.QuadPart) / (float)m_fpsTicksPerSecond.QuadPart);
#else
    struct timeval tm;
    gettimeofday(&tm, NULL);
    m_fpsCurrentTicks = (double)tm.tv_sec + (double)tm.tv_usec / 1000000.0;
    m_deltaTime = (m_fpsCurrentTicks - m_fpsPreviousTicks);
#endif //_WIN32
	m_fps = 1.0f / m_deltaTime;
	m_fpsPreviousTicks = m_fpsCurrentTicks;

	// Update interpolator singleton
	Interpolator::GetInstance()->Update(m_deltaTime);

	// Pause the interpolator if animations are paused.
	Interpolator::GetInstance()->SetPaused(m_animationUpdate == false);

	// Update the time manager (countdowntimers);
	TimeManager::GetInstance()->Update(m_deltaTime);

	// Animation update
	if (m_animationUpdate)
	{
		// Update the lighting manager
		m_pLightingManager->Update(m_deltaTime);

		// Block particle manager
		m_pBlockParticleManager->Update(m_deltaTime);

		// Player
		m_pPlayer->Update(m_deltaTime);
	}

	// Update the chunk manager
	m_pChunkManager->Update(m_deltaTime);

	// Update controls
	UpdateControls(m_deltaTime);

	// Update the camera
	if (m_gameMode == GameMode_Game)
	{
		UpdateCamera(m_deltaTime);
	}
	UpdateCameraZoom(m_deltaTime);
	UpdateCameraClipping(m_deltaTime);

	// Update the GUI
	int x = m_pVoxWindow->GetCursorX();
	int y = m_pVoxWindow->GetCursorY();
	m_pGUI->Update(m_deltaTime);
	m_pGUI->ImportMouseMotion(x, m_windowHeight - y);

	UpdateGUI(m_deltaTime);

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
