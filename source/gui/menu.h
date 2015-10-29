// ******************************************************************************
//
// Filename:	menu.h
// Project:		OpenGLGUI
// Author:		Steven Ball
//
// Purpose:
//   A menu is a container of menu items.
//
// Revision History:
//   Initial Revision - 05/05/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "abstractbutton.h"
#include "menuitem.h"

class PulldownMenu;



class Menu : public AbstractButton, public MouseListener, public FocusListener
{
public:
	/* Public methods */
	Menu(Renderer* pRenderer, unsigned int GUIFont, const std::string &label, bool lShowTopLevelMenu);
	Menu(Renderer* pRenderer, unsigned int GUIFont, const std::string &label, bool lShowTopLevelMenu, const std::string &defaultTexture, const std::string &selectedTexture, const std::string &hoverTexture, const std::string &disabledTexture);

	~Menu();

	void ResetMenu();

	void AddEventListeners();
	void RemoveEventListeners();

	void SetPullDownMenuParent(PulldownMenu* pPullDownMenuParent);
	PulldownMenu* GetPullDownMenuParent();

	void Add(MenuItem* lpMenuItem, bool lScrollBarPresent = true);

	MenuItem* FindItem(const std::string &label);

	void SetAutoSizeMenuWidth(bool lAutoSize);

	void SetDimensions(int x, int y, int width, int height);
	void SetDimensions(const Dimensions& r);
	void SetWidth(int width);
	void SetHeight(int height);
	void ResetToTextWidth();

	void SetMenuItemSpacer(int spacer);
	int GetMenuItemSpacer() const;

	int GetBiggestWidth() const;

	int GetCurrentMenuheight() const;

	const std::string GetMenuTitle() const;

	void OpenMenu();
	void CloseMenu();
	bool IsMenuOpen();

	bool ChildHasFocus();

	EComponentType GetComponentType() const;

protected:
	/* Protected methods */
	void MouseEntered(const MouseEvent& lEvent);
	void MouseExited(const MouseEvent& lEvent);
	void MousePressed(const MouseEvent& lEvent);
	void MouseReleased(const MouseEvent& lEvent);
	void MouseReleasedOutside(const MouseEvent& lEvent);
	void MouseClicked(const MouseEvent& lEvent);

	void FocusLost(const FocusEvent& lEvent);
	void FocusGained(const FocusEvent& lEvent);

	virtual void OnMouseEnter();
	virtual void OnMouseExit();
	virtual void OnMousePressed();
	virtual void OnMouseReleased();
	virtual void OnMouseClicked();

	void DrawSelf();

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	bool mbShowTopLevelMenu;
	bool mbMenuOpen;

	bool mbAutosizeMenuBase;

	int mBiggestWidth;
	int mCurrentMenuheight;
	int mMenuItemSpacer;

	PulldownMenu* m_pPullDownMenuParent;
};
