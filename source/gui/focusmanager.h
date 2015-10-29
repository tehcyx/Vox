// ******************************************************************************
//
// Filename:	focusmanager.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//	 Manages the focus of components and sends events to the components when
//	 focus has been lost or gained.
//
// Revision History:
//   Initial Revision - 09/07/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "component.h"


class FocusManager
{
public:
	/* Public methods */
	static FocusManager* GetInstance();
	void Destroy();

	void SetFocusOwner(Component* c);
	Component* GetFocusOwner();

	void KeyPressed(int keyCode, int modifier);
	void KeyReleased(int keyCode, int modifier);
	void CharacterEntered(int characterCode);

protected:
	/* Protected methods */

private:
	/* Private methods */
	FocusManager();
	FocusManager(const FocusManager&);
	FocusManager& operator=(const FocusManager&);

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	Component* m_focusedComponent;

	// Singleton instance
	static FocusManager *c_instance;
};
