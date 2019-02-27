#pragma once
#include "Object.h"
class Apple : public Object
{
public:
	Apple();
	virtual ~Apple();

	virtual void Update(float _dt) override; 
	//override는 기능 자체에 영향을 주는 것은 아니고 상속받았다는 키워드
	// 상속받을 애가 없을 때 빨간줄 띄워주는 역할이다 (안전장치)
	virtual void Render() override;
};

