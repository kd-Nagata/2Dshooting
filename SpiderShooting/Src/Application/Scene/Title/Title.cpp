#include"Title.h"
#include "../../Core/SceneManager.h"
#include "../../GameSystem/GameManager.h"
#include "../GameMain/GameMain.h"

void TitleScene::OnEnter()
{

	UIBase* ui;

	// スタートボタン
	ui = new UIBtn({ 0,100 }, { 1,1 }, { 160,40 }, 0, &m_startTex, Math::Rectangle{ 0,0,320,80 });
	ui->onClick = [this]()
		{
			
		};
	m_ui.Add(ui, UILayer::Front);

	m_startTex.Load("Texture/UI/Button/STARTBtn2.png");
	m_tex.Load("Texture/UI/Picture/kumo.png");

	GAME.ResetGame();

	SceneBase::OnEnter();
}

void TitleScene::OnExit()
{
	m_tex.Release();
	m_startTex.Release();
	SceneBase::OnExit();
}

void TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		//mp_manager->RequestChange(std::make_unique<GameMain()>);
	}

	GAME.Update();

	Math::Matrix t = Math::Matrix::CreateTranslation(0, 0, 0);
	Math::Matrix s = Math::Matrix::CreateScale(1, 1, 1);
	mat = s * t;

	m_ui.Update();
}

void TitleScene::Draw()
{
	
	m_ui.Draw();

	/*SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawTex(TEX.GetTexture(TextureType::Player, "Player1"), Math::Rectangle(0,0,128,128));*/

	PLAYER.Draw();

	//SHADER.m_spriteShader.SetMatrix(mat);
	//SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle{0, 0, 379,400 });
	
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawString(0, 0, "hello", Math::Vector4(1, 1, 0, 1));
}

void TitleScene::ImGuiUpdate()
{
}
