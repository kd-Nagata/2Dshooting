#pragma once
#include"../ObjectBase.h"

#include "../../../System/Input/Mouse.h"

class UIBase :public ObjectBase
{

public:

	virtual ~UIBase() = default;

	// 基本
	virtual void Update()override;
	virtual void Draw()override;

	// マウスとの当たり判定
	virtual bool Contains() { return HitRect(); }// HitRect()

	// function ==========================

	// クリックした時
	std::function<void()> onClick = nullptr;

	// カーソルと重なっている時
	std::function<void(float x, float y)> onHover = nullptr;

	// カーソルと重なっていない時
	std::function<void()> offHover = nullptr;

	//=====================================

	void SetScale(const Math::Vector2& scale) { m_scale = scale; }

	void MarkForDelete(){}
	bool IsDelete() const { return m_isDelete; }

protected:

	// 元の拡大率保存用
	Math::Vector2 m_baseScale = { 1.0f,1.0f };

	// 半径
	Math::Vector2 m_half = { 0.0f,0.0f };
	float m_radius = 0.0f;

	// アニメ用変数
	float m_animCnt = 0.0f;		// 現在のアニメフレーム数
	float m_animStep = 0.0f;	// 1Fに進める数
	float m_animMax = 0.0f;		// アニメの最大数

	bool m_animFlg = false;		// アニメするかどうか

	// 画像用
	Math::Rectangle m_rect{ 0,0,0,0 };
	Math::Color m_color{ 1,1,1,1 };

	// マウス用のフラグ
	bool m_isHover = false;		// 重なっているかどうか
	bool m_isPressed = false;	// 押しているかどうか

	// 削除するかどうかのフラグ
	bool m_isDelete = false;

	// 中心座標と半幅・半高を使った矩形判定
	bool HitRect() const
	{
		int x = MOUSE.GetPos().x;
		int y = MOUSE.GetPos().y;

		return (x >= m_pos.x - m_half.x &&
			x <= m_pos.x + m_half.x &&
			y >= m_pos.y - m_half.y &&
			y <= m_pos.y + m_half.y);
	}

	// 中心座標と半径を使った円判定
	bool HitCircle() const
	{
		int x = MOUSE.GetPos().x;
		int y = MOUSE.GetPos().y;

		float dx = x - m_pos.x;
		float dy = y - m_pos.y;
		float r = m_radius;

		return (dx * dx + dy * dy) <= (r * r);
	}
};