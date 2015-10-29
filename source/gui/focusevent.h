// ******************************************************************************
//
// Filename:	focusevent.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A focus event class to handle events created by focus changes,
//	 i.e Components gaining and losing focus from mouse/keyboard input.
//
// Revision History:
//   Initial Revision - 09/07/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "event.h"

enum eFocusEvent
{
	FOCUS_GAINED,
	FOCUS_LOST
};

class FocusEvent : public Event
{
public:
	/* Public methods */
	FocusEvent(Component* source, int id);

	~FocusEvent();

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
