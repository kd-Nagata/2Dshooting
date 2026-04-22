#include "GameMain.h"

void GameMain::OnEnter()
{
}

void GameMain::Update()
{
}

void GameMain::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "hello", Math::Vector4(1, 1, 0, 1));
}

void GameMain::OnExit()
{
}
