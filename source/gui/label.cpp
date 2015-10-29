// ******************************************************************************
//
// Filename:	label.cpp
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A simple GUI component that simple displays a text label
//
// Revision History:
//   Initial Revision - 27/09/06
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#include "label.h"

#include "../Renderer/Renderer.h"


Label::Label(Renderer* pRenderer, unsigned int GUIFont, const std::string &label, Colour colour)
  : Component(pRenderer),
    m_GUIFont(GUIFont),
	m_colour(colour)
{
	SetText(label);
	SetVerticalAlignment(eVerticalAlignment_Center);
	SetHorizontalAlignment(eHorizontalAlignment_Left);

	// Set default dimensions
	SetDimensions(0, 0, 1, 1);

	m_outline = false;
}

Label::~Label()
{
	/* Nothing */
}

void Label::SetText(const std::string &label)
{
	m_text = label;
}

const std::string& Label::GetText() const
{
	return m_text;
}

void Label::SetFontID(unsigned int lFontID)
{
	m_GUIFont = lFontID;
}

unsigned int Label::GetFontID()
{
	return m_GUIFont;
}

void Label::SetColour(Colour lColour)
{
	m_colour = lColour;
}

void Label::SetOutlineColour(Colour lColour)
{
	m_outlineColour = lColour;
}

void Label::SetOutlineFont(unsigned int OutlineGUIFont)
{
	m_OutlineGUIFont = OutlineGUIFont;
}

void Label::GetColour(float *r, float *g, float *b, float *a)
{
	*r = m_colour.GetRed();
	*g = m_colour.GetGreen();
	*b = m_colour.GetBlue();
	*a = m_colour.GetAlpha();
}

void Label::GetOutlineColour(float *r, float *g, float *b, float *a)
{
	*r = m_outlineColour.GetRed();
	*g = m_outlineColour.GetGreen();
	*b = m_outlineColour.GetBlue();
	*a = m_outlineColour.GetAlpha();
}

void Label::SetOutline(bool outline)
{
	m_outline = outline;
}

void Label::SetVerticalAlignment(EVerticalAlignment alignment)
{
	m_eVerticalAlignment = alignment;
}

EVerticalAlignment Label::GetVerticalAlignment() const
{
	return m_eVerticalAlignment;
}

void Label::SetHorizontalAlignment(EHorizontalAlignment alignment)
{
	m_eHorizontalAlignment = alignment;
}

EHorizontalAlignment Label::GetHorizontalAlignment() const
{
	return m_eHorizontalAlignment;
}

EComponentType Label::GetComponentType() const
{
	return EComponentType_Label;
}

void Label::Insert(int index, char* character)
{
	m_text.insert(index, character);
}

void Label::Erase(int start, int num)
{
	m_text.erase(start, num);
}

void Label::DrawSelf()
{
	int l_posX = 0;
	int l_posY = 0;

	m_pRenderer->SetRenderMode(RM_SOLID);

	m_pRenderer->RenderFreeTypeText(m_GUIFont, (float)l_posX, (float)l_posY, GetDepth(), m_colour, 1.0f, "%s", m_text.c_str());

	if(m_outline)
	{
		m_pRenderer->RenderFreeTypeText(m_OutlineGUIFont, (float)l_posX, (float)l_posY, GetDepth(), m_outlineColour, 1.0f, "%s", m_text.c_str());
	}

	/* DEBUG : Text bounds checking
	int l_stringWidth = m_pRenderer->GetFreeTypeTextWidth(m_GUIFont, "%s", m_text.c_str());
	int l_stringHeight = m_pRenderer->GetFreeTypeTextHeight(m_GUIFont, "%s", m_text.c_str());

	int l_outlineX1 = 0;
	int l_outlineX2 = l_stringWidth;
	int l_outlineY1 = 0;
	int l_outlineY2 = l_stringHeight;

	m_pRenderer->PushMatrix();
		m_pRenderer->SetRenderMode(RM_WIREFRAME);
		m_pRenderer->EnableImmediateMode(IM_QUADS);
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
		m_pRenderer->ImmediateVertex(l_outlineX1, l_outlineY1, (int)m_depth);
		m_pRenderer->ImmediateVertex(l_outlineX2, l_outlineY1, (int)m_depth);
		m_pRenderer->ImmediateVertex(l_outlineX2, l_outlineY2, (int)m_depth);
		m_pRenderer->ImmediateVertex(l_outlineX1, l_outlineY2, (int)m_depth);
		m_pRenderer->DisableImmediateMode();
	m_pRenderer->PopMatrix();
	*/
}