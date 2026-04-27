#include "Player.h"
#include "../../GameSystem/GameManager.h"

void c_Player::Init()
{
	m_pos = { 0,-200 };
	m_scale = { 1,1 };
	m_rot = { -90.0f,0 };

	count = 0.0f;
}

void c_Player::PreUpdate()
{
	triW = GetAsyncKeyState('W') & 0x8000;
	triS = GetAsyncKeyState('S') & 0x8000;

	if (triW)
	{
		m_pow.y += 2;
		count += 6;
	}
	if (triS)
	{
		m_pow.y -= 2;
		count -= 6;
	}
	m_pow.y *= 0.9f;
	count *= 0.9f;
}

void c_Player::Update()
{

	m_move += (m_pow - m_move) * 0.05f;
	m_pos += m_pow;
	float _angle = cosf(DirectX::XMConvertToRadians(count));

	m_scale.x = _angle;

	UpdateMatrix();
}

void c_Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(TEX.GetTexture(TextureType::Player, "Player2"), Math::Rectangle(0, 0, 128, 128));

	if (triS)
	{
		
	}
}

void c_Player::Release()
{
}
