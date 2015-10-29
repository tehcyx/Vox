// ******************************************************************************
//
// Filename:	openglgui.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   Class to manage everything related to the GUI. Has methods
//   that must be called for the GUI to function properly such as
//   Render() and Update(). Also requires access to input events.
//
// Revision History:
//   Initial Revision - 27/09/06
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "component.h"
#include "container.h"
#include "abstractbutton.h"
#include "button.h"
#include "checkbox.h"
#include "optionbox.h"
#include "optioncontroller.h"
#include "menubar.h"
#include "menu.h"
#include "menuitem.h"
#include "label.h"
#include "formattedlabel.h"
#include "renderrectangle.h"
#include "directdrawrectangle.h"
#include "icon.h"
#include "multitextureicon.h"
#include "draggablerenderrectangle.h"
#include "slider.h"
#include "titlebar.h"
#include "guiwindow.h"
#include "textbox.h"
#include "multilinetextbox.h"
#include "progressbar.h"
#include "scrollbar.h"
#include "pulldownmenu.h"
#include "treeview.h"


class OpenGLGUI
{
public:
	/* Public methods */
	OpenGLGUI(Renderer* pRenderer);

	~OpenGLGUI();

	bool IsMouseInteractingWithGUIComponent(bool ignoreGUIWindows) const;
	bool IsKeyboardInteractingWithGUIComponent() const;
	Component* GetCurrentMouseInteractionComponent() const;

	void AddWindow(GUIWindow* window);
	void RemoveWindow(GUIWindow* window);

	void SetFocusedWindow(GUIWindow* window);
	
	void SetComponentFocus(Component* component);
	void ResetFocus();

	void AddComponent(Component* component);
	void RemoveComponent(Component *component);

	Component* GetComponent(Component *component);

	void SetDraggingComponentPriority(Component* pDraggingComponentPriority);

	void SetDebugRender(bool debug);
	bool IsDebugRender();

	void Render();

	void Update(float deltaTime);

	void ImportMouseMotion(int x, int y);
	void MousePressed(int button);
	void MouseReleased(int button);

	void KeyPressed(int keyCode, int modifier);
	void KeyReleased(int keyCode, int modifier);
	void CharacterEntered(int characterCode);

	void DepthSortGUIWindowChildren();
	void DepthSortComponentChildren();

    void SetAudio(bool set);
    void SetAudioVolume(float volume);

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
	int m_mouseX;
	int m_mouseY;

	GUIWindowList m_vpGUIWindowList;

	ComponentList m_vpComponentList;
	Component* m_pDraggingComponentPriority;

	Renderer* m_pRenderer;

	unsigned int m_GUIViewport;

	unsigned int m_GUIFont;

	bool m_bDegubRender;

	float m_currentWindowDepth;

	bool m_audio;
	float m_audioVolume;

	GUIWindow* m_pFocusedWindow;
};