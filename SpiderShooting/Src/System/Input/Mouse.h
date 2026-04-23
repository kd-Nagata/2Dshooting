#pragma once

//====================================================
// マウス入力管理クラス(System寄り)
//
// ・シングルトンとしてアプリ全体で1つだけの存在
// ・毎フレームUpdate()を呼び
//	 現在/前フレのボタン状態を更新、判定関数で利用できるようにする。
// ・左/右クリックの押下/トリガー/リリース判定を提供
// ・マウスの座標取得も可
//======================================================

class c_Mouse
{

public:

	// 座標/クリックフラグの更新
	void Update();

	// マウスカーソル描画関数
	void DrawMouseCursor();

	// 現在のマウス座標を返す
	POINT GetPos()const { return m_pos; }

	// マウスカーソルの表示切替
	void SetMyCursorShowHide(bool showHide) { m_view = showHide; }

	// ボタン判定関数

	//---------- 左クリック ----------
	// 押されているか（押しっぱなし）
	bool IsLeftPressed() const { return m_nowLeftBtn; }

	// 押された瞬間か（前フレームは離されていた）
	bool IsLeftTriggerd() const { return m_nowLeftBtn && !m_prevLeftBtn; }

	// 離された瞬間か（前フレームは押されていた）
	bool IsLeftReleased() const { return !m_nowLeftBtn && m_prevLeftBtn; }


	//---------- 右クリック ----------
	bool IsRightPressed() const { return m_nowRightBtn; }
	bool IsRightTriggered() const { return m_nowRightBtn && !m_prevRightBtn; }
	bool IsRightReleased() const { return !m_nowRightBtn && m_prevRightBtn; }


	// シングルトンインスタンス取得
	static c_Mouse& GetInstance()
	{
		static c_Mouse instance;
		return instance;
	}


private:

	// マウスポインタのテクスチャをコンストラクタでLoadする(未実装)
	c_Mouse() {}


	// マウス座標
	POINT m_pos;

	// 左クリック状態
	bool m_nowLeftBtn = false;	// 現フレ
	bool m_prevLeftBtn = false;	// 前フレ

	// 右クリック状態
	bool m_nowRightBtn = false;	// 現フレ
	bool m_prevRightBtn = false;// 前フレ

	// カーソルを表示させるかどうか(ゲーム用カーソル)
	bool m_view = true;

	// マウスカーソルの画像(未実装)

};

#define MOUSE c_Mouse::GetInstance()