#include"Title.h"
#include "../../Core/SceneManager.h"
#include "../GameMain/GameMain.h"

void TitleScene::OnEnter()
{
	m_tex.Load("Texture/UI/Picture/kumo.png");
	SceneBase::OnEnter();
}

void TitleScene::OnExit()
{
	m_tex.Release();
	SceneBase::OnExit();
}

void TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		//mp_manager->RequestChange(std::make_unique<GameMain()>);
	}

	Math::Matrix t = Math::Matrix::CreateTranslation(0, 0, 0);
	Math::Matrix s = Math::Matrix::CreateScale(1, 1, 1);
	mat = s * t;
}

void TitleScene::Draw()
{
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle{0, 0, 379,400 });
	
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawString(0, 0, "hello", Math::Vector4(1, 1, 0, 1));
}

void TitleScene::ImGuiUpdate()
{
}
