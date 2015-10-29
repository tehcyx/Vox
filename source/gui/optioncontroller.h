// ******************************************************************************
//
// Filename:	optioncontroller.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A controller for a group of option boxes
//
// Revision History:
//   Initial Revision - 02/02/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "container.h"
#include "optionbox.h"


class OptionController : public Container
{
public:
	/* Public methods */
	OptionController(Renderer* pRenderer, unsigned int GUIFont, const std::string &label);
	OptionController(Renderer* pRenderer, unsigned int GUIFont, unsigned int OutlineGUIFont, const std::string &label, Colour fontColour, Colour outlineColour);

	~OptionController();

	void SetVisible(bool Visible);
	bool IsVisible() const;

	void SetDimensions(int x, int y, int width, int height);
	void SetDimensions(const Dimensions& r);

	void SetDisplayLabel(bool display);
	void SetDisplayBorder(bool display);

	void SetActiveOption(OptionBox *lpOption);
	OptionBox *GetActiveOption() const;

	void ResetAllOptions();

	EComponentType GetComponentType() const;

protected:
	/* Protected methods */
	void DrawSelf();

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	Label m_label;

	int m_labelIndent;

	bool mbDisplayLabel;
	bool mbDisplayBorder;

	OptionBox* m_pActiveOption;
};