// ******************************************************************************
// Filename:	FileUtils.h
// Project:		Game
// Author:		Steven Ball
//
// Purpose:
//   Some general file and folder utility functions.
//
// Revision History:
//   Initial Revision - 17/03/13
//
// Copyright (c) 2005-2015, Steven Ball
// ***************	***************************************************************

#pragma once

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#if defined(__linux__) || defined(__MACH__)
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
#endif

string wchar_t2string(const wchar_t *wchar);
wchar_t *string2wchar_t(const string &str);
vector<string> listFilesInDirectory(string directoryName);
