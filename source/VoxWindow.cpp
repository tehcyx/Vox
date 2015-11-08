// ******************************************************************************
// Filename:	VoxWindow.cpp
// Project:		Vox
// Author:		Steven Ball
// 
// Revision History:
//   Initial Revision - 27/10/15
//
// Copyright (c) 2005-2015, Steven Ball
// ******************************************************************************

#include "glew/include/GL/glew.h"

#ifdef _WIN32
#include <windows.h>
#endif //_WIN32
#include <GL/gl.h>
#include <GL/glu.h>

#pragma comment (lib, "opengl32")
#pragma comment (lib, "glu32")

#include "VoxWindow.h"
#include "VoxGame.h"

// Callback functionality
void WindowResizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void MouseScrollCallback(GLFWwindow* window, double x, double y);


VoxWindow::VoxWindow()
{
	/* Minimized flag */
	m_minimized = false;

	/* Set default cursor positions */
	m_cursorX = 0;
	m_cursorY = 0;

	/* Default windows dimensions */
	m_windowWidth = 900;
	m_windowHeight = 900;
	m_oldWindowWidth = m_windowWidth;
	m_oldWindowHeight = m_windowHeight;
}

VoxWindow::~VoxWindow()
{
}

void VoxWindow::Create()
{
	/* Initialize the window library */
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	/* Initialize any rendering params */
	int samples = 8;
	glfwWindowHint(GLFW_SAMPLES, samples);
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glGetIntegerv(GL_SAMPLES_ARB, &samples);

	/* Create a windowed mode window and it's OpenGL context */
	window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Vox", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Initialize this window object */
	InitializeWindowContext(window);
}

void VoxWindow::Destroy()
{
	glfwTerminate();
}

void VoxWindow::Update(float dt)
{
	// Updae the cursor positions
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);

	m_cursorX = (int)floor(x);
	m_cursorY = (int)floor(y);
}

void VoxWindow::Render()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(window);
}

void VoxWindow::InitializeWindowContext(GLFWwindow* window)
{
	/* Window callbacks */
	glfwSetWindowSizeCallback(window, WindowResizeCallback);

	/* Input callbacks */
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);

	/* Center on screen */
	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwGetWindowSize(window, &m_windowWidth, &m_windowHeight);
	glfwSetWindowPos(window, (vidmode->width - m_windowWidth) / 2, (vidmode->height - m_windowHeight) / 2);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0); // Disable v-sync

	/* Force resize */
	WindowResizeCallback(window, m_windowWidth, m_windowHeight);

	/* Show the window */
	glfwShowWindow(window);
}

// Windows dimensions
int VoxWindow::GetWindowWidth()
{
	return m_windowWidth;
}

int VoxWindow::GetWindowHeight()
{
	return m_windowHeight;
}

void VoxWindow::ResizeWindow(int width, int height)
{
	m_minimized = (width == 0 || height == 0);

	m_windowWidth = width;
	m_windowHeight = height;
}

bool VoxWindow::GetMinimized()
{
	return m_minimized;
}

// Cursor position
int VoxWindow::GetCursorX()
{
	return m_cursorX;
}

int VoxWindow::GetCursorY()
{
	return m_cursorY;
}

// Fullscreen
void VoxWindow::ToggleFullScreen(bool fullscreen)
{
	if (fullscreen)
	{
		const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		m_oldWindowWidth = m_windowWidth;
		m_oldWindowHeight = m_windowHeight;

		m_windowWidth = vidMode->width;
		m_windowHeight = vidMode->height;
	}
	else
	{
		m_windowWidth = m_oldWindowWidth;
		m_windowHeight = m_oldWindowHeight;
	}

	// Create new window
	GLFWwindow* newWindow = glfwCreateWindow(m_windowWidth, m_windowHeight, "Vox", fullscreen ? glfwGetPrimaryMonitor() : NULL, window);

	/* Initialize this new window object */
	InitializeWindowContext(newWindow);

	// Destroy the existing window pointer and assign new one, since we are context switching
	glfwDestroyWindow(window);
	window = newWindow;
}

// Events
void VoxWindow::PollEvents()
{
	/* Poll for and process events */
	glfwPollEvents();
}

int VoxWindow::ShouldCloseWindow()
{
	return glfwWindowShouldClose(window);
}

// Callbacks
void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	VoxGame::GetInstance()->ResizeWindow(width, height);
}
