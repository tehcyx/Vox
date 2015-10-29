// ******************************************************************************
//
// Filename:	mouseevent.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A key event class to handle events created by keyboard input.
//
// Revision History:
//   Initial Revision - 29/06/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "event.h"


enum eKeyEvent
{
	KEY_PRESSED = 0,
	KEY_RELEASED,
	KEY_TYPED,

	CHARACTER_ENTERED,
};

class KeyEvent : public Event
{
public:
	/* Public methods */
	KeyEvent(Component* source, int id, int keyCode, int modifier);

	~KeyEvent();

	int GetKeyCode() const;
	int GetModifier() const;

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
	int m_KeyCode;
	int m_Modifier;
};
