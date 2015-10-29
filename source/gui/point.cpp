// ******************************************************************************
//
// Filename:	point.cpp
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   Class to represent a 2d point in space.
//
// Revision History:
//   Initial Revision - 18/09/06
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#include "point.h"

Point::Point()
{
	m_x = 0;
	m_y = 0;
}

Point::Point(int x, int y)
{
	m_x = x;
	m_y = y;
}

Point::~Point()
{
	/* Nothing */
}


bool Point::operator==(const Point& rhs)
{
	return ((m_x == rhs.m_x) && (m_y == rhs.m_x));
}