#pragma once

// このクラスがインスタンスを持つクラスのファイルを読み込む
#include "TextureManager.h"
#include "../Object/Player/Player.h"
// PlayerやSound等も持つ

#include "../Constans/ScreenConstans.h"


//===========================================================
// ゲーム全体を管理するクラス
// ・プレイヤーはこのクラスにある一つだけ
// ・Textureや当たり判定、カメラやサウンドもここから貰う
//===========================================================
class GameManager
{

public:

	// ゲームをリセットする関数(未実装)
	// (主にプレイヤーの初期化とカメラの初期化を行う想定)
	void ResetGame() 
	{
		m_player.Init();
	}

	// 更新 ここでPlayerの更新を行う(カメラがあればカメラのUpdateも行う)
	// (未実装)
	void Update()
	{
		m_player.PreUpdate();
		m_player.Update();
	}

	// 背景描画関数
	void DrawBackGround1(std::string &texName,float texW,float texH);
	//void DrawBackGround2(std::string &texName,float texW,float texH);

	// ゲッター
	TextureManager& GetTexture() { return m_texture; }

	c_Player& GetPlayer() { return m_player; }

private:

	// シングルトン
	GameManager() = default;

	// TextureManager
	TextureManager m_texture;

	c_Player m_player;

public:

	static GameManager& GetInstance()
	{
		static GameManager instance;
		return instance;
	}

};

// ↓↓ここにdefineを書いて、GameManager経由でTexやSoundを貰えるようにする

#define GAME GameManager::GetInstance()

#define TEX GameManager::GetInstance().GetTexture()

#define PLAYER GameManager::GetInstance().GetPlayer()