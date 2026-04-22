#pragma once
class ObjectBase
{

public:

	virtual ~ObjectBase() = default;

	// 基本
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// 基本の行列計算を行う関数
	void UpdateMatrix()
	{
		// 行列の合成
		Math::Matrix t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		Math::Matrix s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
		m_mat = s * t;
	}

	// ワールド座標をスクリーン座標に変換して渡す行列計算を行う関数
	void UpdateMatrix(Math::Vector2 drawPos)
	{
		// 行列の合成
		Math::Matrix t = Math::Matrix::CreateTranslation(drawPos.x, drawPos.y, 0);
		Math::Matrix s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
		m_mat = s * t;
	}

	// ゲッター/セッター
	
	// pos
	const Math::Vector2& GetPos()const { return m_pos; }
	void SetPos(const Math::Vector2& pos) { m_pos = pos; }

	// move
	const Math::Vector2& GetMove() const { return m_move; }
	void SetMove(const Math::Vector2& move) { m_move = move; }

	// scale
	const Math::Vector2& GetScale() const { return m_scale; }
	void SetScale(const Math::Vector2& scale) { m_scale = scale; }


protected:

	// 全オブジェクトが共通で持つであろう変数
	Math::Vector2 m_pos = {};
	Math::Vector2 m_move = {};
	Math::Vector2 m_scale = {};

	KdTexture* mp_tex = nullptr;
	Math::Matrix m_mat;

};