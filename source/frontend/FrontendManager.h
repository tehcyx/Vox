// ******************************************************************************
//
// Filename:	FrontendManager.h
// Project:		Game
// Author:		Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 01/11/15
//
// Copyright (c) 2005-2015, Steven Ball
//
// ******************************************************************************

#pragma once

#include "../Renderer/Renderer.h"
#include "../gui/icon.h"


class FrontendManager
{
public:
	/* Public methods */
	FrontendManager(Renderer* pRenderer);
	~FrontendManager();

	void LoadCommonGraphics(string themeName);

	// Checkbox
	Icon* GetCheckboxIcon() { return m_pCheckboxIcon; };
	Icon* GetCheckboxIconHover() { return m_pCheckboxIconHover; };
	Icon* GetCheckboxIconPressed() { return m_pCheckboxIconPressed; };
	Icon* GetCheckboxIconDisabled() { return m_pCheckboxIconDisabled; };
	Icon* GetCheckboxIconToggled() { return m_pCheckboxIconToggled; };
	Icon* GetCheckboxIconToggledHover() { return m_pCheckboxIconToggledHover; };
	Icon* GetCheckboxIconToggledPressed() { return m_pCheckboxIconToggledPressed; };
	Icon* GetCheckboxIconToggledDisabled() { return m_pCheckboxIconToggledDisabled; };

	// Updating
	void Update(float dt);
	
	// Rendering
	void Render();

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	Renderer* m_pRenderer;

	// Checkbox
	Icon* m_pCheckboxIcon;
	Icon* m_pCheckboxIconHover;
	Icon* m_pCheckboxIconPressed;
	Icon* m_pCheckboxIconDisabled;
	Icon* m_pCheckboxIconToggled;
	Icon* m_pCheckboxIconToggledHover;
	Icon* m_pCheckboxIconToggledPressed;
	Icon* m_pCheckboxIconToggledDisabled;
};
