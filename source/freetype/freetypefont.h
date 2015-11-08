// ******************************************************************************
//
// Filename:	freetypefont.h
// Project:		Vox
// Author:		Steven Ball
//
// Purpose:
//   
//
// Revision History:
//   Initial Revision - 11/10/08
//
// Copyright (c) 2005-2015, Steven Ball
//
// ******************************************************************************

#pragma once

<<<<<<< HEAD
#ifdef _WIN32 || WIN32 || WIN64 || _WIN64
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>		/* OpenGL Utility Toolkit header */
#else
=======
#ifdef _WIN32
#include <windows.h>
#endif //_WIN32
>>>>>>> origin/ag/master
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <ft2build.h>
#include FT_FREETYPE_H


class FreeTypeFont {
public:
	FreeTypeFont();
	~FreeTypeFont();

	void BuildFont(const char* fontName, int size);
	void DrawString(const char *text, float scale);

	int GetTextWidth(const char *text);
	int GetCharWidth(int c);
	int GetCharHeight(int c);
	int GetAscent();
	int GetDescent();

protected:
	void MakeDisplayList(FT_Face face, unsigned char ch, GLuint list_base, GLuint * tex_base);

private:

	bool m_inited;

	FT_Library m_library;

	FT_Face m_face;

	int m_size;

	GLuint* m_textures;
	GLuint m_base;
};
