// ******************************************************************************
//
// Filename:	event.h
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

#pragma once

// Foreward declaration of component class
class Component;

class Event
{
public:
	/* Public methods */
	Event(Component* source, int id);

	~Event();

	Component* GetSource() const;
	int GetID() const;

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
	int m_eventId;
	Component* m_pSource;
};
