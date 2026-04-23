#pragma once

#include"UIBase.h"

class UIBtn : public UIBase
{
public:

	//=== アニメーションなしコンストラクタ ========================

	UIBtn(Math::Vector2 pos,
		Math::Vector2 scale,
		Math::Vector2 half,
		float radius,
		KdTexture* tex,
		Math::Rectangle rect,
		Math::Color color = Math::Color(1, 1, 1, 1))
	{
		m_pos = pos;
		m_scale = scale;
		m_baseScale = scale;
		m_half.x = half.x * fabs(scale.x);
		m_half.y = half.y * fabs(scale.y);
		m_radius = radius;
		mp_tex = tex;
		m_rect = rect;
		m_color = color;
	}

	//=== アニメーションありコンストラクタ ========================

	UIBtn(Math::Vector2 pos,
		Math::Vector2 scale,
		Math::Vector2 half,
		float radius,
		KdTexture* tex,
		float animStep,
		float animMax,
		Math::Rectangle rect,
		Math::Color color = Math::Color(1, 1, 1, 1))
	{
		m_pos = pos;
		m_scale = scale;
		m_baseScale = scale;
		m_half.x = half.x * fabs(scale.x);
		m_half.y = half.y * fabs(scale.y);
		m_radius = radius;
		mp_tex = tex;
		m_animFlg = true;
		m_animStep = animStep;
		m_animMax = animMax;
		m_rect = rect;
		m_color = color;
	}

	//=== 更新処理 =========================

	void Update()override;

private:

	// スケールをいじる最大数値
	const float kDiff = 0.04f;

	// スケールをいじる速度
	const float kSpeed = 0.01f;

};