#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

#include <GLFW/glfw3.h>


class VoxWindow
{
public:
	/* Public methods */
	VoxWindow();
	~VoxWindow();

	void Create();
	void Destroy();
	void Update(float dt);
	void Render();

	int GetWindowWidth();
	int GetWindowHeight();
	void ResizeWindow(int width, int height);

	int GetCursorX();
	int GetCursorY();

	// Events
	void PollEvents();
	int ShouldCloseWindow();

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
	GLFWwindow* window;

	int m_windowWidth;
	int m_windowHeight;

	int m_cursorX;
	int m_cursorY;
};