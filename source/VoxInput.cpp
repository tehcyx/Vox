#include <stdio.h>
#include <stdlib.h>

#include "VoxGame.h"


// Event callbacks
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
		case GLFW_PRESS:
		{
			VoxGame::GetInstance()->KeyPressed(key, scancode, mods);
			break;
		}
		case GLFW_RELEASE:
		{
			VoxGame::GetInstance()->KeyReleased(key, scancode, mods);
			break;
		}
		case GLFW_REPEAT:
		{
			break;
		}
	}
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
		case GLFW_PRESS:
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
				VoxGame::GetInstance()->MouseLeftPressed();
			if (button == GLFW_MOUSE_BUTTON_RIGHT)
				VoxGame::GetInstance()->MouseRightPressed();
			if (button == GLFW_MOUSE_BUTTON_MIDDLE)
				VoxGame::GetInstance()->MouseMiddlePressed();

			break;
		}
		case GLFW_RELEASE:
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
				VoxGame::GetInstance()->MouseLeftReleased();
			if (button == GLFW_MOUSE_BUTTON_RIGHT)
				VoxGame::GetInstance()->MouseRightReleased();
			if (button == GLFW_MOUSE_BUTTON_MIDDLE)
				VoxGame::GetInstance()->MouseMiddleReleased();

			break;
		}
	}
}

void MouseScrollCallback(GLFWwindow* window, double x, double y)
{
	VoxGame::GetInstance()->MouseScroll(x, y);
}


// Controls
void VoxGame::UpdateControls(float dt)
{
	int x = m_pVoxWindow->GetCursorX();
	int y = m_pVoxWindow->GetCursorY();

	// Keyboard movements
	if (m_bKeyboardForward)
	{
		m_pGameCamera->Fly(20.0f * dt);
	}
	if (m_bKeyboardBackward)
	{
		m_pGameCamera->Fly(-20.0f * dt);
	}
	if (m_bKeyboardStrafeLeft)
	{
		m_pGameCamera->Strafe(-20.0f * dt);
	}
	if (m_bKeyboardStrafeRight)
	{
		m_pGameCamera->Strafe(20.0f * dt);
	}

	// Camera movements
	if (m_bCameraRotate)
	{
		MouseCameraRotate(x, y);
	}
	if (m_bCameraZoom)
	{
		MouseCameraZoom(x, y);
	}
}

void VoxGame::KeyPressed(int key, int scancode, int mods)
{
	switch (key)
	{
	case GLFW_KEY_UP:
	{
		m_bKeyboardForward = true;
		break;
	}
	case GLFW_KEY_DOWN:
	{
		m_bKeyboardBackward = true;
		break;
	}
	case GLFW_KEY_LEFT:
	{
		m_bKeyboardStrafeLeft = true;
		break;
	}
	case GLFW_KEY_RIGHT:
	{
		m_bKeyboardStrafeRight = true;
		break;
	}
	}
}

void VoxGame::KeyReleased(int key, int scancode, int mods)
{
	switch (key)
	{
		case GLFW_KEY_UP:
		{
			m_bKeyboardForward = false;
			break;
		}
		case GLFW_KEY_DOWN:
		{
			m_bKeyboardBackward = false;
			break;
		}
		case GLFW_KEY_LEFT:
		{
			m_bKeyboardStrafeLeft = false;
			break;
		}
		case GLFW_KEY_RIGHT:
		{
			m_bKeyboardStrafeRight = false;
			break;
		}

		case GLFW_KEY_H:
		{
			m_displayHelpText = !m_displayHelpText;
			break;
		}
		case GLFW_KEY_W:
		{
			m_modelWireframe = !m_modelWireframe;
			m_pVoxelCharacter->SetWireFrameRender(m_modelWireframe);
			break;
		}
		case GLFW_KEY_E:
		{
			m_modelTalking = !m_modelTalking;
			m_pVoxelCharacter->SetTalkingAnimationEnabled(m_modelTalking);
			break;
		}
		case GLFW_KEY_Q:
		{
			m_modelAnimationIndex++;
			if (m_modelAnimationIndex >= m_pVoxelCharacter->GetNumAnimations())
			{
				m_modelAnimationIndex = 0;
			}

			m_pVoxelCharacter->PlayAnimation(AnimationSections_FullBody, false, AnimationSections_FullBody, m_pVoxelCharacter->GetAnimationName(m_modelAnimationIndex));
			break;
		}
		case GLFW_KEY_Z:
		{
			m_pVoxelCharacter->PlayAnimation(AnimationSections_FullBody, false, AnimationSections_FullBody, m_pVoxelCharacter->GetAnimationName(m_modelAnimationIndex));
			break;
		}
		case GLFW_KEY_R:
		{
			m_multiSampling = !m_multiSampling;
			break;
		}
		case GLFW_KEY_Y:
		{
			m_ssao = !m_ssao;
			break;
		}
		case GLFW_KEY_U:
		{
			m_shadows = !m_shadows;
			break;
		}
		case GLFW_KEY_I:
		{
			m_dynamicLighting = !m_dynamicLighting;
			break;
		}
		case GLFW_KEY_T:
		{
			m_renderModeIndex++;
			if (m_renderModeIndex >= 3)
			{
				m_renderModeIndex = 0;
			}

			if (m_renderModeIndex == 0)
			{
				m_renderModeString = "Shadow";
			}
			else if (m_renderModeIndex == 1)
			{
				m_renderModeString = "Phong";
			}
			else if (m_renderModeIndex == 2)
			{
				m_renderModeString = "Default";
			}

			break;
		}
		case GLFW_KEY_L:
		{
			m_animationUpdate = !m_animationUpdate;

			break;
		}
		case GLFW_KEY_F:
		{
			m_fullscreen = !m_fullscreen;

			m_pVoxWindow->ToggleFullScreen(m_fullscreen);
			m_pBlockParticleManager->SetupGLBuffers();

			break;
		}
		case GLFW_KEY_A:
		{
			switch (m_weaponIndex)
			{
				case 0:
				{
					m_weaponString = "Sword";
					UnloadWeapon(true);
					UnloadWeapon(false);
					m_pVoxelCharacter->LoadRightWeapon("media/gamedata/weapons/Sword/Sword.weapon");
					break;
				}
				case 1:
				{
					m_weaponString = "Sword & Shield";
					UnloadWeapon(true);
					UnloadWeapon(false);
					m_pVoxelCharacter->LoadRightWeapon("media/gamedata/weapons/Sword/Sword.weapon");
					m_pVoxelCharacter->LoadLeftWeapon("media/gamedata/weapons/Shield/Shield.weapon");
					break;
				}
				case 2:
				{
					m_weaponString = "Staff";
					UnloadWeapon(true);
					UnloadWeapon(false);
					m_pVoxelCharacter->LoadRightWeapon("media/gamedata/weapons/Staff/Staff.weapon");
					break;
				}
				case 3:
				{
					m_weaponString = "Bow";
					UnloadWeapon(true);
					UnloadWeapon(false);
					m_pVoxelCharacter->LoadLeftWeapon("media/gamedata/weapons/Bow/Bow.weapon");
					break;
				}
				case 4:
				{
					m_weaponString = "2HandedSword";
					UnloadWeapon(true);
					UnloadWeapon(false);
					m_pVoxelCharacter->LoadRightWeapon("media/gamedata/weapons/2HandedSword/2HandedSword.weapon");
					break;
				}
				case 5:
				{
					m_weaponString = "Torch";
					UnloadWeapon(true);
					UnloadWeapon(false);
					m_pVoxelCharacter->LoadRightWeapon("media/gamedata/weapons/Torch/Torch.weapon");
					break;
				}
				case 6:
				{
					m_weaponString = "Fireball";
					UnloadWeapon(true);
					UnloadWeapon(false);
					m_pVoxelCharacter->LoadRightWeapon("media/gamedata/weapons/FireballHands/FireballHandsRight.weapon");
					m_pVoxelCharacter->LoadLeftWeapon("media/gamedata/weapons/FireballHands/FireballHandsLeft.weapon");
					m_pVoxelCharacter->SetQubicleMatrixRender("Right_Hand", false);
					m_pVoxelCharacter->SetQubicleMatrixRender("Left_Hand", false);
					break;
				}
				case 7:
				{
					m_weaponString = "NONE";
					UnloadWeapon(true);
					UnloadWeapon(false);
					m_pVoxelCharacter->SetQubicleMatrixRender("Right_Hand", true);
					m_pVoxelCharacter->SetQubicleMatrixRender("Left_Hand", true);
					break;
				}
			}

			m_weaponIndex++;
			if (m_weaponIndex == 8)
				m_weaponIndex = 0;

			m_pVoxelCharacter->GetRightWeapon()->StartWeaponTrails();
			m_pVoxelCharacter->GetLeftWeapon()->StartWeaponTrails();

			break;
		}
	}
}

void VoxGame::MouseLeftPressed()
{
	m_currentX = m_pVoxWindow->GetCursorX();
	m_currentY = m_pVoxWindow->GetCursorY();
	m_pressedX = m_currentX;
	m_pressedY = m_currentY;

	m_bCameraRotate = true;
}

void VoxGame::MouseLeftReleased()
{
	m_bCameraRotate = false;
}

void VoxGame::MouseRightPressed()
{
	m_currentX = m_pVoxWindow->GetCursorX();
	m_currentY = m_pVoxWindow->GetCursorY();
	m_pressedX = m_currentX;
	m_pressedY = m_currentY;

	m_bCameraZoom = true;
}

void VoxGame::MouseRightReleased()
{
	m_bCameraZoom = false;
}

void VoxGame::MouseMiddlePressed()
{
}

void VoxGame::MouseMiddleReleased()
{
}

void VoxGame::MouseScroll(double x, double y)
{
}

// Mouse controls
void VoxGame::MouseCameraRotate(int x, int y)
{
	float changeX;
	float changeY;

	// The mouse hasn't moved so just return
	if ((m_currentX == x) && (m_currentY == y))
	{
		return;
	}

	// Calculate and scale down the change in position
	changeX = (x - m_currentX) / 5.0f;
	changeY = (y - m_currentY) / 5.0f;

	// Upside down
	if (m_pGameCamera->GetUp().y < 0.0f)
	{
		changeX = -changeX;
	}

	m_pGameCamera->RotateAroundPoint(changeY*0.5f, -changeX*0.5f);

	m_currentX = x;
	m_currentY = y;
}

void VoxGame::MouseCameraZoom(int x, int y)
{
	float changeX;
	float changeY;

	// The mouse hasn't moved so just return
	if ((m_currentX == x) && (m_currentY == y))
	{
		return;
	}

	// Calculate and scale down the change in position
	changeX = (x - m_currentX) / 5.0f;
	changeY = (y - m_currentY) / 5.0f;

	m_pGameCamera->Zoom(changeY*0.05f);

	m_currentX = x;
	m_currentY = y;
}