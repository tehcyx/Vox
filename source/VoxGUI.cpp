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
	m_pMSAACheckBox = new CheckBox(m_pRenderer, m_defaultFont, "MSAA");
	m_pMSAACheckBox->SetDimensions(10, 46, 14, 14);
	m_pMSAACheckBox->SetToggled(true);
	m_pDynamicLightingCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "Lighting");
	m_pDynamicLightingCheckBox->SetDimensions(10, 64, 14, 14);
	m_pDynamicLightingCheckBox->SetToggled(true);
	m_pSSAOCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "SSAO");
	m_pSSAOCheckBox->SetDimensions(10, 82, 14, 14);
	m_pSSAOCheckBox->SetToggled(true);
	m_pDeferredCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "Deferred");
	m_pDeferredCheckBox->SetDimensions(10, 100, 14, 14);
	m_pDeferredCheckBox->SetToggled(true);

	m_pUpdateCheckBox = new CheckBox(m_pRenderer, m_defaultFont, "Update");
	m_pUpdateCheckBox->SetDimensions(130, 40, 14, 14);
	m_pUpdateCheckBox->SetToggled(true);

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
	m_pWeaponsPulldown->AddPulldownItem("Bow");
	m_pWeaponsPulldown->AddPulldownItem("Staff");
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
	m_pCharacterPulldown->AddPulldownItem("TreeElemental");

	m_pMainWindow->AddComponent(m_pShadowsCheckBox);
	m_pMainWindow->AddComponent(m_pSSAOCheckBox);
	m_pMainWindow->AddComponent(m_pDynamicLightingCheckBox);
	m_pMainWindow->AddComponent(m_pWireframeCheckBox);
	m_pMainWindow->AddComponent(m_pMSAACheckBox);
	m_pMainWindow->AddComponent(m_pDeferredCheckBox);
	m_pMainWindow->AddComponent(m_pUpdateCheckBox);
	m_pMainWindow->AddComponent(m_pFullscreenButton);
	m_pMainWindow->AddComponent(m_pPlayAnimationButton);
	m_pMainWindow->AddComponent(m_pAnimationsPulldown);
	m_pMainWindow->AddComponent(m_pWeaponsPulldown);
	m_pMainWindow->AddComponent(m_pCharacterPulldown);

	m_pGUI->AddWindow(m_pMainWindow);

	UpdateAnimationsPulldown();
}

void VoxGame::DestroyGUI()
{
	delete m_pMainWindow;
	delete m_pShadowsCheckBox;
	delete m_pSSAOCheckBox;
	delete m_pDynamicLightingCheckBox;
	delete m_pWireframeCheckBox;
	delete m_pMSAACheckBox;
	delete m_pDeferredCheckBox;
	delete m_pUpdateCheckBox;
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
	m_dynamicLighting = m_pDynamicLightingCheckBox->GetToggled();
	m_modelWireframe = m_pWireframeCheckBox->GetToggled();
	m_multiSampling = m_pMSAACheckBox->GetToggled();
	m_deferredRendering = m_pDeferredCheckBox->GetToggled();
	m_animationUpdate = m_pUpdateCheckBox->GetToggled();

	if (m_deferredRendering)
	{
		m_pSSAOCheckBox->SetDisabled(false);
		m_pDynamicLightingCheckBox->SetDisabled(false);
		m_pMSAACheckBox->SetDisabled(true);
	}
	else
	{
		m_pSSAOCheckBox->SetDisabled(true);
		m_pDynamicLightingCheckBox->SetDisabled(true);
		m_pMSAACheckBox->SetDisabled(false);
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
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Bow") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadLeftWeapon("media/gamedata/weapons/Bow/Bow.weapon");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Staff") == 0)
		{
			m_pPlayer->GetVoxelCharacter()->LoadRightWeapon("media/gamedata/weapons/Staff/Staff.weapon");
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

		if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Steve") == 0)
		{
			m_pPlayer->LoadCharacter("Steve");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Mage") == 0)
		{
			m_pPlayer->LoadCharacter("Mage");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Warrior") == 0)
		{
			m_pPlayer->LoadCharacter("Warrior");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Necromancer") == 0)
		{
			m_pPlayer->LoadCharacter("Necromancer");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Priest") == 0)
		{
			m_pPlayer->LoadCharacter("Priest");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "Paladin") == 0)
		{
			m_pPlayer->LoadCharacter("Paladin");
		}
		else if (strcmp(pMenuItem->GetLabel().GetText().c_str(), "TreeElemental") == 0)
		{
			m_pPlayer->LoadCharacter("TreeElemental");
		}

		WeaponPullDownChanged();
		AnimationPullDownChanged();
	}
}