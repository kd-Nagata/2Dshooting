#include "UIManager.h"

void UIManager::Add(UIBase* ui, UILayer layer)
{
	// 指定されたlayerのリストに追加
	m_uiList[(int)layer].push_back(ui);
}

void UIManager::Update()
{
	// 削除フラグの経っている要素を削除
	for (int i = 0;i < (int)UILayer::Count;++i)
	{
		for (auto itr = m_uiList[i].begin();itr != m_uiList[i].end();)
		{
			if ((*itr)->IsDelete())
			{
				delete* itr;
				itr = m_uiList[i].erase(itr);
				continue;
			}
			++itr;
		}
	}

	// 更新処理
	for (int i = 0;i < (int)UILayer::Count;++i)
	{
		for(auto ui : m_uiList[i])
		{
			ui->Update();
		}
	}

}

void UIManager::Draw()
{
	for (int i = 0; i < (int)UILayer::Count;++i)
	{
		for (auto ui : m_uiList[i])
		{
			ui->Draw();
		}
	}
}

void UIManager::Clear()
{
	for (int i = 0; i < (int)UILayer::Count;++i)
	{
		for (auto ui : m_uiList[i])
		{
			delete ui;
		}
		m_uiList[i].clear();
	}
}
