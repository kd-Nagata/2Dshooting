#pragma once
#include "../../Core/SceneBase.h"

class GameMain : public SceneBase
{

public:

	const char* GetName() const override { return "GameMain"; }

	void OnEnter()override;
	void Update()override;
	void Draw()override;
	void OnExit()override;

	void ImGuiUpdate()override;

private:

};