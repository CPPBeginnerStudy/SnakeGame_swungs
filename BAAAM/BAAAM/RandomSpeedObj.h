#pragma once
#include "Object.h" 

class RandomSpeedObj : public Object
// Ŭ���� : �θ� Ŭ������ ���·� ����� ��� ����

{
public:
	// �ݵ�� ���� �Ҹ��� 
	RandomSpeedObj();
	virtual ~RandomSpeedObj();

	virtual void Update() override;
	virtual void Render() override;

private:

};

