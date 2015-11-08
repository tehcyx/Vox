// ******************************************************************************
// Filename:	main.cpp
// Project:		Vox
// Author:		Steven Ball
//
// Purpose:
//   The main entry point for the application.
// 
// Revision History:
//   Initial Revision - 27/10/15
//
// Copyright (c) 2005-2015, Steven Ball
// ******************************************************************************

#include "VoxGame.h"

int main(void)
{
	/* Create and initialize VoxGame object */
	VoxGame* m_pVoxGame = VoxGame::GetInstance();
	m_pVoxGame->Create();

	/* Loop until the user closes the window or application */
	while (!m_pVoxGame->ShouldClose())
	{
		/* Poll input events*/
		m_pVoxGame->PollEvents();

		/* Update */
		m_pVoxGame->Update();

		/* PreRender */
		m_pVoxGame->PreRender();

		/* Render */
		m_pVoxGame->Render();
	}

	/* Cleanup */
	m_pVoxGame->Destroy();

	/* Exit */
	exit(EXIT_SUCCESS);
}
