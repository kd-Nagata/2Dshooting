#pragma once
#include"UIBase.h"
#include"../../Enum/UILayer.h"

// ↓↓ 子クラス
#include "UIBtn.h"

class UIManager
{

public:

	// UIを追加する関数(Front,Backを指定可能)
	void Add(UIBase* ui, UILayer layer = UILayer::Front);

	// 基本
	void Update();
	void Draw();

	// 要素全削除
	void Clear();

private:

	// UIのリスト
	std::vector<UIBase*>m_uiList[(int)UILayer::Count];

};