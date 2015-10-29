// ******************************************************************************
//
// Filename:	directdrawrectangle.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A rendered rectangle that is drawn directly by OpenGL, using primitives.
//
// Revision History:
//   Initial Revision - 07/08/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#include "directdrawrectangle.h"


DirectDrawRectangle::DirectDrawRectangle(Renderer* pRenderer)
  : RenderRectangle(pRenderer)
{
}

DirectDrawRectangle::~DirectDrawRectangle()
{
}

void DirectDrawRectangle::SetBackgroundColourTopLeft(Colour col)
{
	mBackgroundColourTopLeft = col;
}

void DirectDrawRectangle::SetBackgroundColourTopRight(Colour col)
{
	mBackgroundColourTopRight = col;
}

void DirectDrawRectangle::SetBackgroundColourBottomLeft(Colour col)
{
	mBackgroundColourBottomLeft = col;
}

void DirectDrawRectangle::SetBackgroundColourBottomRight(Colour col)
{
	mBackgroundColourBottomRight = col;
}

void DirectDrawRectangle::SetOutlineColourTop(Colour col)
{
	mOutlineColourTop = col;
}

void DirectDrawRectangle::SetOutlineColourBottom(Colour col)
{
	mOutlineColourBottom = col;
}

void DirectDrawRectangle::SetOutlineColourLeft(Colour col)
{
	mOutlineColourLeft = col;
}

void DirectDrawRectangle::SetOutlineColourRight(Colour col)
{
	mOutlineColourRight = col;
}

EComponentType DirectDrawRectangle::GetComponentType() const
{
	return EComponentType_DirectDrawRectangle;
}

void DirectDrawRectangle::DrawSelf()
{
	int l_containerWidth = m_dimensions.m_width;
	int l_containerHeight = m_dimensions.m_height;
	float l_depth = GetDepth();

	float l_containerX1 = 0.5f;
	float l_containerX2 = (float)l_containerWidth;
	float l_containerY1 = 0.5f;
	float l_containerY2 = (float)l_containerHeight;

	float l_outlineX1 = -0.5f;
	float l_outlineX2 = l_containerWidth + 0.5f;
	float l_outlineY1 = 0.0f;
	float l_outlineY2 = l_containerHeight + 0.5f;

	// Draw the background
	m_pRenderer->PushMatrix();
		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->EnableImmediateMode(IM_QUADS);
		m_pRenderer->ImmediateColourAlpha(mBackgroundColourBottomLeft.GetRed(), mBackgroundColourBottomLeft.GetGreen(), mBackgroundColourBottomLeft.GetBlue(), mBackgroundColourBottomLeft.GetAlpha());
		m_pRenderer->ImmediateVertex(l_containerX1, l_containerY1, l_depth);
		m_pRenderer->ImmediateColourAlpha(mBackgroundColourBottomRight.GetRed(), mBackgroundColourBottomRight.GetGreen(), mBackgroundColourBottomRight.GetBlue(), mBackgroundColourBottomRight.GetAlpha());
		m_pRenderer->ImmediateVertex(l_containerX2, l_containerY1, l_depth);
		m_pRenderer->ImmediateColourAlpha(mBackgroundColourTopRight.GetRed(), mBackgroundColourTopRight.GetGreen(), mBackgroundColourTopRight.GetBlue(), mBackgroundColourTopRight.GetAlpha());
		m_pRenderer->ImmediateVertex(l_containerX2, l_containerY2, l_depth);
		m_pRenderer->ImmediateColourAlpha(mBackgroundColourTopLeft.GetRed(), mBackgroundColourTopLeft.GetGreen(), mBackgroundColourTopLeft.GetBlue(), mBackgroundColourTopLeft.GetAlpha());
		m_pRenderer->ImmediateVertex(l_containerX1, l_containerY2, l_depth);
		m_pRenderer->DisableImmediateMode();
	m_pRenderer->PopMatrix();

	// Draw the outline
	m_pRenderer->PushMatrix();
		m_pRenderer->SetLineWidth(1.0f);
		m_pRenderer->EnableImmediateMode(IM_LINES);
		m_pRenderer->ImmediateColourAlpha(mOutlineColourBottom.GetRed(), mOutlineColourBottom.GetGreen(), mOutlineColourBottom.GetBlue(), mOutlineColourBottom.GetAlpha());
		m_pRenderer->ImmediateVertex(l_outlineX1, l_outlineY1, l_depth);
		m_pRenderer->ImmediateVertex(l_outlineX2, l_outlineY1, l_depth);

		m_pRenderer->ImmediateColourAlpha(mOutlineColourRight.GetRed(), mOutlineColourRight.GetGreen(), mOutlineColourRight.GetBlue(), mOutlineColourRight.GetAlpha());
		m_pRenderer->ImmediateVertex(l_outlineX2, l_outlineY1, l_depth);
		m_pRenderer->ImmediateVertex(l_outlineX2, l_outlineY2, l_depth);

		m_pRenderer->ImmediateColourAlpha(mOutlineColourTop.GetRed(), mOutlineColourTop.GetGreen(), mOutlineColourTop.GetBlue(), mOutlineColourTop.GetAlpha());
		m_pRenderer->ImmediateVertex(l_outlineX2, l_outlineY2, l_depth);
		m_pRenderer->ImmediateVertex(l_outlineX1, l_outlineY2, l_depth);

		m_pRenderer->ImmediateColourAlpha(mOutlineColourLeft.GetRed(), mOutlineColourLeft.GetGreen(), mOutlineColourLeft.GetBlue(), mOutlineColourLeft.GetAlpha());
		m_pRenderer->ImmediateVertex(l_outlineX1, l_outlineY2, l_depth);
		m_pRenderer->ImmediateVertex(l_outlineX1, l_outlineY1, l_depth);
		m_pRenderer->DisableImmediateMode();
	m_pRenderer->PopMatrix();
}