// ******************************************************************************
//
// Filename:	keylistener.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   Key listener interface, inherit from this class if you need
//   to listen for and handle key events.
//
// Revision History:
//   Initial Revision - 29/06/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "eventlistener.h"
#include "keyevent.h"


class KeyListener :	public EventListener
{
public:
	/* Public methods */
	KeyListener();
	~KeyListener();

	virtual void KeyPressed(const KeyEvent& lEvent) {}
	virtual void KeyReleased(const KeyEvent& lEvent) {}
	virtual void KeyTyped(const KeyEvent& lEvent) {} // Pressed AND Released
	virtual void CharacterEntered(const KeyEvent& lEvent) {}

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
};
