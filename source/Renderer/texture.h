// Juice Engine by Steven Ball
// Texture - An OpenGL texture object
// Created : 08/06/06
// Edited  : 08/06/06

#pragma once

#ifdef _WIN32 || WIN32 || WIN64 || _WIN64
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>		/* OpenGL Utility Toolkit header */
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#pragma comment (lib, "opengl32")
#pragma comment (lib, "glu32")

#include <string>
using namespace std;

int LoadFileTGA(const char *filename, unsigned char **pixels, int *width, int *height, bool flipvert);
int LoadFileBMP(const char *filename, unsigned char **pixels, int *width, int *height);
//int LoadFileJPG(const char *filename, unsigned char **pixels, int *width, int *height);

enum TextureFileType
{
	TextureFileType_BMP = 0,
	TextureFileType_JPG,
	TextureFileType_TGA,
};


class Texture {
public:
	Texture();
	~Texture();

	string GetFileName() const { return m_fileName; }

	int GetWidth();
	int GetHeight();

	int GetWidthPower2();
	int GetHeightPower2();

	GLuint GetId() const;

	TextureFileType GetFileType() const;

	bool Load(string fileName, int *width, int *height, int *width_power2, int *height_power2, bool refresh);

	void GenerateEmptyTexture();

	void Bind();

private:
	string m_fileName;

	int m_width;
	int m_height;

	int m_width_power2;
	int m_height_power2;

	GLuint m_id;

	TextureFileType m_filetype;
};
