#pragma once
#include "../ObjectBase.h"

class c_Player :public ObjectBase
{
public:

	void Init();
	void PreUpdate()override;
	void Update()override;
	void Draw()override;
	void Release();

private:

	Math::Vector2 m_pow = {};

	float count = 0;

	bool triW = false;
	bool triS = false;
};
