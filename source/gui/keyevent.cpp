// ******************************************************************************
//
// Filename:	mouseevent.cpp
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

#include "keyevent.h"


KeyEvent::KeyEvent(Component* source, int id, int keyCode, int modifier)
  :  Event(source, id),
     m_KeyCode(keyCode),
	 m_Modifier(modifier)
{
	/* Nothing */
}

KeyEvent::~KeyEvent()
{
	/* Nothing */
}

int KeyEvent::GetKeyCode() const
{
	return m_KeyCode;
}

int KeyEvent::GetModifier() const
{
	return m_Modifier;
}