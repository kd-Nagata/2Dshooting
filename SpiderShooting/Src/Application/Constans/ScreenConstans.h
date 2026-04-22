#pragma once

//==========================================
// ゲーム画面の大きさを設定する領域
//==========================================

// 画面の幅
constexpr float SCREEN_WIDTH = 1280.0f;	// 横幅
constexpr float SCREEN_HEIGHT = 720.0f;	// 縦幅

// 以下は上の大きさを変えるだけで勝手に変わる
constexpr float SCREEN_TOP		= +SCREEN_HEIGHT / 2;
constexpr float SCREEN_BOTTOM	= -SCREEN_HEIGHT / 2;
constexpr float SCREEN_LEFT		= -SCREEN_WIDTH / 2;
constexpr float SCREEN_RIGHT	= +SCREEN_WIDTH / 2;
