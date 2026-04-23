#include "UIBtn.h"

//=== 更新関数(Base にボタンらしい動きを追加) ====================================================================
void UIBtn::Update()
{
	//=== アニメーション・フラグ更新 ============================

	UIBase::Update();

	//=== 押下中は色を変える ===================================

	m_color = m_isPressed ?
		Math::Color(0.9f, 0.9f, 0.9f, 1.0f) :
		Math::Color(1.0f, 1.0f, 1.0f, 1.0f);

	//=== ボタンらしく大きさを変える ============================

	if (m_isPressed)
	{
		// 押されていたら元の拡大率から
		// 変化する最大値になるまで小さくする
		if (m_scale.x > m_baseScale.x - kDiff)
		{
			m_scale.x -= kSpeed;
			m_scale.y -= kSpeed;
		}
	}
	else if (m_isHover)
	{
		// ホバー中は元の拡大率から
		// 変化する最大値になるまで大きくする
		if (m_scale.x < m_baseScale.x + kDiff)
		{
			m_scale.x += kSpeed;
			m_scale.y += kSpeed;
		}
	}
	else if (!m_isHover)
	{
		// ホバーされていなければ
		// 元の拡大率に戻っていく
		// 戻れば終わり
		if (m_scale == m_baseScale)
		{

			return;
		}

		if (m_scale.x > m_baseScale.x)
		{
			m_scale.x -= kSpeed;
			m_scale.y -= kSpeed;
		}
		else if (m_scale.x < m_baseScale.x)
		{
			m_scale.x += kSpeed;
			m_scale.y += kSpeed;
		}
	}
}
