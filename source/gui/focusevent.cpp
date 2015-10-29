// ******************************************************************************
//
// Filename:	focusevent.cpp
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

#include "focusevent.h"

FocusEvent::FocusEvent(Component* source, int id)
  :  Event(source, id)
{
	/* Nothing */
}

FocusEvent::~FocusEvent()
{
	/* Nothing */
}
