#pragma once
#include "../ObjectBase.h"

class c_Player :public ObjectBase
{
public:

	void Init();
	void Update()override;
	void Draw()override;
	void Release();

private:




};
