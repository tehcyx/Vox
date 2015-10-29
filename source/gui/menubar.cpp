// ******************************************************************************
//
// Filename:	menubar.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A menu bar is a container of menus.
//
// Revision History:
//   Initial Revision - 15/05/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#include "menubar.h"


MenuBar::MenuBar(Renderer* pRenderer)
  : Container(pRenderer)
{
	mBiggestHeight = 0;
	mCurrentMenuBarWidth = 0;
}

MenuBar::~MenuBar()
{

}

void MenuBar::Add(Menu* lpMenu)
{
	Container::Add(lpMenu);

	int lNewMenuWidth = lpMenu->GetDimensions().m_width - (lpMenu->GetMenuItemSpacer() * 2);
	int lNewMenuHeight = lpMenu->GetDimensions().m_height - (lpMenu->GetMenuItemSpacer() * 2);

	// Check to see if this new menu has a bigger height
	if(lNewMenuHeight > mBiggestHeight)
	{
		mBiggestHeight = lNewMenuHeight;

		SetHeight(mBiggestHeight + (lpMenu->GetMenuItemSpacer() * 2));

		// Notify all our children menu items of the NEW biggest height
		ComponentList::const_iterator iterator;

		for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
		{
			if((*iterator)->GetComponentType() == EComponentType_Menu)
			{
				(*iterator)->SetHeight(mBiggestHeight);
			}
		}
	}

	// Set the location of the new menu
	lpMenu->SetDimensions(mCurrentMenuBarWidth, 0, lNewMenuWidth, mBiggestHeight);

	// Reset the main menu to be the width of its original text length
	lpMenu->ResetToTextWidth();

	// Get this original menu width and use this as the new width marker, this means menu bars dont have massive
	// gaps for the biggest entry size.
	int lOriginalMenuWidth = lpMenu->GetDimensions().m_width - (lpMenu->GetMenuItemSpacer() * 2);

	mCurrentMenuBarWidth += lOriginalMenuWidth + (lpMenu->GetMenuItemSpacer() * 2);

	// Extend our width
	SetWidth(mCurrentMenuBarWidth);
}

void MenuBar::CloseAllMenus()
{
	ComponentList::const_iterator iterator;

	for(iterator = m_vpComponentList.begin(); iterator != m_vpComponentList.end(); ++iterator)
	{
		if((*iterator)->GetComponentType() == EComponentType_Menu)
		{
			Menu* lpMenu = (Menu *)(*iterator);

			lpMenu->CloseMenu();
		}
	}
}

EComponentType MenuBar::GetComponentType() const
{
	return EComponentType_MenuBar;
}

void MenuBar::DrawSelf()
{
	//Container::DrawSelf();
}