#pragma once
#include "Object.h" 

class RandomSpeedObj : public Object
// 클래스 : 부모 클래스의 형태로 적어야 상속 받음

{
public:
	// 반드시 가상 소멸자 
	RandomSpeedObj();
	virtual ~RandomSpeedObj();

	virtual void Update() override;
	virtual void Render() override;

private:

};

