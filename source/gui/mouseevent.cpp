// ******************************************************************************
//
// Filename:	mouseevent.cpp
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

#include "mouseevent.h"


MouseEvent::MouseEvent(Component* source, int id, int x, int y, int mouseButton)
  : Event(source, id),
	m_mouseX(x),
	m_mouseY(y),
	m_button(mouseButton)
{
	/* Nothing */
}

MouseEvent::~MouseEvent()
{
	/* Nothing */
}

int MouseEvent::GetButton() const
{
	return m_button;
}

int MouseEvent::GetX() const
{
	return m_mouseX;
}

int MouseEvent::GetY() const
{
	return m_mouseY;
}