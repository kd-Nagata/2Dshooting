#pragma once
// 親クラス
#include"../../Core/SceneBase.h"

class TitleScene : public SceneBase
{

public:

	// 何のシーンか文字列を返す関数
	const char* GetName() const override { return "TitleScene"; }
	
	// InitとReleaseの代わり
	void OnEnter() override;		// Init代わり
	void OnExit()  override;		// Release代わり

	// いつもの
	void Update()override;
	void Draw()override;

	// デバッグ画面更新関数
	void ImGuiUpdate()override;



private:

	KdTexture m_tex;
	KdTexture m_startTex;

	Math::Matrix mat;

};