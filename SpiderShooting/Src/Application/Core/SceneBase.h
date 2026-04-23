#pragma once

class SceneManager;

#include"../Object/UI/UIManager.h"

class SceneBase
{

public:

	virtual ~SceneBase() = default;

	// デバッグ用 (シーン名を返す)
	virtual const char* GetName() const = 0;

	// SceneMnagerがシーンを生成後に呼び出す
	void SetManager(SceneManager* mgr) { mp_manager = mgr; }

	// シーンに入った時の処理
	virtual void OnEnter()
	{
		
	}
	// シーンを出る時の処理
	virtual void OnExit()
	{

	}

	// シーンが上に積まれる前の処理
	virtual void OnPause() {}
	// シーンが最上位に戻るときの処理
	virtual void OnResume() {}

	// メイン処理
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// デバッグ画面更新処理
	virtual void ImGuiUpdate() {}

	// 裏にあるシーンの更新/描画を止めるかどうか
	virtual bool BlocksBelowUpdate() { return true; }
	virtual bool BlocksBelowDraw() { return false; }


protected:

	// SceneManagerのポインタを持たせる
	SceneManager* mp_manager = nullptr;
	
	// UIManagerを持たせる
	UIManager m_ui;
	
	// EffectManagerのポインタを持たせる


};