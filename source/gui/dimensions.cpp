// ******************************************************************************
//
// Filename:	dimensions.cpp
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   Class to represent 2d rectangular spaces, useful for objects
//   such as windows, boxes, buttons, etc.
//
// Revision History:
//   Initial Revision - 18/09/06
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#include "dimensions.h"


Dimensions::Dimensions()
{
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
}

Dimensions::Dimensions(int x, int y, int width, int height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

Dimensions::~Dimensions()
{
	/* Nothing */
}

bool Dimensions::Contains(int x, int y)
{
	if((x >= m_x && x <= (m_x + m_width)) && (y >= m_y && y <= (m_y + m_height)))
		return true;

	return false;
}

bool Dimensions::Contains(const Point& point)
{
	return Contains(point.m_x, point.m_y);
}

bool Dimensions::operator==(const Dimensions& rhs)
{
	return ((m_x == rhs.m_x) && (m_y == rhs.m_y) && (m_width == rhs.m_width) && (m_height == rhs.m_height));
}