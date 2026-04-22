#pragma once
#include "SceneBase.h"
#include "SceneTransitionController.h"

//====================================================
// シーンを管理するクラス
// Path of Wavesと同様のシーンスタック方式を採用
// 遷移命令は即時実行せずキューに積んでフレーム終わりに処理
//====================================================

class SceneManager
{

public:

	SceneManager() = default;
	~SceneManager();

	// 新しいシーンを現在の上に積む関数
	void RequestPush(std::unique_ptr<SceneBase> scene);

	// 最上位シーンを取り除く
	void RequestPop();

	// 現在のシーンを新しいシーンに置き換える
	void RequestChange(std::unique_ptr<SceneBase>scene);

	// シーン遷移命令が出ていればキューに従って遷移する
	void ProcessCommands();

	// 毎フレーム処理
	void Update();
	void Draw();
	void ImGuiUpdate();

	// フェード状態のゲッター関数

	// m_transition(トランジションクラスのインスタンスを返す)
	bool GetFeatIn()const { return 0; }
	bool GetFeatOut()const { return 0; }

private:

	// 遷移コマンドの種類
	enum class CommandType
	{
		Push,	// 上に積む
		Pop,	// 上のシーンを消す
		Change	// シーンを変える
	};

	// シーン遷移要求をキューに積むためのデータ
	struct Command
	{
		CommandType type;					// 遷移コマンドの種類
		std::unique_ptr<SceneBase> scene;	// push/changeの時につかう新しいシーン
	};

	// シーンをスタック方式で管理
	// (最上位が現在のシーン)
	std::vector<std::unique_ptr<SceneBase>> mp_sceneStack;

	// 遷移命令をフレーム終わりにまとめて処理する為のキュー
	std::queue<Command> m_commandQueue;

	// シーン遷移システムのインスタンス
	SceneTransitionController m_transition;

	// シーン遷移処理
	void PushScene(std::unique_ptr<SceneBase> scene);
	void PopScene();
	void ChangeScene(std::unique_ptr<SceneBase> scene);
};