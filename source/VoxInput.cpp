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

	m_currentX = m_pVoxWindow->GetCursorX();
	m_currentY = m_pVoxWindow->GetCursorY();
	m_pressedX = m_currentX;
	m_pressedY = m_currentY;

	m_bCameraZoom = true;
}

void VoxGame::MouseRightReleased()
{
	m_pGUI->MouseReleased(MOUSE_BUTTON2);

	m_bCameraZoom = false;
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

	m_pGameCamera->RotateAroundPoint(changeY*0.5f, -changeX*0.5f, 0.0f);
	//m_pGameCamera->Rotate(changeY*0.5f, -changeX*0.5f, 0.0f);

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