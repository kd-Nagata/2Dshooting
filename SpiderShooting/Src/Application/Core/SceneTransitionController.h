#pragma once

// SceneTransitionController
// シーン線いのフェード演出を管理するクラス

// フェードイン	：黒→透明
// フェードアウト	：透明→黒

// SceneManagerから呼び出され、シーン遷移の演出部分のみを
// このクラスに切り離すことでSceneManagerとSceneBaseの責務を
// 明確に分離する事が目的。

// ゲーム全体で共通のフェード演出を提供し、
// 遷移完了の判定(IsFabeInFinished/IsFadeOutFinished)も行う。


// フェードの状態
enum class FadeState
{
	None,		// 何もしていない
	FadeIn,		// 黒 → 透明
	FadeOut		// 透明 → 黒
};

class SceneTransitionController
{

public:

	// フェード開始
	void StartFeadIn();
	void StartFeadOut();

	// 毎フレーム更新
	void Update(float deltaTime);

	// フェード描画
	void Draw();

	// 状態のゲッター
	FadeState GetState() { return m_state; }

	// フェード完了判定
	bool IsFadeInFinished() const { return (m_state == FadeState::None && m_alp <= 0.0f); }
	bool IsFadeOutFinished() const { return (m_state == FadeState::None && m_alp >= 1.0f); }

private:

	FadeState m_state = FadeState::None;

	float m_timer = 0.0f;	// 経過時間
	float m_alp = 0.0f;		// 透明度
	float m_duration = 1.0f;// フェードにかける時間

};