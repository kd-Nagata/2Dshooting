#include "main.h"
#include "Scene.h"

#include "Scene/Title/Title.h"
#include "Scene/GameMain/GameMain.h"

void Scene::Draw2D()
{
	
}

void Scene::Update()
{
	
}

void Scene::Init()
{
	
}

void Scene::Release()
{
	// 画像の解放処理
	charaTex.Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
