// ******************************************************************************
//
// Filename:	focusmanager.cpp
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

#include "focusmanager.h"

// Initialize the singleton instance
FocusManager *FocusManager::c_instance = 0;

FocusManager* FocusManager::GetInstance()
{
	if(c_instance == 0)
		c_instance = new FocusManager;

	return c_instance;
}

void FocusManager::Destroy()
{
	if(c_instance)
	{
		delete c_instance;
	}
}

void FocusManager::SetFocusOwner(Component* c)
{
	if(c == m_focusedComponent)
		return;

	Component* lOldFocus = m_focusedComponent;

	m_focusedComponent = c;

	// The new component has gained focus
	if(m_focusedComponent)
	{
		FocusEvent focusGainEvent(m_focusedComponent, FOCUS_GAINED);
		m_focusedComponent->ProcessFocusEvent(focusGainEvent);
	}

	// The old component has lost focus
	if(lOldFocus)
	{
		FocusEvent focusLostEvent(lOldFocus, FOCUS_LOST);
		lOldFocus->ProcessFocusEvent(focusLostEvent);
	}
}

Component* FocusManager::GetFocusOwner()
{
	return m_focusedComponent;
}

void FocusManager::KeyPressed(int keyCode, int modifier)
{
	if(m_focusedComponent != 0 )
	{
		KeyEvent keyPressedEvent(m_focusedComponent, KEY_PRESSED, keyCode, modifier);
		m_focusedComponent->ProcessKeyEvent(keyPressedEvent);
	}
}

void FocusManager::KeyReleased(int keyCode, int modifier)
{
	if(m_focusedComponent != 0 )
	{
		KeyEvent keyReleasedEvent(m_focusedComponent, KEY_RELEASED, keyCode, modifier);
		m_focusedComponent->ProcessKeyEvent(keyReleasedEvent);

		KeyEvent keyTypedEvent(m_focusedComponent, KEY_TYPED, keyCode, modifier);
		m_focusedComponent->ProcessKeyEvent(keyTypedEvent);
	}
}

void FocusManager::CharacterEntered(int characterCode)
{
	if(m_focusedComponent != 0 )
	{
		KeyEvent CharacterEnteredEvent(m_focusedComponent, CHARACTER_ENTERED, characterCode, 0);
		m_focusedComponent->ProcessKeyEvent(CharacterEnteredEvent);
	}
}

FocusManager::FocusManager()
  : m_focusedComponent(0)
{
}
