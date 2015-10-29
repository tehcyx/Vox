// ******************************************************************************
//
// Filename:	guiwindowminimizebutton.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A button that is included in the title bar of a gui window
//   clicking on this button will minimize the window.
//
// Revision History:
//   Initial Revision - 22/01/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "button.h"


// Forward declaration
class GUIWindow;


class GUIWindowMinimizeButton : public Button
{
public:
	/* Public methods */
	GUIWindowMinimizeButton(Renderer* pRenderer, unsigned int GUIFont, const std::string &label);
	
	~GUIWindowMinimizeButton();

	void SetGUIWindowParent(GUIWindow *pParent);

protected:
	/* Protected methods */
	virtual void OnMouseEnter();
	virtual void OnMouseExit();
	virtual void OnMousePressed();
	virtual void OnMouseReleased();
	virtual void OnMouseClicked();

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	GUIWindow *m_pParentGUIWindow;
};
