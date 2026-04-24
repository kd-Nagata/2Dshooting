#include "GameManager.h"

// (未完成)(未実装)
void GameManager::DrawBackGround1(std::string &texName,float texW,float texH)
{
	// 画面サイズ
	const float scrW = SCREEN_WIDTH;
	const float scrH = SCREEN_HEIGHT;

	// 画面に合わせてスケール
	float scaleX = 1.0f;
	float scaleY = scrH / texH;

	// ループさせる(未実装)(カメラが必要)


	for (int i = 0;i < 5;++i)
	{
		Math::Matrix s = Math::Matrix::CreateScale(scaleX, scaleY,1);
		// 本来はscrollをする為に第一引数をSCREEN_LEFT - scrollX + (i * texW)を入れている(未実装))
		Math::Matrix t = Math::Matrix::CreateTranslation(
			0,
			0,
			0);

		SHADER.m_spriteShader.SetMatrix(s * t);
		SHADER.m_spriteShader.DrawTex(TEX.GetTexture(TextureType::Map, texName),
			Math::Rectangle(0, 0, texW, texH));
	}

}