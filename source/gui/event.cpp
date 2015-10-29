// ******************************************************************************
//
// Filename:	event.cpp
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   An abstract event base class.
//
// Revision History:
//   Initial Revision - 06/10/06
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#include "event.h"


Event::Event(Component* source, int id)
  : m_pSource(source),
    m_eventId(id)
{
	/* Nothing */
}

Event::~Event()
{
	/* Nothing */
}

Component* Event::GetSource() const
{
	return m_pSource;
}

int Event::GetID() const
{
	return m_eventId;
}