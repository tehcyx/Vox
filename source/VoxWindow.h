// ******************************************************************************
// Filename:	VoxWindow.h
// Project:		Vox
// Author:		Steven Ball
//
// Purpose:
//   Vox window class.
// 
// Revision History:
//   Initial Revision - 27/10/15
//
// Copyright (c) 2005-2015, Steven Ball
// ******************************************************************************

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

	void InitializeWindowContext(GLFWwindow* window);

	// Windows dimensions
	int GetWindowWidth();
	int GetWindowHeight();
	void ResizeWindow(int width, int height);

	// Minimized
	bool GetMinimized();

	// Cursor position
	int GetCursorX();
	int GetCursorY();

	// Fullscreen
	void ToggleFullScreen(bool fullscreen);

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

	// Window dimensions
	int m_windowWidth;
	int m_windowHeight;
	int m_oldWindowWidth;
	int m_oldWindowHeight;

	bool m_minimized;

	// Cursor position
	int m_cursorX;
	int m_cursorY;
};