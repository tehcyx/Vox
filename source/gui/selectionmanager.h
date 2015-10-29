// ******************************************************************************
//
// Filename:	selectionmanager.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   Handles the picking of components, events are sent to the currently
//   selected component. This is worked out using component bounding boxes.
//
// Note:
//   The actual algorithm for working out what component is currently
//   selected doesn't have to be mathematically, we could use the opengl
//   selection buffer, colour picking or a number of other methods.
//
// Revision History:
//   Initial Revision - 15/10/06
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "component.h"
#include "container.h"


class SelectionManager
{
public:
	/* Public methods */
	static SelectionManager* GetInstance();
	void Destroy();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	void Update(int x, int y);
	Component* GetComponentAt(int x, int y);

	Component* GetCurrentComponent() const;

	void MouseMotion(int x, int y);
	void MousePressed(int button);
	void MouseReleased(int button);

protected:
	/* Protected methods */

private:
	/* Private methods */
	SelectionManager();
	SelectionManager(const SelectionManager&);
	SelectionManager& operator=(const SelectionManager&);

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	ComponentList m_vpComponentList;

	Component* m_foundComponent;
	Component* m_hoverOverComponent;
	Component* m_firstClickedComponent;

	bool m_bPressed;
	int m_buttonPressed;

	int m_mouseX;
	int m_mouseY;
	int m_lastX;
	int m_lastY;

	// Singleton instance
	static SelectionManager *c_instance;
};
