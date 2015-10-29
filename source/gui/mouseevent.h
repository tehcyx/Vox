// ******************************************************************************
//
// Filename:	mouseevent.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A mouse event class to handle events created by mouse input.
//
// Revision History:
//   Initial Revision - 06/10/06
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "event.h"


enum EMouseEvent
{
	MOUSE_PRESSED = 0,
	MOUSE_RELEASED,
	MOUSE_RELEASED_OUTSIDE,
	MOUSE_CLICKED,
	MOUSE_EXITED,
	MOUSE_DRAGGED,
	MOUSE_DRAGGED_OUTSIDE,  // Hack
	MOUSE_ENTERED,
	MOUSE_MOTION
};

enum EMouseButton
{
	MOUSE_BUTTON1 = 0,	// Left button
	MOUSE_BUTTON2,		// Right button
	MOUSE_BUTTON3,		// Middle button
	MOUSE_SCROLL_UP,
	MOUSE_SCROLL_DOWN
};

class MouseEvent : public Event
{
public:
	/* Public methods */
	MouseEvent(Component* source, int id, int x, int y, int mouseButton);

	~MouseEvent();

	int GetButton() const;
	int GetX() const;
	int GetY() const;

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
	int m_mouseX;
	int m_mouseY;
	int m_button;
};
