#pragma once
class Object
{
public:
	// �Ҹ��ڸ� ���� �Ҹ��ڷ� �����Ѵ�
	// �� Ŭ������ ��ӹ��� Ŭ�������� ��� ������ �Լ��� 
	// �� ��ӹ��� Ŭ�������� ���ǵȴ�� ���̷��� �̷��� ���� �Ҹ��ڷ� �����ؾ� �Ѵٰ� �Ѵ�.
	Object();
	virtual ~Object();

	// ������Ʈ Ŭ���� ���� �Լ�
	// ����� ���� ���� �� ������ ����
	//virtual void Init();
	//virtual void Release();
	virtual void Update();
	virtual void Render();

	// ���⼭ const�� ���� ���ϱ��? 
	// getshape �Լ��� ��ȯ�ϴ��� ������ �Ұ����ϴٴ� ���ΰ�. 
	// const�� ���ִ� ������..
    /// > �Լ� �ٷ� �ڿ� const�� �ٴ� ����, �ش� �Լ��� ��������� �������� �ʴ´ٴ� �ǹ��Դϴ�.
    /// > �Լ����� ��ȯ�� ���� ������ �ִ� ���� �ƴϰ�, �Լ� ���ο����� �Һ����� ���մϴ�.
    /// > const ��ü������ const �Լ����� ȣ���� �� �ֽ��ϴ�.
    /// > (�� ��ü�� ���¸� �������� �ʴ´ٴ� ���� ����Ǳ� ������)
    /// > ��)
    /// > const Obejct a;
    /// > a.GetShape();     // ok
    /// > a.SetShape(' ');  // error
	wchar_t GetShape() const { return m_Shape; }
	short GetX() const { return m_X; }
	short GetY() const { return m_Y; }

	void SetShape(wchar_t _shape) { m_Shape = _shape; }
	void SetX(short _x) { m_X = _x; }
	void SetY(short _y) { m_Y = _y; }

private:
protected: 
	// �� ������ �ڽ� Ŭ���������� ������ ������ �����̴�.
	// ������ �����ϴٴ� ���� ��Ȯ�� ���� �ǹ����� �� �𸣰ڽ��ϴ�.
	// RandomSpeedObj.m_X �̷� ������ �ڽ� Ŭ�������� �Ʒ��� ��� �������� ����� �� ���ٴ� ���ΰ���? 
	// ���� ��ǥ
	wchar_t m_Shape;
	short m_X;
	short m_Y;

	// �ӷ�
	short m_SpeedX;
	short m_SpeedY;

	// �̵����� ����
	bool m_IsRight;
	bool m_IsBottom;

};

