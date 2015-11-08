// ******************************************************************************
// Filename:	FileUtils.cpp
// Project:		Game
// Author:		Steven Ball
//
// Revision History:
//   Initial Revision - 17/03/13
//
// Copyright (c) 2005-2015, Steven Ball
// ******************************************************************************

#include "FileUtils.h"

#ifdef _WIN32
#include <windows.h>
#endif //_WIN32

string wchar_t2string(const wchar_t *wchar)
{
	string str = "";
	int index = 0;
	while(wchar[index] != 0)
	{
		str += (char)wchar[index];
		++index;
	}
	return str;
}

wchar_t *string2wchar_t(const string &str)
{
	wchar_t wchar[260];
	unsigned int index = 0;
	while(index < str.size())
	{
		wchar[index] = (wchar_t)str[index];
		++index;
	}
	wchar[index] = 0;
	return wchar;
}

vector<string> listFilesInDirectory(string directoryName)
{
#ifdef _WIN32
	WIN32_FIND_DATA FindFileData;
	wchar_t * FileName = string2wchar_t(directoryName);
	HANDLE hFind = FindFirstFile(FileName, &FindFileData);

	vector<string> listFileNames;
	if (GetLastError() != ERROR_FILE_NOT_FOUND)
	{
		listFileNames.push_back(wchar_t2string(FindFileData.cFileName));
	}

	while (FindNextFile(hFind, &FindFileData))
		listFileNames.push_back(wchar_t2string(FindFileData.cFileName));

	FindClose(hFind);

	return listFileNames;
#elif __linux__
	vector<string> vStrings;
	return vStrings;
#endif //_WIN32
}

bool dirExists(const std::string& dirName_in)
{
#ifdef _WIN32
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!
#endif //_WIN32

	return false;    // this is not a directory!
}