#pragma once
#include "Object.h"
class Apple : public Object
{
public:
	Apple();
	virtual ~Apple();

	virtual void Update(float _dt) override; 
	//override�� ��� ��ü�� ������ �ִ� ���� �ƴϰ� ��ӹ޾Ҵٴ� Ű����
	// ��ӹ��� �ְ� ���� �� ������ ����ִ� �����̴� (������ġ)
	virtual void Render() override;
};

