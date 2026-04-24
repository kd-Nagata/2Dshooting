#include "Player.h"
#include "../../GameSystem/GameManager.h"

void c_Player::Init()
{
	m_pos = { 0,-200 };
}

void c_Player::Update()
{

	UpdateMatrix();
}

void c_Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(TEX.GetTexture(TextureType::Player, "Player1"), Math::Rectangle(0, 0, 128, 128));
}

void c_Player::Release()
{
}
