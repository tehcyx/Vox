#include "VoxGame.h"

#include <glm/detail/func_geometric.hpp>


// Rendering
void VoxGame::PreRender()
{
	// Update matrices for game objects
	m_pPlayer->CalculateWorldTransformMatrix();
}

void VoxGame::Render()
{
	if (m_pVoxWindow->GetMinimized())
	{
		// Don't call any render functions if minimized
		return;
	}

	glShader* pShader = NULL;

	// Begin rendering
	m_pRenderer->BeginScene(true, true, true);

		//glEnable(GL_COLOR_MATERIAL);
		//glEnable(GL_NORMALIZE);

		// Shadow rendering to the shadow frame buffer
		if (m_shadows)
		{
			m_pRenderer->PushMatrix();
				m_pRenderer->StartRenderingToFrameBuffer(m_shadowFrameBuffer);
				glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, 0.01f, 1000.0f);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt(m_defaultLightPosition.x, m_defaultLightPosition.y, m_defaultLightPosition.z, m_defaultLightView.x, m_defaultLightView.y, m_defaultLightView.z, 0.0f, 1.0f, 0.0f);

				m_pRenderer->PushMatrix();
					m_pRenderer->SetCullMode(CM_FRONT);

					// Render the player
					m_pPlayer->Render();

					// Render the block particles
					m_pBlockParticleManager->Render();

					m_pRenderer->SetTextureMatrix();
					m_pRenderer->SetCullMode(CM_BACK);
				m_pRenderer->PopMatrix();

				glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
				m_pRenderer->StopRenderingToFrameBuffer(m_shadowFrameBuffer);
			m_pRenderer->PopMatrix();
		}

		// SSAO frame buffer rendering start
		if (m_deferredRendering)
		{
			m_pRenderer->StartRenderingToFrameBuffer(m_SSAOFrameBuffer);
		}

		// ---------------------------------------
		// Render 3d
		// ---------------------------------------
		m_pRenderer->PushMatrix();
			// Set the default projection mode
			m_pRenderer->SetProjectionMode(PM_PERSPECTIVE, m_defaultViewport);

			// Set back culling as default
			m_pRenderer->SetCullMode(CM_BACK);

			// Set the lookat camera
			m_pGameCamera->Look();

			// Enable the lights
			m_pRenderer->PushMatrix();
				m_pRenderer->EnableLight(m_defaultLight, 0);
			m_pRenderer->PopMatrix();

			// Multisampling MSAA
			if (m_multiSampling)
			{
				m_pRenderer->EnableMultiSampling();
			}
			else
			{
				m_pRenderer->DisableMultiSampling();
			}

			// Render the lights (DEBUG)
			m_pRenderer->PushMatrix();
				m_pRenderer->SetCullMode(CM_BACK);
				m_pRenderer->SetRenderMode(RM_SOLID);
				m_pRenderer->RenderLight(m_defaultLight);
			m_pRenderer->PopMatrix();

			m_pRenderer->BeginGLSLShader(m_shadowShader);

			pShader = m_pRenderer->GetShader(m_shadowShader);
			GLuint shadowMapUniform = glGetUniformLocationARB(pShader->GetProgramObject(), "ShadowMap");
			m_pRenderer->PrepareShaderTexture(7, shadowMapUniform);
			m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_shadowFrameBuffer));
			glUniform1iARB(glGetUniformLocationARB(pShader->GetProgramObject(), "renderShadow"), m_shadows);
			glUniform1iARB(glGetUniformLocationARB(pShader->GetProgramObject(), "alwaysShadow"), false);
			
			// Render world
			RenderWorld();

			// Render the player
			m_pPlayer->Render();

			// Render the block particles
			m_pBlockParticleManager->Render();

			m_pRenderer->EndGLSLShader(m_shadowShader);

			// Debug rendering
			//m_pLightingManager->DebugRender();
		m_pRenderer->PopMatrix();

		// Render the deferred lighting pass
		if (m_dynamicLighting)
		{
			RenderDeferredLighting();
		}

		// ---------------------------------------
		// Render 2d
		// ---------------------------------------
		m_pRenderer->PushMatrix();
		m_pRenderer->PopMatrix();

		// SSAO frame buffer rendering stop
		if (m_deferredRendering)
		{
			m_pRenderer->StopRenderingToFrameBuffer(m_SSAOFrameBuffer);
		}

		// ---------------------------------------
		// Render transparency
		// ---------------------------------------
		RenderTransparency();

		// Render the SSAO texture
		if (m_deferredRendering)
		{
			RenderSSAOTexture();
		}

		// Disable multisampling for 2d gui and text
		m_pRenderer->DisableMultiSampling();

		// Render debug information and text
		RenderDebugInformation();

		// Render the GUI
		RenderGUI();

	// End rendering
	m_pRenderer->EndScene();


	// Render the window
	m_pVoxWindow->Render();
}

void VoxGame::RenderWorld()
{
	float floorY = 0.0f;
	float floorLength = 5.0f;

	m_pRenderer->SetRenderMode(RM_SHADED);
	m_pRenderer->EnableMaterial(m_defaultMaterial);
	m_pRenderer->EnableImmediateMode(IM_QUADS);
		m_pRenderer->ImmediateColourAlpha(0.227f, 1.0f, 0.419f, 1.0f);

		m_pRenderer->ImmediateTextureCoordinate(0.0f, 0.0f);
		m_pRenderer->ImmediateVertex(-floorLength, floorY, -floorLength);
		m_pRenderer->ImmediateNormal(0.0f, 1.0f, 0.0f);

		m_pRenderer->ImmediateTextureCoordinate(0.0f, 1.0f);
		m_pRenderer->ImmediateVertex(-floorLength, floorY, floorLength);
		m_pRenderer->ImmediateNormal(0.0f, 1.0f, 0.0f);

		m_pRenderer->ImmediateTextureCoordinate(1.0f, 1.0f);
		m_pRenderer->ImmediateVertex(floorLength, floorY, floorLength);
		m_pRenderer->ImmediateNormal(0.0f, 1.0f, 0.0f);

		m_pRenderer->ImmediateTextureCoordinate(1.0f, 0.0f);
		m_pRenderer->ImmediateVertex(floorLength, floorY, -floorLength);
		m_pRenderer->ImmediateNormal(0.0f, 1.0f, 0.0f);
	m_pRenderer->DisableImmediateMode();
}

void VoxGame::RenderDeferredLighting()
{
	// Render deferred lighting to light frame buffer
	m_pRenderer->PushMatrix();
		m_pRenderer->StartRenderingToFrameBuffer(m_lightingFrameBuffer);

		m_pRenderer->SetFrontFaceDirection(FrontFaceDirection_CW);
		m_pRenderer->EnableTransparency(BF_ONE, BF_ONE);
		m_pRenderer->DisableDepthTest();

		// Set the default projection mode
		m_pRenderer->SetProjectionMode(PM_PERSPECTIVE, m_defaultViewport);

		// Set the lookat camera
		m_pGameCamera->Look();

		m_pRenderer->PushMatrix();
			m_pRenderer->BeginGLSLShader(m_lightingShader);

			glShader* pLightShader = m_pRenderer->GetShader(m_lightingShader);
			unsigned NormalsID = glGetUniformLocationARB(pLightShader->GetProgramObject(), "normals");
			unsigned PositionssID = glGetUniformLocationARB(pLightShader->GetProgramObject(), "positions");

			m_pRenderer->PrepareShaderTexture(0, NormalsID);
			m_pRenderer->BindRawTextureId(m_pRenderer->GetNormalTextureFromFrameBuffer(m_SSAOFrameBuffer));

			m_pRenderer->PrepareShaderTexture(1, PositionssID);
			m_pRenderer->BindRawTextureId(m_pRenderer->GetPositionTextureFromFrameBuffer(m_SSAOFrameBuffer));

			pLightShader->setUniform1i("screenWidth", m_windowWidth);
			pLightShader->setUniform1i("screenHeight", m_windowHeight);

			for (int i = 0; i < m_pLightingManager->GetNumLights(); i++)
			{
				DynamicLight* lpLight = m_pLightingManager->GetLight(i);
				float lightRadius = lpLight->m_radius;

				vec3 cameraPos = vec3(cameraPos.x, cameraPos.y, cameraPos.z);
				float length = glm::distance(cameraPos, lpLight->m_position);
				if (length < lightRadius + 0.5f) // Small change to account for differences in circle render (with slices) and circle radius
				{
					m_pRenderer->SetCullMode(CM_BACK);
				}
				else
				{
					m_pRenderer->SetCullMode(CM_FRONT);
				}

				pLightShader->setUniform1f("radius", lightRadius);
				pLightShader->setUniform1f("diffuseScale", lpLight->m_diffuseScale);

				float r = lpLight->m_colour.GetRed();
				float g = lpLight->m_colour.GetGreen();
				float b = lpLight->m_colour.GetBlue();
				float a = lpLight->m_colour.GetAlpha();
				pLightShader->setUniform4f("diffuseLightColor", r, g, b, a);

				m_pRenderer->PushMatrix();
					m_pRenderer->SetRenderMode(RM_SOLID);
					m_pRenderer->TranslateWorldMatrix(lpLight->m_position.x, lpLight->m_position.y + 0.5f, lpLight->m_position.z);
					m_pRenderer->DrawSphere(lightRadius, 30, 30);
				m_pRenderer->PopMatrix();
			}

			m_pRenderer->EmptyTextureIndex(1);
			m_pRenderer->EmptyTextureIndex(0);

			m_pRenderer->EndGLSLShader(m_lightingShader);

		m_pRenderer->PopMatrix();

		m_pRenderer->SetFrontFaceDirection(FrontFaceDirection_CCW);
		m_pRenderer->DisableTransparency();
		m_pRenderer->SetCullMode(CM_BACK);
		m_pRenderer->EnableDepthTest(DT_LESS);

		m_pRenderer->StopRenderingToFrameBuffer(m_lightingFrameBuffer);

	m_pRenderer->PopMatrix();
}

void VoxGame::RenderTransparency()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_PERSPECTIVE, m_defaultViewport);
		m_pRenderer->SetCullMode(CM_BACK);

		// Set the lookat camera
		m_pGameCamera->Look();

		if (m_deferredRendering)
		{
			m_pRenderer->StartRenderingToFrameBuffer(m_transparencyFrameBuffer);
		}

		// Render the player's face
		m_pPlayer->RenderFace();

		// Render the player's weapon trails
		m_pPlayer->RenderWeaponTrails();

		if (m_deferredRendering)
		{
			m_pRenderer->StopRenderingToFrameBuffer(m_transparencyFrameBuffer);
		}
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderSSAOTexture()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);

		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		// SSAO shader
		m_pRenderer->BeginGLSLShader(m_SSAOShader);
		glShader* pShader = m_pRenderer->GetShader(m_SSAOShader);

		unsigned int textureId0 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_DepthTexture");
		m_pRenderer->PrepareShaderTexture(0, textureId0);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_SSAOFrameBuffer));

		unsigned int textureId1 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_RenderedTexture");
		m_pRenderer->PrepareShaderTexture(1, textureId1);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_SSAOFrameBuffer));

		unsigned int textureId2 = glGetUniformLocationARB(pShader->GetProgramObject(), "light");
		m_pRenderer->PrepareShaderTexture(2, textureId2);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_lightingFrameBuffer));

		unsigned int textureId3 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_TransparentTexture");
		m_pRenderer->PrepareShaderTexture(3, textureId3);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_transparencyFrameBuffer));

		unsigned int textureId4 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_TransparentDepthTexture");
		m_pRenderer->PrepareShaderTexture(4, textureId4);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_transparencyFrameBuffer));


		pShader->setUniform1i("screenWidth", m_windowWidth);
		pShader->setUniform1i("screenHeight", m_windowHeight);
		pShader->setUniform1f("nearZ", 0.01f);
		pShader->setUniform1f("farZ", 1000.0f);

		pShader->setUniform1f("samplingMultiplier", 0.5f);

		pShader->setUniform1i("lighting_enabled", m_dynamicLighting);
		pShader->setUniform1i("ssao_enabled", m_ssao);

		m_pRenderer->SetRenderMode(RM_TEXTURED);
		m_pRenderer->EnableImmediateMode(IM_QUADS);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 0.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 1.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, (float)m_windowHeight, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 1.0f);
			m_pRenderer->ImmediateVertex(0.0f, (float)m_windowHeight, 1.0f);
		m_pRenderer->DisableImmediateMode();

		m_pRenderer->EmptyTextureIndex(4);
		m_pRenderer->EmptyTextureIndex(3);
		m_pRenderer->EmptyTextureIndex(2);
		m_pRenderer->EmptyTextureIndex(1);
		m_pRenderer->EmptyTextureIndex(0);

		m_pRenderer->EndGLSLShader(m_SSAOShader);
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderGUI()
{
	m_pRenderer->EmptyTextureIndex(0);

	// Render the GUI
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);

		m_pRenderer->SetCullMode(CM_BACK);

		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		m_pGUI->Render();
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderDebugInformation()
{
	char lCameraBuff[256];
	sprintf_s(lCameraBuff, 256, "Pos(%.2f, %.2f, %.2f), Facing(%.2f, %.2f, %.2f) = %.2f, Up(%.2f, %.2f, %.2f) = %.2f, Right(%.2f, %.2f, %.2f) = %.2f, Zoom=%.2f",
		m_pGameCamera->GetPosition().x, m_pGameCamera->GetPosition().y, m_pGameCamera->GetPosition().z,
		m_pGameCamera->GetFacing().x, m_pGameCamera->GetFacing().y, m_pGameCamera->GetFacing().z, length(m_pGameCamera->GetFacing()),
		m_pGameCamera->GetUp().x, m_pGameCamera->GetUp().y, m_pGameCamera->GetUp().z, length(m_pGameCamera->GetUp()),
		m_pGameCamera->GetRight().x, m_pGameCamera->GetRight().y, m_pGameCamera->GetRight().z, length(m_pGameCamera->GetRight()),
		m_pGameCamera->GetZoomAmount());
	char lFPSBuff[128];
	sprintf_s(lFPSBuff, "FPS: %.0f  Delta: %.4f", m_fps, m_deltaTime);

	int l_nTextHeight = m_pRenderer->GetFreeTypeTextHeight(m_defaultFont, "a");

	m_pRenderer->PushMatrix();
		m_pRenderer->EmptyTextureIndex(0);

		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);
		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, 15.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lFPSBuff);

		m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, m_windowHeight - l_nTextHeight - 10.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lCameraBuff);
	m_pRenderer->PopMatrix();
}