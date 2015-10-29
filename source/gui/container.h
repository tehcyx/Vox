// ******************************************************************************
//
// Filename:	container.cpp
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A container to hold multiple components. Inclues
//   functionality for adding and removing components.
//
// Revision History:
//   Initial Revision - 23/09/06
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "component.h"


typedef std::vector<Component*> ComponentList;


class Container : public Component
{
public:
	/* Public methods */
	Container(Renderer* pRenderer);

	virtual ~Container();

	virtual void AddEventListeners();
	virtual void RemoveEventListeners();

	bool IsContainer() const;
	virtual bool IsRootContainer() const;

	bool HasChildren() const;

	void SetEnabled(bool enable);

	virtual void SetDebugRender(bool debug);

	virtual void Add(Component* component);
	virtual void Remove(Component* component);
	void RemoveAll();

	const ComponentList& GetChildren() const;
	Component* GetChild(int n) const;
	int GetNumberOfChildren() const;

	void DepthSortComponentChildren();

	EComponentType GetComponentType() const;

    virtual void SetAudio(bool set);
    virtual void SetAudioVolume(float volume);

	virtual void Update(float deltaTime);

protected:
	/* Protected methods */
	virtual void DrawSelf();
	virtual void DrawChildren();

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */
	ComponentList m_vpComponentList;

private:
	/* Private members */
};
