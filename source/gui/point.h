// ******************************************************************************
//
// Filename:	point.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   Class to represent a 2d point in 2d screen space.
//
// Revision History:
//   Initial Revision - 18/09/06
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

class Point
{
public:
	/* Public methods */
	Point();
	Point(int x, int y);

	~Point();

	bool operator==(const Point& rhs);

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */
	int m_x;
	int m_y;

protected:
	/* Protected members */

private:
	/* Private members */
};
