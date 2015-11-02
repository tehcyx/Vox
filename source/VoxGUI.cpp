#include "VoxGame.h"

void VoxGame::CreateGUI()
{
	m_pMainWindow = new GUIWindow(m_pRenderer, m_defaultFont, "Main");
	m_pMainWindow->AllowMoving(true);
	m_pMainWindow->AllowClosing(false);
	m_pMainWindow->AllowMinimizing(true);
	m_pMainWindow->AllowScrolling(true);
	m_pMainWindow->SetRenderTitleBar(true);
	m_pMainWindow->SetRenderWindowBackground(true);
	m_pMainWindow->SetOutlineRender(true);
	m_pMainWindow->SetDimensions(15, 35, 320, 140);
	m_pMainWindow->SetApplicationDimensions(m_windowWidth, m_windowHeight);

	m_pWireframeCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "Wireframe");
	m_pWireframeCheckBox->SetDimensions(10, 10, 14, 14);
	m_pShadowsCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "Shadows");
	m_pShadowsCheckBox->SetDimensions(10, 28, 14, 14);
	m_pShadowsCheckBox->SetToggled(true);
	m_pMSAACheckBox = new CheckBox(m_pRenderer, m_defaultFont, "Anti-Aliasing");
	m_pMSAACheckBox->SetDimensions(10, 46, 14, 14);
	m_pMSAACheckBox->SetToggled(true);
	m_pDynamicLightingCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "Lighting");
	m_pDynamicLightingCheckBox->SetDimensions(10, 64, 14, 14);
	m_pDynamicLightingCheckBox->SetToggled(true);
	m_pSSAOCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "SSAO");
	m_pSSAOCheckBox->SetDimensions(10, 82, 14, 14);
	m_pSSAOCheckBox->SetToggled(true);
	m_pBlurCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "Blur");
	m_pBlurCheckBox->SetDimensions(10, 100, 14, 14);
	m_pBlurCheckBox->SetToggled(false);
	m_pDeferredCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "Deferred");
	m_pDeferredCheckBox->SetDimensions(10, 118, 14, 14);
	m_pDeferredCheckBox->SetToggled(true);
	m_pUpdateCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "Update");
	m_pUpdateCheckBox->SetDimensions(130, 40, 14, 14);
	m_pUpdateCheckBox->SetToggled(true);
	m_pDebugRenderCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "DebugRender");
	m_pDebugRenderCheckBox->SetDimensions(210, 10, 14, 14);
	m_pDebugRenderCheckBox->SetToggled(false);

	m_pFullscreenButton = new Button(m_pRenderer, m_defaultFont, "FullScreen");
	m_pFullscreenButton->SetDimensions(110, 10, 80, 20);
	m_pFullscreenButton->SetCallBackFunction(_ToggleFullScreenPressed);
	m_pFullscreenButton->SetCallBackData(this);

	m_pPlayAnimationButton = new Button(m_pRenderer, m_defaultFont, "Play Animation");
	m_pPlayAnimationButton->SetDimensions(230, 45, 85, 20);
	m_pPlayAnimationButton->SetCallBackFunction(_PlayAnimationPressed);
	m_pPlayAnimationButton->SetCallBackData(this);

	m_pAnimationsPulldown = new PulldownMenu(m_pRenderer, m_defaultFont, "Animation");
	m_pAnimationsPulldown->SetDimensions(150, 70, 140, 14);
	m_pAnimationsPulldown->SetMaxNumItemsDisplayed(5);
	m_pAnimationsPulldown->SetDepth(2.0f);
	m_pAnimationsPulldown->SetRenderHeader(true);
	m_pAnimationsPulldown->SetMenuItemChangedCallBackFunction(_AnimationPullDownChanged);
	m_pAnimationsPulldown->SetMenuItemChangedCallBackData(this);

	m_pWeaponsPulldown = new PulldownMenu(m_pRenderer, m_defaultFont, "Weapons");
	m_pWeaponsPulldown->SetDimensions(150, 90, 140, 14);
	m_pWeaponsPulldown->SetMaxNumItemsDisplayed(5);
	m_pWeaponsPulldown->SetDepth(3.0f);
	m_pWeaponsPulldown->SetRenderHeader(true);
	m_pWeaponsPulldown->SetMenuItemChangedCallBackFunction(_WeaponPullDownChanged);
	m_pWeaponsPulldown->SetMenuItemChangedCallBackData(this);
	m_pWeaponsPulldown->AddPulldownItem("None");
	m_pWeaponsPulldown->AddPulldownItem("Sword");
	m_pWeaponsPulldown->AddPulldownItem("Sword & Shield");
	m_pWeaponsPulldown->AddPulldownItem("2 Handed Sword");
	m_pWeaponsPulldown->AddPulldownItem("Hammer");
	m_pWeaponsPulldown->AddPulldownItem("Bow");
	m_pWeaponsPulldown->AddPulldownItem("Staff");
	m_pWeaponsPulldown->AddPulldownItem("DruidStaff");
	m_pWeaponsPulldown->AddPulldownItem("PriestStaff");
	m_pWeaponsPulldown->AddPulldownItem("NecroStaff");
	m_pWeaponsPulldown->AddPulldownItem("Torch");
	m_pWeaponsPulldown->AddPulldownItem("Magic");

	m_pCharacterPulldown = new PulldownMenu(m_pRenderer, m_defaultFont, "Character");
	m_pCharacterPulldown->SetDimensions(150, 110, 140, 14);
	m_pCharacterPulldown->SetMaxNumItemsDisplayed(5);
	m_pCharacterPulldown->SetDepth(4.0f);
	m_pCharacterPulldown->SetRenderHeader(true);
	m_pCharacterPulldown->SetMenuItemChangedCallBackFunction(_CharacterPullDownChanged);
	m_pCharacterPulldown->SetMenuItemChangedCallBackData(this);
	m_pCharacterPulldown->AddPulldownItem("Steve");
	m_pCharacterPulldown->AddPulldownItem("Mage");
	m_pCharacterPulldown->AddPulldownItem("Warrior");
	m_pCharacterPulldown->AddPulldownItem("Necromancer");
	m_pCharacterPulldown->AddPulldownItem("Priest");
	m_pCharacterPulldown->AddPulldownItem("Paladin");
	m_pCharacterPulldown->AddPulldownItem("Druid");
	m_pCharacterPulldown->AddPulldownItem("TreeElemental");

	m_pMainWindow->AddComponent(m_pShadowsCheckBox);
	m_pMainWindow->AddComponent(m_pSSAOCheckBox);
	m_pMainWindow->AddComponent(m_pBlurCheckBox);
	m_pMainWindow->AddComponent(m_pDynamicLightingCheckBox);
	m_pMainWindow->AddComponent(m_pWireframeCheckBox);
	m_pMainWindow->AddComponent(m_pMSAACheckBox);
	m_pMainWindow->AddComponent(m_pDeferredCheckBox);
	m_pMainWindow->AddComponent(m_pUpdateCheckBox);
	m_pMainWindow->AddComponent(m_pDebugRenderCheckBox);
	m_pMainWindow->AddComponent(m_pFullscreenButton);
	m_pMainWindow->AddComponent(m_pPlayAnimationButton);
	m_pMainWindow->AddComponent(m_pAnimationsPulldown);
	m_pMainWindow->AddComponent(m_pWeaponsPulldown);
	m_pMainWindow->AddComponent(m_pCharacterPulldown);

	m_pGUI->AddWindow(m_pMainWindow);

	UpdateAnimationsPulldown();
}

void VoxGame::SkinGUI()
{
	m_pShadowsCheckBox->SetDefaultIcon(m_pFrontendManager->GetCheckboxIcon());
	m_pShadowsCheckBox->SetHoverIcon(m_pFrontendManager->GetCheckboxIconHover());
	m_pShadowsCheckBox->SetSelectedIcon(m_pFrontendManager->GetCheckboxIconPressed());
	m_pShadowsCheckBox->SetDisabledIcon(m_pFrontendManager->GetCheckboxIconDisabled());
	m_pShadowsCheckBox->SetToggledIcon(m_pFrontendManager->GetCheckboxIconToggled());
	m_pShadowsCheckBox->SetToggledHoverIcon(m_pFrontendManager->GetCheckboxIconToggledHover());
	m_pShadowsCheckBox->SetToggledSelectedIcon(m_pFrontendManager->GetCheckboxIconToggledPressed());
	m_pShadowsCheckBox->SetToggledDisabledIcon(m_pFrontendManager->GetCheckboxIconToggledDisabled());
	m_pMSAACheckBox->SetDefaultIcon(m_pFrontendManager->GetCheckboxIcon());
	m_pMSAACheckBox->SetHoverIcon(m_pFrontendManager->GetCheckboxIconHover());
	m_pMSAACheckBox->SetSelectedIcon(m_pFrontendManager->GetCheckboxIconPressed());
	m_pMSAACheckBox->SetDisabledIcon(m_pFrontendManager->GetCheckboxIconDisabled());
	m_pMSAACheckBox->SetToggledIcon(m_pFrontendManager->GetCheckboxIconToggled());
	m_pMSAACheckBox->SetToggledHoverIcon(m_pFrontendManager->GetCheckboxIconToggledHover());
	m_pMSAACheckBox->SetToggledSelectedIcon(m_pFrontendManager->GetCheckboxIconToggledPressed());
	m_pMSAACheckBox->SetToggledDisabledIcon(m_pFrontendManager->GetCheckboxIconToggledDisabled());
	m_pDynamicLightingCheckBox->SetDefaultIcon(m_pFrontendManager->GetCheckboxIcon());
	m_pDynamicLightingCheckBox->SetHoverIcon(m_pFrontendManager->GetCheckboxIconHover());
	m_pDynamicLightingCheckBox->SetSelectedIcon(m_pFrontendManager->GetCheckboxIconPressed());
	m_pDynamicLightingCheckBox->SetDisabledIcon(m_pFrontendManager->GetCheckboxIconDisabled());
	m_pDynamicLightingCheckBox->SetToggledIcon(m_pFrontendManager->GetCheckboxIconToggled());
	m_pDynamicLightingCheckBox->SetToggledHoverIcon(m_pFrontendManager->GetCheckboxIconToggledHover());
	m_pDynamicLightingCheckBox->SetToggledSelectedIcon(m_pFrontendManager->GetCheckboxIconToggledPressed());
	m_pDynamicLightingCheckBox->SetToggledDisabledIcon(m_pFrontendManager->GetCheckboxIconToggledDisabled());
	m_pSSAOCheckBox->SetDefaultIcon(m_pFrontendManager->GetCheckboxIcon());
	m_pSSAOCheckBox->SetHoverIcon(m_pFrontendManager->GetCheckboxIconHover());
	m_pSSAOCheckBox->SetSelectedIcon(m_pFrontendManager->GetCheckboxIconPressed());
	m_pSSAOCheckBox->SetDisabledIcon(m_pFrontendManager->GetCheckboxIconDisabled());
	m_pSSAOCheckBox->SetToggledIcon(m_pFrontendManager->GetCheckboxIconToggled());
	m_pSSAOCheckBox->SetToggledHoverIcon(m_pFrontendManager->GetCheckboxIconToggledHover());
	m_pSSAOCheckBox->SetToggledSelectedIcon(m_pFrontendManager->GetCheckboxIconToggledPressed());
	m_pSSAOCheckBox->SetToggledDisabledIcon(m_pFrontendManager->GetCheckboxIconToggledDisabled());
	m_pBlurCheckBox->SetDefaultIcon(m_pFrontendManager->GetCheckboxIcon());
	m_pBlurCheckBox->SetHoverIcon(m_pFrontendManager->GetCheckboxIconHover());
	m_pBlurCheckBox->SetSelectedIcon(m_pFrontendManager->GetCheckboxIconPressed());
	m_pBlurCheckBox->SetDisabledIcon(m_pFrontendManager->GetCheckboxIconDisabled());
	m_pBlurCheckBox->SetToggledIcon(m_pFrontendManager->GetCheckboxIconToggled());
	m_pBlurCheckBox->SetToggledHoverIcon(m_pFrontendManager->GetCheckboxIconToggledHover());
	m_pBlurCheckBox->SetToggledSelectedIcon(m_pFrontendManager->GetCheckboxIconToggledPressed());
	m_pBlurCheckBox->SetToggledDisabledIcon(m_pFrontendManager->GetCheckboxIconToggledDisabled());
	m_pDeferredCheckBox->SetDefaultIcon(m_pFrontendManager->GetCheckboxIcon());
	m_pDeferredCheckBox->SetHoverIcon(m_pFrontendManager->GetCheckboxIconHover());
	m_pDeferredCheckBox->SetSelectedIcon(m_pFrontendManager->GetCheckboxIconPressed());
	m_pDeferredCheckBox->SetDisabledIcon(m_pFrontendManager->GetCheckboxIconDisabled());
	m_pDeferredCheckBox->SetToggledIcon(m_pFrontendManager->GetCheckboxIconToggled());
	m_pDeferredCheckBox->SetToggledHoverIcon(m_pFrontendManager->GetCheckboxIconToggledHover());
	m_pDeferredCheckBox->SetToggledSelectedIcon(m_pFrontendManager->GetCheckboxIconToggledPressed());
	m_pDeferredCheckBox->SetToggledDisabledIcon(m_pFrontendManager->GetCheckboxIconToggledDisabled());
	m_pWireframeCheckBox->SetDefaultIcon(m_pFrontendManager->GetCheckboxIcon());
	m_pWireframeCheckBox->SetHoverIcon(m_pFrontendManager->GetCheckboxIconHover());
	m_pWireframeCheckBox->SetSelectedIcon(m_pFrontendManager->GetCheckboxIconPressed());
	m_pWireframeCheckBox->SetDisabledIcon(m_pFrontendManager->GetCheckboxIconDisabled());
	m_pWireframeCheckBox->SetToggledIcon(m_pFrontendManager->GetCheckboxIconToggled());
	m_pWireframeCheckBox->SetToggledHoverIcon(m_pFrontendManager->GetCheckboxIconToggledHover());
	m_pWireframeCheckBox->SetToggledSelectedIcon(m_pFrontendManager->GetCheckboxIconToggledPressed());
	m_pWireframeCheckBox->SetToggledDisabledIcon(m_pFrontendManager->GetCheckboxIconToggledDisabled());
	m_pUpdateCheckBox->SetDefaultIcon(m_pFrontendManager->GetCheckboxIcon());
	m_pUpdateCheckBox->SetHoverIcon(m_pFrontendManager->GetCheckboxIconHover());
	m_pUpdateCheckBox->SetSelectedIcon(m_pFrontendManager->GetCheckboxIconPressed());
	m_pUpdateCheckBox->SetDisabledIcon(m_pFrontendManager->GetCheckboxIconDisabled());
	m_pUpdateCheckBox->SetToggledIcon(m_pFrontendManager->GetCheckboxIconToggled());
	m_pUpdateCheckBox->SetToggledHoverIcon(m_pFrontendManager->GetCheckboxIconToggledHover());
	m_pUpdateCheckBox->SetToggledSelectedIcon(m_pFrontendManager->GetCheckboxIconToggledPressed());
	m_pUpdateCheckBox->SetToggledDisabledIcon(m_pFrontendManager->GetCheckboxIconToggledDisabled());
	m_pDebugRenderCheckBox->SetDefaultIcon(m_pFrontendManager->GetCheckboxIcon());
	m_pDebugRenderCheckBox->SetHoverIcon(m_pFrontendManager->GetCheckboxIconHover());
	m_pDebugRenderCheckBox->SetSelectedIcon(m_pFrontendManager->GetCheckboxIconPressed());
	m_pDebugRenderCheckBox->SetDisabledIcon(m_pFrontendManager->GetCheckboxIconDisabled());
	m_pDebugRenderCheckBox->SetToggledIcon(m_pFrontendManager->GetCheckboxIconToggled());
	m_pDebugRenderCheckBox->SetToggledHoverIcon(m_pFrontendManager->GetCheckboxIconToggledHover());
	m_pDebugRenderCheckBox->SetToggledSelectedIcon(m_pFrontendManager->GetCheckboxIconToggledPressed());
	m_pDebugRenderCheckBox->SetToggledDisabledIcon(m_pFrontendManager->GetCheckboxIconToggledDisabled());
}

void VoxGame::DestroyGUI()
{
	delete m_pMainWindow;
	delete m_pShadowsCheckBox;
	delete m_pSSAOCheckBox;
	delete m_pBlurCheckBox;
	delete m_pDynamicLightingCheckBox;
	delete m_pWireframeCheckBox;
	delete m_pMSAACheckBox;
	delete m_pDeferredCheckBox;
	delete m_pUpdateCheckBox;
	delete m_pDebugRenderCheckBox;
	delete m_pFullscreenButton;
	delete m_pPlayAnimationButton;
	delete m_pAnimationsPulldown;
	delete m_pWeaponsPulldown;
	delete m_pCharacterPulldown;
}

void VoxGame::UpdateGUI(float dt)
{
	m_shadows = m_pShadowsCheckBox->GetToggled();
	m_ssao = m_pSSAOCheckBox->GetToggled();
	m_blur = m_pBlurCheckBox->GetToggled();
	m_dynamicLighting = m_pDynamicLightingCheckBox->GetToggled();
	m_modelWireframe = m_pWireframeCheckBox->GetToggled();
	m_multiSampling = m_pMSAACheckBox->GetToggled();
	m_deferredRendering = m_pDeferredCheckBox->GetToggled();
	m_animationUpdate = m_pUpdateCheckBox->GetToggled();
	m_debugRender = m_pDebugRenderCheckBox->GetToggled();

	if (m_deferredRendering)
	{
		m_pSSAOCheckBox->SetDisabled(false);
		m_pDynamicLightingCheckBox->SetDisabled(false);
		m_pBlurCheckBox->SetDisabled(false);
	}
	else
	{
		m_pSSAOCheckBox->SetDisabled(true);
		m_pDynamicLightingCheckBox->SetDisabled(true);
		m_pBlurCheckBox->SetDisabled(true);
	}

	m_pPlayer->SetWireFrameRender(m_modelWireframe);
	m_pBlockParticleManager->SetWireFrameRender(m_modelWireframe);
}

void VoxGame::UpdateAnimationsPulldown()
{
	m_pAnimationsPulldown->RemoveAllPullDownMenuItems();
	m_pAnimationsPulldown->ResetPullDownMenu();
	m_pMainWindow->RemoveComponent(m_pAnimationsPulldown);

	for (int i = 0; i < m_pPlayer->GetVoxelCharacter()->GetNumAnimations(); i++)
	{
		m_pAnimationsPulldown->AddPulldownItem(m_pPlayer->GetVoxelCharacter()->GetAnimationName(i));
	}

	m_pMainWindow->AddComponent(m_pAnimationsPulldown);
	m_pAnimationsPulldown->AddEventListeners();
}

// GUI callbacks
void VoxGame::_ToggleFullScreenPressed(void *apData)
{
	VoxGame* lpVoxGame = (VoxGame*)apData;
	lpVoxGame->ToggleFullScreenPressed();
}

void VoxGame::ToggleFullScreenPressed()
{
	m_fullscreen = !m_fullscreen;

	m_pVoxWindow->ToggleFullScreen(m_fullscreen);
	m_pBlockParticleManager->SetupGLBuffers();
}

void VoxGame::_PlayAnimationPressed(void *apData)
{
	VoxGame* lpVoxGame = (VoxGame*)apData;
	lpVoxGame->PlayAnimationPressed();
}

void VoxGame::PlayAnimationPressed()
{
	AnimationPullDownChanged();
}

void VoxGame::_AnimationPullDownChanged(void *apData)
{
	VoxGame* lpVoxGame = (VoxGame*)apData;
	lpVoxGame->AnimationPullDownChanged();
}

void VoxGame::AnimationPullDownChanged()
{
	MenuItem* pMenuItem = m_pAnimationsPulldown->GetSelectedMenuItem();
	if (pMenuItem != NULL)
	{
		m_pPlayer->GetVoxelCharacter()->PlayAnimation(AnimationSections_FullBody, false, AnimationSections_FullBody, pMenuItem->GetLabel().GetText().c_str());
	}
}

void VoxGame::_WeaponPullDownChanged(void *apData)
{
	VoxGame* lpVoxGame = (VoxGame*)apData;
	lpVoxGame->WeaponPullDownChanged();
}

void VoxGame::WeaponPullDownChanged()
{
	m_pPlayer->UnloadWeapon(true);
	m_pPlayer->UnloadWeapon(false);
	m_pPlayer->GetVoxelCharacter()->SetQubicleMatrixRender("Right_Hand", true);
	m_pPlayer->GetVoxelCharacter()->SetQubicleMatrixRender("Left_Hand", true);

	MenuItem* pMenuItem = m_pWeaponsPulldown->GetSelectedMenuItem();
	if (pMenuItem != NULL)
	{
		if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "NONE") == 0)
		{
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Sword") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/Sword/Sword.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Sword & Shield") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/Sword/Sword.weapon");
			m_pPlayer->GetVoxelCharacter()->LoadLeftWeapon("media/gamedata/weapons/Shield/Shield.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "2 Handed Sword") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/2HandedSword/2HandedSword.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Hammer") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/Hammer/Hammer.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Bow") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadLeftWeapon("media/gamedata/weapons/Bow/Bow.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Staff") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/Staff/Staff.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "DruidStaff") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/DruidStaff/DruidStaff.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "PriestStaff") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/PriestStaff/PriestStaff.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "NecroStaff") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/NecroStaff/NecroStaff.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Torch") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/Torch/Torch.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Magic") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/FireballHands/FireballHandsRight.weapon");
			m_pPlayer->GetVoxelCharacter()->LoadLeftWeapon("media/gamedata/weapons/FireballHands/FireballHandsLeft.weapon");
			m_pPlayer->GetVoxelCharacter()->SetQubicleMatrixRender("Right_Hand", false);
			m_pPlayer->GetVoxelCharacter()->SetQubicleMatrixRender("Left_Hand", false);
		}
	}
}

void VoxGame::_CharacterPullDownChanged(void *apData)
{
	VoxGame* lpVoxGame = (VoxGame*)apData;
	lpVoxGame->CharacterPullDownChanged();
}

void VoxGame::CharacterPullDownChanged()
{
	MenuItem* pMenuItem = m_pCharacterPulldown->GetSelectedMenuItem();
	if (pMenuItem != NULL)
	{
		m_pPlayer->UnloadWeapon(false);
		m_pPlayer->UnloadWeapon(true);

		m_pPlayer->LoadCharacter(pMenuItem->GetLabel().GetText().c_str());

		WeaponPullDownChanged();
		AnimationPullDownChanged();
	}
}