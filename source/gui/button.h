// ******************************************************************************
//
// Filename:	button.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A simple button class that defines standard
//   button behaviour.
//
// Revision History:
//   Initial Revision - 28/05/07
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "abstractbutton.h"


class Button : public AbstractButton, public MouseListener
{
public:
	/* Public methods */
	Button(Renderer* pRenderer, unsigned int GUIFont, const std::string &label);
	Button(Renderer* pRenderer, unsigned int GUIFont, unsigned int OutlineGUIFont, const std::string &label, Colour fontColour, Colour outlineColour);
	Button(Renderer* pRenderer, unsigned int GUIFont, const std::string &label, const std::string &defaultTexture, const std::string &selectedTexture, const std::string &hoverTexture, const std::string &disabledTexture);

	~Button();

	void AddText(Renderer* pRenderer, unsigned int GUIFont, unsigned int OutlineGUIFont, const std::string &label, Colour colour, int xOffset, int yOffset, bool outline = false, Colour outlineColour = Colour(1.0f, 1.0f, 1.0f, 1.0f));
	void AddIcon(Renderer* pRenderer, const std::string &fileName, int texWidth, int texHeight, int width, int height, int xOffset, int yOffset, float depth);

	void SetDimensions(int x, int y, int width, int height);
	void SetDimensions(const Dimensions& r);

	void SetLabelOffset(int x, int y);
	
	void SetPressedOffset(int x, int y);

	void SetNormalLabelColour(Colour normal);
	void SetHoverLabelColour(Colour hover);
	void SetPressedLabelColour(Colour pressed);	

	void SetLabelColour(Colour colour);
	void SetLabelOutlineColour(Colour colour);

	void AddEventListeners();
	void RemoveEventListeners();

	EComponentType GetComponentType() const;

protected:
	/* Protected methods */
	void MouseEntered(const MouseEvent& lEvent);
	void MouseExited(const MouseEvent& lEvent);
	void MousePressed(const MouseEvent& lEvent);
	void MouseReleased(const MouseEvent& lEvent);
	void MouseClicked(const MouseEvent& lEvent);

	virtual void OnMouseEnter();
	virtual void OnMouseExit();
	virtual void OnMousePressed();
	virtual void OnMouseReleased();
	virtual void OnMouseClicked();

	void DrawSelf();

private: 
	/* Private methods */


public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	ComponentList m_vpAddedComponentList;

	int m_pressedOffsetX;
	int m_pressedOffsetY;
	bool m_offsetApplied;

	bool m_bChangeLabelText;
	Colour m_normalLabelColour;
	Colour m_hoverLabelColour;
	Colour m_PressedLabelColour;
};
