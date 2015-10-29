// ******************************************************************************
//
// Filename:	abstractbutton.cpp
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   An abstract button class used as a base
//   class for all button related components.
//
// Revision History:
//   Initial Revision - 28/05/07
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#include "abstractbutton.h"


AbstractButton::AbstractButton(Renderer* pRenderer, unsigned int GUIFont, const std::string &label)
  : Container(pRenderer),
    m_label(pRenderer, GUIFont, label, Colour(1.0f, 1.0f, 1.0f)),
    m_pDefaultIcon(0),
    m_pSelectedIcon(0),
	m_pHoverIcon(0),
	m_pDisabledIcon(0),
	m_bSelected(false),
	m_bHover(false),
	m_bDisabled(false)
{
	m_bDisplayLabel = true;

	m_Callback = NULL;
	m_pCallbackData = NULL;

	m_Callback_Pressed = NULL;
	m_pCallbackData_Pressed = NULL;

	m_Callback_Released = NULL;
	m_pCallbackData_Released = NULL;

	m_EnterCallback = NULL;
	m_pEnterCallbackData = NULL;

	m_ExitCallback = NULL;
	m_pExitCallbackData = NULL;

	m_labelOffsetX = 0;
	m_labelOffsetY = 0;

	m_enterSound = false;
	m_exitSound = false;
	m_pressedSound = false;
	m_clickedSound = false;
}

AbstractButton::~AbstractButton()
{
}

void AbstractButton::SetLabel(const string &label)
{
	m_label.SetText(label);
	
	// Set the label location to be the center of the button
	int buttonLabelHeight = m_pRenderer->GetFreeTypeTextHeight(m_label.GetFontID(), "%s", m_label.GetText().c_str());
	int buttonLabelWidth = m_pRenderer->GetFreeTypeTextWidth(m_label.GetFontID(), "%s", m_label.GetText().c_str());
	int m_center_width = (int)((m_dimensions.m_width * 0.5f ) - (buttonLabelWidth * 0.5f));
	int m_center_height = (int)((m_dimensions.m_height * 0.5f) - (buttonLabelHeight * 0.5f));
	m_label.SetLocation(m_center_width + m_labelOffsetX, m_center_height + m_labelOffsetY);
}


void AbstractButton::SetDisplayLabel(bool display)
{
	m_bDisplayLabel = display;
}

void AbstractButton::SetDefaultIcon(RenderRectangle *icon)
{
	MultiTextureIcon* lpMulti = dynamic_cast<MultiTextureIcon*>(icon);
	Icon* lpIcon = dynamic_cast<Icon*>(icon);
	DirectDrawRectangle* lpDirectDraw = dynamic_cast<DirectDrawRectangle*>(icon);

	if(m_pDefaultIcon)
	{
		// If we already own a default icon, remove it from out component list and also delete it, since we will be replacing it
		Remove(m_pDefaultIcon);

		delete m_pDefaultIcon;
		m_pDefaultIcon = NULL;
	}

	// Check what type of render rectangle we have been given, and then assign our new data
	if(lpMulti)
	{
		MultiTextureIcon* lpNewMulti = new MultiTextureIcon((*lpMulti));
		m_pDefaultIcon = lpNewMulti;
	}
	else if(lpIcon)
	{
		Icon* lpNewIcon = new Icon((*lpIcon));
		m_pDefaultIcon = lpNewIcon;
	}
	else if(lpDirectDraw)
	{
		DirectDrawRectangle* lpNewDirectDraw = new DirectDrawRectangle((*lpDirectDraw));
		m_pDefaultIcon = lpNewDirectDraw;
	}

	// Re-add this icon to the component list
	Add(m_pDefaultIcon);
}

void AbstractButton::SetSelectedIcon(RenderRectangle *icon)
{
	MultiTextureIcon* lpMulti = dynamic_cast<MultiTextureIcon*>(icon);
	Icon* lpIcon = dynamic_cast<Icon*>(icon);
	DirectDrawRectangle* lpDirectDraw = dynamic_cast<DirectDrawRectangle*>(icon);

	if(m_pSelectedIcon)
	{
		// If we already own a selected icon, remove it from out component list and also delete it, since we will be replacing it
		Remove(m_pSelectedIcon);

		delete m_pSelectedIcon;
		m_pSelectedIcon = NULL;
	}

	// Check what type of render rectangle we have been given, and then create a new copy of it
	if(lpMulti)
	{
		MultiTextureIcon* lpNewMulti = new MultiTextureIcon((*lpMulti));
		m_pSelectedIcon = lpNewMulti;
	}
	else if(lpIcon)
	{
		Icon* lpNewIcon = new Icon((*lpIcon));
		m_pSelectedIcon = lpNewIcon;
	}
	else if(lpDirectDraw)
	{
		DirectDrawRectangle* lpNewDirectDraw = new DirectDrawRectangle((*lpDirectDraw));
		m_pSelectedIcon = lpNewDirectDraw;
	}

	// Re-add this icon to the component list
	Add(m_pSelectedIcon);
}

void AbstractButton::SetHoverIcon(RenderRectangle *icon)
{
	MultiTextureIcon* lpMulti = dynamic_cast<MultiTextureIcon*>(icon);
	Icon* lpIcon = dynamic_cast<Icon*>(icon);
	DirectDrawRectangle* lpDirectDraw = dynamic_cast<DirectDrawRectangle*>(icon);

	if(m_pHoverIcon)
	{
		// If we already own a hover icon, remove it from out component list and also delete it, since we will be replacing it
		Remove(m_pHoverIcon);

		delete m_pHoverIcon;
		m_pHoverIcon = NULL;
	}

	// Check what type of render rectangle we have been given, and then assign our new data
	if(lpMulti)
	{
		MultiTextureIcon* lpNewMulti = new MultiTextureIcon((*lpMulti));
		m_pHoverIcon = lpNewMulti;
	}
	else if(lpIcon)
	{
		Icon* lpNewIcon = new Icon((*lpIcon));
		m_pHoverIcon = lpNewIcon;
	}
	else if(lpDirectDraw)
	{
		DirectDrawRectangle* lpNewDirectDraw = new DirectDrawRectangle((*lpDirectDraw));
		m_pHoverIcon = lpNewDirectDraw;
	}

	// Re-add this icon to the component list
	Add(m_pHoverIcon);
}

void AbstractButton::SetDisabledIcon(RenderRectangle *icon)
{
	MultiTextureIcon* lpMulti = dynamic_cast<MultiTextureIcon*>(icon);
	Icon* lpIcon = dynamic_cast<Icon*>(icon);
	DirectDrawRectangle* lpDirectDraw = dynamic_cast<DirectDrawRectangle*>(icon);

	if(m_pDisabledIcon)
	{
		// If we already own a disabled icon, remove it from out component list and also delete it, since we will be replacing it
		Remove(m_pDisabledIcon);

		delete m_pDisabledIcon;
		m_pDisabledIcon = NULL;
	}

	// Check what type of render rectangle we have been given, and then assign our new data
	if(lpMulti)
	{
		MultiTextureIcon* lpNewMulti = new MultiTextureIcon((*lpMulti));
		m_pDisabledIcon = lpNewMulti;
	}
	else if(lpIcon)
	{
		Icon* lpNewIcon = new Icon((*lpIcon));
		m_pDisabledIcon = lpNewIcon;
	}
	else if(lpDirectDraw)
	{
		DirectDrawRectangle* lpNewDirectDraw = new DirectDrawRectangle((*lpDirectDraw));
		m_pDisabledIcon = lpNewDirectDraw;
	}

	// Re-add this icon to the component list
	Add(m_pDisabledIcon);
}

void AbstractButton::SetEnterAudio(const char* filename)
{
	m_enterSound = true;
	sprintf_s(m_enterSoundFilename, 64, "%s", filename);
}

void AbstractButton::SetExitAudio(const char* filename)
{
	m_exitSound = true;
	sprintf_s(m_exitSoundFilename, 64, "%s", filename);
}

void AbstractButton::SetPressedAudio(const char* filename)
{
	m_pressedSound = true;
	sprintf_s(m_pressedSoundFilename, 64, "%s", filename);
}

void AbstractButton::SetClickedAudio(const char* filename)
{
	m_clickedSound = true;
	sprintf_s(m_clickedSoundFilename, 64, "%s", filename);
}

Label AbstractButton::GetLabel() const
{
	return m_label;
}

void AbstractButton::SetSelected(bool val)
{
	m_bSelected = val;

	// TEMP : Remove button state animations until animation switching can be worked on.
	/*
	if(m_bSelected)
	{
		SetAnimation(m_pSelectedAnimation);
	}
	else
	{
		if(m_bHover)
		{
			SetAnimation(m_pHoverAnimation);
		}
		else
		{
			SetAnimation(m_pDefaultAnimation);
		}
	}
	*/
}

void AbstractButton::SetHover(bool val)
{
	m_bHover = val;

	// TEMP : Remove button state animations until animation switching can be worked on.
	/*
	if(m_bHover)
	{
		SetAnimation(m_pHoverAnimation);
	}
	else
	{
		if(m_bSelected)
		{
			SetAnimation(m_pSelectedAnimation);
		}
		else
		{
			SetAnimation(m_pDefaultAnimation);
		}
	}
	*/
}

void AbstractButton::SetDisabled(bool val)
{
	m_bDisabled = val;

	if(m_bDisabled)
	{
		SetSelected(false);
		SetHover(false);

		// TEMP : Remove button state animations until animation switching can be worked on.
		//SetAnimation(m_pDisabledAnimation);
	}
}

bool AbstractButton::IsSelected() const
{
	return m_bSelected;
}

bool AbstractButton::IsHover() const
{
	return m_bHover;
}

bool AbstractButton::IsDisabled() const
{
	return m_bDisabled;
}

void AbstractButton::SetCallBackFunction(FunctionCallback lFunction)
{
	m_Callback = lFunction;
}

void AbstractButton::SetCallBackData(void *lpData)
{
	m_pCallbackData = lpData;
}

void AbstractButton::SetCallBackFunction_Pressed(FunctionCallback lFunction)
{
	m_Callback_Pressed = lFunction;
}

void AbstractButton::SetCallBackData_Pressed(void *lpData)
{
	m_pCallbackData_Pressed = lpData;
}

void AbstractButton::SetCallBackFunction_Released(FunctionCallback lFunction)
{
	m_Callback_Released = lFunction;
}

void AbstractButton::SetCallBackData_Released(void *lpData)
{
	m_pCallbackData_Released = lpData;
}


void AbstractButton::SetEnterCallBackFunction(FunctionCallback lFunction)
{
	m_EnterCallback = lFunction;
}

void AbstractButton::SetEnterCallBackData(void *lpData)
{
	m_pEnterCallbackData = lpData;
}

void AbstractButton::SetExitCallBackFunction(FunctionCallback lFunction)
{
	m_ExitCallback = lFunction;
}

void AbstractButton::SetExitCallBackData(void *lpData)
{
	m_pExitCallbackData = lpData;
}

EComponentType AbstractButton::GetComponentType() const
{
	return EComponentType_AbstractButton;
}