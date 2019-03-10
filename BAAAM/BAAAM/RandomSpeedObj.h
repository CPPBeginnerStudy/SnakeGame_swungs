#pragma once
#include "Object.h" 

class RandomSpeedObj : public Object
// Ŭ���� : �θ� Ŭ������ ���·� ����� ��� ����

{
public:
	// �ݵ�� ���� �Ҹ��� 
	RandomSpeedObj();
	virtual ~RandomSpeedObj();

	virtual void Update(float _dt) override;
	virtual void Render() override;

private:

	// �ӷ�
	int m_SpeedX;
	int m_SpeedY;

	// �̵����� ����
	bool m_IsRight;
	bool m_IsBottom;

};

