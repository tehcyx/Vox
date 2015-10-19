#include "../glew/include/GL/glew.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

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
	m_windowWidth = 800;
	m_windowHeight = 800;
	window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Vox", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Set default cursor positions */
	m_cursorX = 0;
	m_cursorY = 0;

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

	/* Show the window */
	glfwShowWindow(window);
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
	m_windowWidth = width;
	m_windowHeight = height;
}

int VoxWindow::GetCursorX()
{
	return m_cursorX;
}

int VoxWindow::GetCursorY()
{
	return m_cursorY;
}

void VoxWindow::PollEvents()
{
	/* Poll for and process events */
	glfwPollEvents();
}

int VoxWindow::ShouldCloseWindow()
{
	return glfwWindowShouldClose(window);
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	VoxGame::GetInstance()->ResizeWindow(width, height);
}
