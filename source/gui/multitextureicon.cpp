// ******************************************************************************
//
// Filename:	multitextureicon.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A multi-textured icon that has a seperate graphic for each of the
//	 rectangles regions, and can scale without graphical distortion.
//
// Revision History:
//   Initial Revision - 10/08/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#include "multitextureicon.h"


MultiTextureIcon::MultiTextureIcon(Renderer* pRenderer)
  : RenderRectangle(pRenderer)
{
	CreateDrawBuffer();
}

MultiTextureIcon::~MultiTextureIcon()
{
}

void MultiTextureIcon::SetTexture(ERectanlgeRegion lRegionTexture, const std::string &fileName)
{
	//m_fileName[lRegionTexture] = fileName;
	m_pRenderer->LoadTexture(fileName.c_str(), &m_TextureWidth[lRegionTexture], &m_TextureHeight[lRegionTexture], &m_TextureWidthPower2[lRegionTexture], &m_TextureHeightPower2[lRegionTexture], &m_textureID[lRegionTexture]);
}

int MultiTextureIcon::GetTextureWidth(ERectanlgeRegion lRegionTexture) const
{
	return m_TextureWidth[lRegionTexture];
}

int MultiTextureIcon::GetTextureHeight(ERectanlgeRegion lRegionTexture) const
{
	return m_TextureHeight[lRegionTexture];
}

void MultiTextureIcon::CreateDrawBuffer()
{
	// Create the buffer used for drawing the image
	OGLPositionNormalVertex vertices[4] = {
		//X				Y				Z		nX		nY		nZ
		{0.0f,			0.0f,			0.0f,	0.0f,	0.0f,	1.0f },
		{1.0f,			0.0f,			0.0f,	0.0f,	0.0f,	1.0f },
		{1.0f,			1.0f,			0.0f,	0.0f,	0.0f,	1.0f },
		{0.0f,			1.0f,			0.0f,	0.0f,	0.0f,	1.0f }
	};

	OGLUVCoordinate textureCoordinates[4] = {
		//u			v
		{0.0f,		1.0f },
		{1.0f,		1.0f },
		{1.0f,		0.0f },
		{0.0f,		0.0f },
	};

	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

	m_pRenderer->CreateStaticBuffer(VT_POSITION_NORMAL_UV, -1, -1, 4, 4, 6, &vertices, &textureCoordinates, indices, &mTextureDrawBuffer);
}

EComponentType MultiTextureIcon::GetComponentType() const
{
	return EComponentType_MultiTextureIcon;
}

void MultiTextureIcon::DrawSelf()
{
	int l_posX = 0;
	int l_posY = 0;

	int l_TotalWidth = m_dimensions.m_width;
	int l_TotalHeight = m_dimensions.m_height;


	// TODO : Need to fix when non-power-of-2 sized textures are used, this will cause an height offset bug and also alpha will be messed up...
	// See the normal Icon class for an example of how to fix this. :)


	// Top left
	int lTopLeftWidth = m_TextureWidth[ERectanlgeRegion_TopLeft];
	int lTopLeftHeight = m_TextureHeight[ERectanlgeRegion_TopLeft];
	int lTopLeftX = l_posX;
	int lTopLeftY = l_posY + l_TotalHeight - lTopLeftHeight;

	m_pRenderer->PushMatrix();
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->TranslateWorldMatrix((float)lTopLeftX, (float)lTopLeftY, GetDepth());
		m_pRenderer->ScaleWorldMatrix((float)lTopLeftWidth, (float)lTopLeftHeight, 1.0f);
		m_pRenderer->BindTexture(m_textureID[ERectanlgeRegion_TopLeft]);
		m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);
		//m_pRenderer->RenderFromArray(VT_POSITION_NORMAL_UV, -1, 4, 6, &vertices, indices);
		m_pRenderer->RenderStaticBuffer(mTextureDrawBuffer);
		m_pRenderer->DisableTransparency();
		m_pRenderer->DisableTexture();
	m_pRenderer->PopMatrix();

	// Top right
	int lTopRightWidth = m_TextureWidth[ERectanlgeRegion_TopRight];
	int lTopRightHeight = m_TextureHeight[ERectanlgeRegion_TopRight];
	int lTopRightX = l_posX + l_TotalWidth - lTopRightWidth;
	int lTopRightY = l_posY + l_TotalHeight - lTopRightHeight;

	m_pRenderer->PushMatrix();
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->TranslateWorldMatrix((float)lTopRightX, (float)lTopRightY, GetDepth());
		m_pRenderer->ScaleWorldMatrix((float)lTopRightWidth, (float)lTopRightHeight, 1.0f);
		m_pRenderer->BindTexture(m_textureID[ERectanlgeRegion_TopRight]);
		m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);
		//m_pRenderer->RenderFromArray(VT_POSITION_NORMAL_UV, -1, 4, 6, &vertices, indices);
		m_pRenderer->RenderStaticBuffer(mTextureDrawBuffer);
		m_pRenderer->DisableTransparency();
		m_pRenderer->DisableTexture();
	m_pRenderer->PopMatrix();

	// Top center
	int lTopCenterWidth = l_TotalWidth - lTopLeftWidth - lTopRightWidth;
	int lTopCenterHeight = m_TextureHeight[ERectanlgeRegion_TopCenter];
	int lTopCenterX = l_posX + lTopLeftWidth;
	int lTopCenterY = l_posY + l_TotalHeight - lTopCenterHeight;

	m_pRenderer->PushMatrix();
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->TranslateWorldMatrix((float)lTopCenterX, (float)lTopCenterY, GetDepth());
		m_pRenderer->ScaleWorldMatrix((float)lTopCenterWidth, (float)lTopCenterHeight, 1.0f);
		m_pRenderer->BindTexture(m_textureID[ERectanlgeRegion_TopCenter]);
		m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);
		//m_pRenderer->RenderFromArray(VT_POSITION_NORMAL_UV, -1, 4, 6, &vertices, indices);
		m_pRenderer->RenderStaticBuffer(mTextureDrawBuffer);
		m_pRenderer->DisableTransparency();
		m_pRenderer->DisableTexture();
	m_pRenderer->PopMatrix();

	// Bottom left
	int lBottomLeftWidth = m_TextureWidth[ERectanlgeRegion_BottomLeft];
	int lBottomLeftHeight = m_TextureHeight[ERectanlgeRegion_BottomLeft];
	int lBottomLeftX = l_posX;
	int lBottomLeftY = l_posY;

	m_pRenderer->PushMatrix();
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->TranslateWorldMatrix((float)lBottomLeftX, (float)lBottomLeftY, GetDepth());
		m_pRenderer->ScaleWorldMatrix((float)lBottomLeftWidth, (float)lBottomLeftHeight, 1.0f);
		m_pRenderer->BindTexture(m_textureID[ERectanlgeRegion_BottomLeft]);
		m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);
		//m_pRenderer->RenderFromArray(VT_POSITION_NORMAL_UV, -1, 4, 6, &vertices, indices);
		m_pRenderer->RenderStaticBuffer(mTextureDrawBuffer);
		m_pRenderer->DisableTransparency();
		m_pRenderer->DisableTexture();
	m_pRenderer->PopMatrix();

	// Bottom right
	int lBottomRightWidth = m_TextureWidth[ERectanlgeRegion_BottomRight];
	int lBottomRightHeight = m_TextureHeight[ERectanlgeRegion_BottomRight];
	int lBottomRightX = l_posX + l_TotalWidth - lBottomRightWidth;
	int lBottomRightY = l_posY;

	m_pRenderer->PushMatrix();
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->TranslateWorldMatrix((float)lBottomRightX, (float)lBottomRightY, GetDepth());
		m_pRenderer->ScaleWorldMatrix((float)lBottomRightWidth, (float)lBottomRightHeight, 1.0f);
		m_pRenderer->BindTexture(m_textureID[ERectanlgeRegion_BottomRight]);
		m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);
		//m_pRenderer->RenderFromArray(VT_POSITION_NORMAL_UV, -1, 4, 6, &vertices, indices);
		m_pRenderer->RenderStaticBuffer(mTextureDrawBuffer);
		m_pRenderer->DisableTransparency();
		m_pRenderer->DisableTexture();
	m_pRenderer->PopMatrix();

	// Bottom center
	int lBottomCenterWidth = l_TotalWidth - lBottomLeftWidth - lBottomRightWidth;
	int lBottomCenterHeight = m_TextureHeight[ERectanlgeRegion_BottomCenter];
	int lBottomCenterX = l_posX + lBottomLeftWidth;
	int lBottomCenterY = l_posY;

	m_pRenderer->PushMatrix();
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->TranslateWorldMatrix((float)lBottomCenterX, (float)lBottomCenterY, GetDepth());
		m_pRenderer->ScaleWorldMatrix((float)lBottomCenterWidth, (float)lBottomCenterHeight, 1.0f);
		m_pRenderer->BindTexture(m_textureID[ERectanlgeRegion_BottomCenter]);
		m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);
		//m_pRenderer->RenderFromArray(VT_POSITION_NORMAL_UV, -1, 4, 6, &vertices, indices);
		m_pRenderer->RenderStaticBuffer(mTextureDrawBuffer);
		m_pRenderer->DisableTransparency();
		m_pRenderer->DisableTexture();
	m_pRenderer->PopMatrix();

	// Middle left
	int lMiddleLeftWidth = m_TextureWidth[ERectanlgeRegion_MiddleLeft];
	int lMiddleLeftHeight = l_TotalHeight - lTopLeftHeight - lBottomLeftHeight;
	int lMiddleLeftX = l_posX;
	int lMiddleLeftY = l_posY + lBottomLeftHeight;

	m_pRenderer->PushMatrix();
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->TranslateWorldMatrix((float)lMiddleLeftX, (float)lMiddleLeftY, GetDepth());
		m_pRenderer->ScaleWorldMatrix((float)lMiddleLeftWidth, (float)lMiddleLeftHeight, 1.0f);
		m_pRenderer->BindTexture(m_textureID[ERectanlgeRegion_MiddleLeft]);
		m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);
		//m_pRenderer->RenderFromArray(VT_POSITION_NORMAL_UV, -1, 4, 6, &vertices, indices);
		m_pRenderer->RenderStaticBuffer(mTextureDrawBuffer);
		m_pRenderer->DisableTransparency();
		m_pRenderer->DisableTexture();
	m_pRenderer->PopMatrix();

	// Middle right
	int lMiddleRightWidth = m_TextureWidth[ERectanlgeRegion_MiddleRight];
	int lMiddleRightHeight = l_TotalHeight - lTopRightHeight - lBottomRightHeight;
	int lMiddleRightX = l_posX + l_TotalWidth - lMiddleRightWidth;
	int lMiddleRightY = l_posY + lBottomLeftHeight;

	m_pRenderer->PushMatrix();
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->TranslateWorldMatrix((float)lMiddleRightX, (float)lMiddleRightY, GetDepth());
		m_pRenderer->ScaleWorldMatrix((float)lMiddleRightWidth, (float)lMiddleRightHeight, 1.0f);
		m_pRenderer->BindTexture(m_textureID[ERectanlgeRegion_MiddleRight]);
		m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);
		//m_pRenderer->RenderFromArray(VT_POSITION_NORMAL_UV, -1, 4, 6, &vertices, indices);
		m_pRenderer->RenderStaticBuffer(mTextureDrawBuffer);
		m_pRenderer->DisableTransparency();
		m_pRenderer->DisableTexture();
	m_pRenderer->PopMatrix();

	// Middle center
	int lMiddleCenterWidth = l_TotalWidth - lMiddleLeftWidth - lMiddleRightWidth;
	int lMiddleCenterHeight = l_TotalHeight - lTopCenterHeight - lBottomCenterHeight;
	int lMiddleCenterX = l_posX + lMiddleLeftWidth;
	int lMiddleCenterY = l_posY + lBottomLeftHeight;

	m_pRenderer->PushMatrix();
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->TranslateWorldMatrix((float)lMiddleCenterX, (float)lMiddleCenterY, GetDepth());
		m_pRenderer->ScaleWorldMatrix((float)lMiddleCenterWidth, (float)lMiddleCenterHeight, 1.0f);
		m_pRenderer->BindTexture(m_textureID[ERectanlgeRegion_MiddleCenter]);
		m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);
		//m_pRenderer->RenderFromArray(VT_POSITION_NORMAL_UV, -1, 4, 6, &vertices, indices);
		m_pRenderer->RenderStaticBuffer(mTextureDrawBuffer);
		m_pRenderer->DisableTransparency();
		m_pRenderer->DisableTexture();
	m_pRenderer->PopMatrix();
}