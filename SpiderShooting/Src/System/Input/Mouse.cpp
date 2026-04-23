#include "Mouse.h"
#include "../../Application/main.h"

#include"../../Application/Constans/ScreenConstans.h"

void c_Mouse::Update()
{
	// カーソルを非表示
	ShowCursor(true);

	// 前フレームのボタン状態を保存
	// 押した瞬間や離した瞬間の判定に使う

	m_prevLeftBtn = m_nowLeftBtn;
	m_prevRightBtn = m_nowRightBtn;

	// 現在のマウス座標をスクリーン座標で取得
	GetCursorPos(&m_pos);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_pos);

	// ウィンドウのクライアント領域のサイズを取得
	RECT clientRect;
	GetClientRect(APP.m_window.GetWndHandle(), &clientRect);
	int windowWidth = clientRect.right - clientRect.left;
	int windowHeight = clientRect.bottom - clientRect.top;

	// 論理座標系(階層解像度)を設定(例:1280×720)
	const int logicalWidht = SCREEN_WIDTH;
	const int logicalHeight = SCREEN_HEIGHT;

	// ウィンドウサイズに対するスケールを計算
	float scaleX = static_cast<float>(logicalWidht) / windowWidth;
	float scaleY = static_cast<float>(logicalHeight) / windowHeight;

	// 論理座標系に変換 (ウィンドウ中心を(0,0)に変換)
	m_pos.x = static_cast<int>((m_pos.x - windowWidth / 2) * scaleX);
	m_pos.y = static_cast<int>((windowHeight / 2 - m_pos.y) * scaleY);

	// 左ボタンの押下状態を取得
	m_nowLeftBtn = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;

	// 右ボタンの押下状態を取得
	m_nowRightBtn = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
}

void c_Mouse::DrawMouseCursor()
{
	//=== カーソル非表示なら表示しない =======================

	if (!m_view)return;

	//=== 描画を終わらせて描画する ==========================
	SHADER.m_spriteShader.End();

	Math::Matrix T = Math::Matrix::CreateTranslation(m_pos.x + 4.5f, m_pos.y - 7.5f, 0);

	Math::Rectangle rect = { 0,0,24,24 };
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		rect = { 24,0,24,24 };
	}

	SHADER.m_spriteShader.SetMatrix(T);
	//SHADER.m_spriteShader.DrawTex(&m_mouseTex, 0, 0, &rect, &Math::Color(1.0f, 1.0f, 1.0f, 1.0f));

	// ↑↑ このゲーム特有のマウスカーソルの表示(未実装)

	//=== カーソルの位置と画像の位置合わせるときに使う ====================================
	/*SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(m_pos.x, m_pos.y,2,2,&Math::Color(1,0,0,1));*/

}
