#include "SceneTransitionController.h"

#include"../Constans/ScreenConstans.h"

// フェードインの開始
void SceneTransitionController::StartFeadIn()
{
	// 黒 → 透明 のフェード開始
	m_state = FadeState::FadeIn;
	m_duration = 1.0f;
	m_timer = 0.0f;

	// フェードインは最初が真っ暗なので1.0fを代入
	m_alp = 1.0f;
}

// フェードアウトの開始
void SceneTransitionController::StartFeadOut()
{
	// 透明 → 黒 のフェードを開始
	m_state = FadeState::FadeOut;
	m_duration = 1.0f;
	m_timer = 0.0f;

	// フェードアウトは最初は透明なので0.0fを代入する
	m_alp = 0.0f;
}

void SceneTransitionController::Update(float deltaTime)
{
	// フェードしていないなら何もしない
	if (m_state == FadeState::None)return;

	// 経過時間を進める
	m_timer += deltaTime;

	// 0.0 ~ 1.0 の進行度
	float t = m_timer / m_duration;

	// フェードイン中の処理
	if (m_state == FadeState::FadeIn)
	{
		// 真っ黒 ~ 透明
		m_alp = 1.0f - t;

		// 完了判定
		if (t >= 1.0f)
		{
			m_alp = 0.0f;
			m_state = FadeState::None;
		}
	}

	// フェードアウト中の処理
	else if (m_state == FadeState::FadeOut)
	{
		// 透明 ~ 黒 
		m_alp = t;

		// 完了判定
		if (t >= 1.0f)
		{
			m_alp = 1.0f;
			m_state = FadeState::None;
		}
	}
}

void SceneTransitionController::Draw()
{
	// フェードしていないなら描画しない
	if (m_state == FadeState::None)return;

	SHADER.m_spriteShader.End();

	// 画面全体を覆う黒い四角を描画
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(
		0, 0,
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		&Math::Color(0, 0, 0, m_alp));
}
