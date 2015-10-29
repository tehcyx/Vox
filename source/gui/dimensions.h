// ******************************************************************************
//
// Filename:	dimensions.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   Class to represent 2d rectangular space, useful for objects
//   such as windows, boxes, buttons, etc.
//
// Revision History:
//   Initial Revision - 18/09/06
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "point.h"


class Dimensions
{
public:
	/* Public methods */
	Dimensions();
	Dimensions(int x, int y, int width, int height);

	~Dimensions();

	bool Contains(int x, int y);
	bool Contains(const Point& point);

	bool operator==(const Dimensions& rhs);

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */
	int m_x;
	int m_y;
	int m_width;
	int m_height;

protected:
	/* Protected members */

private:
	/* Private members */
};
