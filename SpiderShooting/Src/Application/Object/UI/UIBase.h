#pragma once
#include"../ObjectBase.h"

class UIBase :public ObjectBase
{

public:

	virtual ~UIBase() = default;

	// 基本
	virtual void Update()override;
	virtual void Draw()override;



private:

};