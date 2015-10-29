// ******************************************************************************
//
// Filename:	checkbox.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A checkbox GUI widget
//
// Revision History:
//   Initial Revision - 26/01/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "abstractbutton.h"


class CheckBox : public AbstractButton, public MouseListener
{
public:
	/* Public methods */
	CheckBox(Renderer* pRenderer, unsigned int GUIFont, const std::string &label);
	CheckBox(Renderer* pRenderer, unsigned int GUIFont, unsigned int OutlineGUIFont, const std::string &label, Colour fontColour, Colour outlineColour);
	CheckBox(Renderer* pRenderer, unsigned int GUIFont, const std::string &label, const std::string &defaultTexture, const std::string &selectedTexture, const std::string &hoverTexture, const std::string &disabledTexture,
																						const std::string &toggledTexture, const std::string &toggledSelectedTexture, const std::string &toggledHoverTexture, const std::string &toggledDisabledTexture);

	~CheckBox();

	void AddEventListeners();
	void RemoveEventListeners();

	void SetToggledIcon(RenderRectangle *icon);
	void SetToggledSelectedIcon(RenderRectangle *icon);
	void SetToggledHoverIcon(RenderRectangle *icon);
	void SetToggledDisabledIcon(RenderRectangle *icon);

	void SetDimensions(int x, int y, int width, int height);
	void SetDimensions(const Dimensions& r);

	void SetPressedOffset(int x, int y);

	void SetHoverLabelColour(Colour hover);
	void SetPressedLabelColour(Colour pressed);	

	bool GetToggled() const;
	void SetToggled(bool toggle);

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
	RenderRectangle *m_pToggledIcon;
	RenderRectangle *m_pToggledSelectedIcon;
	RenderRectangle *m_pToggledHoverIcon;
	RenderRectangle *m_pToggledDisabledIcon;

	bool m_bToggled;

	int m_pressedOffsetX;
	int m_pressedOffsetY;
	bool m_offsetApplied;

	bool m_bChangeLabelText;
	Colour m_normalLabelColour;
	Colour m_hoverLabelColour;
	Colour m_PressedLabelColour;
};
