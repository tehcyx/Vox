// ******************************************************************************
//
// Filename:	container.h
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

#include "container.h"


Container::Container(Renderer* pRenderer)
  : Component(pRenderer)
{
	/* Nothing */
}

Container::~Container()
{
	m_vpComponentList.clear();
}

void Container::AddEventListeners()
{
	ComponentList::const_iterator iterator;

	for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
	{
		(*iterator)->AddEventListeners();
	}
}

void Container::RemoveEventListeners()
{
	ComponentList::const_iterator iterator;

	for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
	{
		(*iterator)->RemoveEventListeners();
	}
}

bool Container::IsContainer() const
{
	return true;
}

bool Container::IsRootContainer() const
{
	return false;
}

bool Container::HasChildren() const
{
	return m_vpComponentList.size() != 0; 
}

void Container::SetEnabled(bool enable)
{
	ComponentList::const_iterator iterator;
	for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
	{
		(*iterator)->SetEnabled(enable);
	}

	Component::SetEnabled(enable);
}

void Container::SetDebugRender(bool debug)
{
	Component::SetDebugRender(debug);

	ComponentList::const_iterator iterator;
	for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
	{
		(*iterator)->SetDebugRender(debug);
	}
}

void Container::Add(Component* component)
{
	// Make this Container the added Components parent.
	component->SetParent(this);

	// Make sure it appears on top of the container
	//component->SetDepth(m_depth + 1.0f);

	// Add the Component to the vector
	m_vpComponentList.push_back(component);

	// Sort the component vector list, by depth
	DepthSortComponentChildren();
}

void Container::Remove(Component* component)
{
	// Find this component in the vector
	ComponentList::iterator iter = std::find(m_vpComponentList.begin(), m_vpComponentList.end(), component);

	if(iter != m_vpComponentList.end())
	{
		(*iter)->SetParent(0);

		// Erase the component
		m_vpComponentList.erase(iter);
	}
}

void Container::RemoveAll()
{
	ComponentList::const_iterator iterator;
	for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
	{
		(*iterator)->SetParent(0);

		(*iterator)->RemoveEventListeners();
	}

	m_vpComponentList.clear();
}

const ComponentList& Container::GetChildren() const
{
	return m_vpComponentList;
}

int Container::GetNumberOfChildren() const
{
	return static_cast<int>(m_vpComponentList.size());
}

void Container::DepthSortComponentChildren()
{
	sort(m_vpComponentList.begin(), m_vpComponentList.end(), Component::DepthLessThan);
}

Component* Container::GetChild(int n) const
{
	if(n > GetNumberOfChildren())
	{
		return 0;
	}
	else
	{
		ComponentList::const_iterator iterator;

		int i = 0;

		for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
		{
			if(i == n)
			{
				return (*iterator);
			}

			i++;
		}

		return 0;
	}
}

EComponentType Container::GetComponentType() const
{
	return EComponentType_Container;
}

void Container::SetAudio(bool set)
{
	Component::SetAudio(set);

    if(IsContainer() && HasChildren())
    {
        // Draw all children
        ComponentList::const_iterator iterator;

        for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
        {
            (*iterator)->SetAudio(set);
        }
    }
}

void Container::SetAudioVolume(float volume)
{
	Component::SetAudioVolume(volume);

    if(IsContainer() && HasChildren())
    {
        // Draw all children
        ComponentList::const_iterator iterator;

        for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
        {
            (*iterator)->SetAudioVolume(volume);
        }
    }
}

void Container::Update(float deltaTime)
{
	Component::Update(deltaTime);

	ComponentList::const_iterator iterator;

	// Update all children
	for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
	{
		if((*iterator)->IsVisible())
		{
			(*iterator)->Update(deltaTime);
		}
	}
}

void Container::DrawSelf()
{
	int l_containerWidth = m_dimensions.m_width;
	int l_containerHeight = m_dimensions.m_height;
	float l_depth = m_depth;

	float l_outlineX1 = 0.0f;
	float l_outlineX2 = (float)l_containerWidth;
	float l_outlineY1 = 0.0f;
	float l_outlineY2 = (float)l_containerHeight;

	m_pRenderer->PushMatrix();
		m_pRenderer->SetLineWidth(1.0f);
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 0.0f, 1.0f);
		m_pRenderer->EnableImmediateMode(IM_LINE_LOOP);
		m_pRenderer->ImmediateVertex(l_outlineX1, l_outlineY1, l_depth);
		m_pRenderer->ImmediateVertex(l_outlineX2, l_outlineY1, l_depth);
		m_pRenderer->ImmediateVertex(l_outlineX2 + 1, l_outlineY2, l_depth);
		m_pRenderer->ImmediateVertex(l_outlineX1, l_outlineY2, l_depth);
		m_pRenderer->DisableImmediateMode();
	m_pRenderer->PopMatrix();
}

void Container::DrawChildren()
{
	// This vector list is depth sorted, so we render in depth order, starting with the lowest depth first
	if(IsContainer() && HasChildren() && IsVisible())
	{
		// Draw all children
		ComponentList::const_iterator iterator;

		for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
		{
			if((*iterator)->IsVisible())
			{
				(*iterator)->Draw();
			}
		}
	}
}
