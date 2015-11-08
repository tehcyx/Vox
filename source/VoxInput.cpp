#include <stdio.h>
#include <stdlib.h>

#include "VoxGame.h"


// Input callbacks
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

// Input
void VoxGame::KeyPressed(int key, int scancode, int mods)
{
	switch (key)
	{
		// Player movement
		case GLFW_KEY_W:
		{
			m_bKeyboardForward = true;
			break;
		}
		case GLFW_KEY_S:
		{
			m_bKeyboardBackward = true;
			break;
		}
		case GLFW_KEY_A:
		{
			m_bKeyboardLeft = true;
			m_bKeyboardStrafeLeft = true;
			break;
		}
		case GLFW_KEY_D:
		{
			m_bKeyboardRight = true;
			m_bKeyboardStrafeRight = true;
			break;
		}
		case GLFW_KEY_F:
		{
			m_bKeyboardUp = true;
			break;
		}
		case GLFW_KEY_V:
		{
			m_bKeyboardDown = true;
			break;
		}
		case GLFW_KEY_SPACE:
		{
			m_bKeyboardSpace = true;
			break;
		}
	}
}

void VoxGame::KeyReleased(int key, int scancode, int mods)
{
	switch (key)
	{
		// Player movement
		case GLFW_KEY_W:
		{
			m_bKeyboardForward = false;
			break;
		}
		case GLFW_KEY_S:
		{
			m_bKeyboardBackward = false;
			break;
		}
		case GLFW_KEY_A:
		{
			m_bKeyboardLeft = false;
			m_bKeyboardStrafeLeft = false;
			break;
		}
		case GLFW_KEY_D:
		{
			m_bKeyboardRight = false;
			m_bKeyboardStrafeRight = false;
			break;
		}
		case GLFW_KEY_F:
		{
			m_bKeyboardUp = false;
			break;
		}
		case GLFW_KEY_V:
		{
			m_bKeyboardDown = false;
			break;
		}
		case GLFW_KEY_SPACE:
		{
			m_bKeyboardSpace = false;
			break;
		}
	}
}

void VoxGame::MouseLeftPressed()
{
	m_pGUI->MousePressed(MOUSE_BUTTON1);

	if (!m_pGUI->IsMouseInteractingWithGUIComponent(false))
	{
		m_currentX = m_pVoxWindow->GetCursorX();
		m_currentY = m_pVoxWindow->GetCursorY();
		m_pressedX = m_currentX;
		m_pressedY = m_currentY;

		m_bCameraRotate = true;
	}
}

void VoxGame::MouseLeftReleased()
{
	m_pGUI->MouseReleased(MOUSE_BUTTON1);

	m_bCameraRotate = false;
}

void VoxGame::MouseRightPressed()
{
	m_pGUI->MousePressed(MOUSE_BUTTON2);

	if (!m_pGUI->IsMouseInteractingWithGUIComponent(false))
	{
		m_currentX = m_pVoxWindow->GetCursorX();
		m_currentY = m_pVoxWindow->GetCursorY();
		m_pressedX = m_currentX;
		m_pressedY = m_currentY;
	}
}

void VoxGame::MouseRightReleased()
{
	m_pGUI->MouseReleased(MOUSE_BUTTON2);
}

void VoxGame::MouseMiddlePressed()
{
	m_pGUI->MousePressed(MOUSE_BUTTON3);
}

void VoxGame::MouseMiddleReleased()
{
	m_pGUI->MouseReleased(MOUSE_BUTTON3);
}

void VoxGame::MouseScroll(double x, double y)
{
	if (!m_pGUI->IsMouseInteractingWithGUIComponent(true))
	{
		m_maxCameraDistance += (float)(-y*0.5f);

		float minAmount = 0.0f;
		float maxAmount = 15.0f;

		if (m_gameMode == GameMode_Game && m_cameraMode == CameraMode_AutoCamera)
		{
			minAmount = 3.0f;
			maxAmount = 15.0f;
		}

		if (m_maxCameraDistance <= minAmount)
		{
			m_maxCameraDistance = minAmount;
		}

		if (m_maxCameraDistance >= maxAmount)
		{
			m_maxCameraDistance = maxAmount;
		}
	}
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
	
	if (m_cameraMode == CameraMode_FirstPerson)
	{
		changeY = -changeY;
	}

	// Limit the rotation, so we can't go 'over' or 'under' the player with out rotations
	vec3 cameraFacing = m_pGameCamera->GetFacing();
	float dotResult = acos(dot(cameraFacing, vec3(0.0f, 1.0f, 0.0f)));
	float rotationDegrees = RadToDeg(dotResult) - 90.0f;
	float limitAngle = 75.0f;
	if ((rotationDegrees > limitAngle && changeY < 0.0f) || (rotationDegrees < -limitAngle && changeY > 0.0f))
	{
		changeY = 0.0f;
	}

	if (m_cameraMode == CameraMode_FirstPerson)
	{
		m_pGameCamera->Rotate(changeY*0.75f, 0.0f, 0.0f);
		m_pGameCamera->RotateY(-changeX*0.75f);
	}
	else
	{
		m_pGameCamera->RotateAroundPoint(changeY*0.75f, 0.0f, 0.0f);
		m_pGameCamera->RotateAroundPointY(-changeX*0.75f);
	}

	m_currentX = x;
	m_currentY = y;
}