#include "UIBase.h"

void UIBase::Update()
{
	// animFlgがtrueならanimCntを進める
	if (m_animFlg)
	{
		m_animCnt += m_animStep;
		if (m_animCnt >= m_animMax)
		{
			m_animCnt = 0.0f;
		}
	}

	// Hover/Press

	m_isHover = Contains();

	if (m_isHover)
	{
		if (onHover)onHover(MOUSE.GetPos().x, MOUSE.GetPos().y);
	}
	else
	{
		if (offHover)offHover();
	}

	// 押された"瞬間"
	if (m_isHover && MOUSE.IsLeftTriggerd())m_isPressed = true;

	// 離された"瞬間"(クリック成立)
	if (m_isPressed && MOUSE.IsLeftReleased())
	{
		if (m_isHover && onClick)onClick();
		m_isPressed = false;
	}

	// Hover範囲から離れたらクリックキャンセル
	if (m_isPressed && !m_isHover && MOUSE.IsLeftPressed())m_isPressed = false;
}

void UIBase::Draw()
{
	if(m_animFlg)
	{ 
		// アニメ用切り取り範囲
		Math::Rectangle rec =
		{
			static_cast<long>((m_rect.width) * (int)m_animCnt),
			0,
			static_cast<long>(m_rect.width),
			static_cast<long>(m_rect.height)
		};

		// 行列更新
		ObjectBase::UpdateMatrix();
		SHADER.m_spriteShader.SetMatrix(m_mat);
		// 描画
		SHADER.m_spriteShader.DrawTex(mp_tex, 0, 0, &rec, &m_color);
	}
	else
	{
		// 行列更新
		ObjectBase::UpdateMatrix();
		SHADER.m_spriteShader.SetMatrix(m_mat);
		// 描画
		SHADER.m_spriteShader.DrawTex(mp_tex, 0, 0, &m_rect, &m_color);
	}
	


}
