#include "SceneManager.h"

// 残ってるシーンがなくなるまで解放し続ける
SceneManager::~SceneManager()
{
	while (!mp_sceneStack.empty())PopScene();
}

// リクエストしたシーンを一番上に生成する
void SceneManager::RequestPush(std::unique_ptr<SceneBase> scene)
{
	// フェード中は受け付けない
	if (m_transition.GetState() != FadeState::None)return;

	// コマンドを積む
	m_commandQueue.push({ CommandType::Push,std::move(scene) });

}

// 一番上のシーンを解放して下にあるシーンを戻す
void SceneManager::RequestPop()
{
	// コマンドを積む
	m_commandQueue.push({ CommandType::Pop,nullptr });
}

// リクエストしたシーンに遷移する
void SceneManager::RequestChange(std::unique_ptr<SceneBase> scene)
{
	// フェード中は新たにChangeリクエストを受け付けない
	if (m_transition.GetState() == FadeState::FadeOut)return;
	if (m_transition.GetState() == FadeState::FadeIn)return;

	// コマンドを積む
	m_commandQueue.push({ CommandType::Change,std::move(scene) });

	// フェードアウトの指示を出す
	m_transition.StartFeadOut();
}

// キューに命令が積まれていれば命令通り実行する
void SceneManager::ProcessCommands()
{
	// キューに溜まったシーン遷移コマンドを順に処理する
	while (!m_commandQueue.empty())
	{
		// 一番最初に積まれている命令を受け取る
		Command cmd = std::move(m_commandQueue.front());

		// 命令の先頭要素を削除
		m_commandQueue.pop();

		// どの命令を出されているかを判定

		switch (cmd.type)
		{
		case CommandType::Push:
		{
			// リクエストされたシーンを上に積む
			PushScene(std::move(cmd.scene));
			break;
		}
		case CommandType::Pop:
		{
			// 一番上にあるシーンの解放
			PopScene();
			break;
		}
		case CommandType::Change:
		{
			// 次のシーンに遷移
			ChangeScene(std::move(cmd.scene));
			break;
		}
		}
	}
}

// 毎フレームの更新
void SceneManager::Update()
{
	// サウンド更新(未実装)
	// SOUND.Update()

	// マウス更新(未実装)
	// MOUSE.Update()

	// フェード中でなければ、キューに溜まったシーン遷移コマンドを実行する
	if (m_transition.GetState() == FadeState::None)
	{
		ProcessCommands();
	}
	

	// 上にあるシーンから順番に更新処理
	for (int i = mp_sceneStack.size() - 1; i >= 0;--i)
	{
		mp_sceneStack[i]->Update();
		
		// このシーンが下の更新をブロックするなら終了
		if (mp_sceneStack[i]->BlocksBelowUpdate())break;
	}

	// フェードスピード
	float deltaTime = 0.03f;

	// フェードイン、フェードアウトの更新処理
	m_transition.Update(deltaTime);

	// フェードアウトが終わったら遷移実行
	if (m_transition.IsFadeOutFinished())
	{
		ProcessCommands();
		// フェードイン開始
		m_transition.StartFeadIn();
	}
}

// 描画処理
void SceneManager::Draw()
{
	// 下にあるシーンから順に描画
	for (int i = 0; i < mp_sceneStack.size();++i)
	{
		mp_sceneStack[i]->Draw();
		// このシーンが上の描画をブロックするなら終了
		if (mp_sceneStack[i]->BlocksBelowDraw())break;
	}

	// フェードイン、フェードアウトの描画処理
	m_transition.Draw();

}

void SceneManager::ImGuiUpdate()
{
	//return;
	
	// ウィンドウの初期位置/サイズを設定
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(240, 300), ImGuiSetCond_Always);

	// 動きを止めて、サイズも変更しない
	ImGuiWindowFlags flag = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	// デバッグ画面生成
	ImGui::Begin("Debug Window", nullptr, flag);

	// 最上位シーンのデバッグ画面を更新する
	if (!mp_sceneStack.empty())mp_sceneStack.back()->ImGuiUpdate();
	
	// 画面終了
	ImGui::End();

}

// シーンスタックの一番上にシーンを積む関数
void SceneManager::PushScene(std::unique_ptr<SceneBase> scene)
{
	// 一番上にあるシーンのポーズ処理を呼ぶ
	if (!mp_sceneStack.empty())mp_sceneStack.back()->OnPause();

	// 各シーンからシーン遷移のリクエストができるようにセットする
	scene->SetManager(this);

	// シーンを上に積む
	mp_sceneStack.push_back(std::move(scene));

	// シーンに入った時の処理(Init()と同じ)
	mp_sceneStack.back()->OnEnter();
}

// スタックの一番上のシーンを解放する
void SceneManager::PopScene()
{
	// 要素がない時に解放処理をしない為にif return
	if (mp_sceneStack.empty())return;

	// 一番上のシーンを抜けるときの処理(Release()と同じ)
	mp_sceneStack.back()->OnExit();

	// 一番上のシーンを削除
	mp_sceneStack.pop_back();

	// まだシーンが残っていたら、そのシーンが最上位に戻っている為
	// 最上位に戻った時の処理を呼ぶ
	if (!mp_sceneStack.empty())mp_sceneStack.back()->OnResume();
}

void SceneManager::ChangeScene(std::unique_ptr<SceneBase> scene)
{
	// 残ってるシーンを全削除
	while (!mp_sceneStack.empty())PopScene();

	// 新しいシーン一つだけにする
	PushScene(std::move(scene));
}
