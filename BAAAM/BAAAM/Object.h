#pragma once
class Object
{

public:
	//Ŭ���� �ȿ� Ŭ����, �̳� ���� ����
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

public:
	// �Ҹ��ڸ� ���� �Ҹ��ڷ� �����Ѵ�
	// �� Ŭ������ ��ӹ��� Ŭ�������� ��� ������ �Լ��� 
	// �� ��ӹ��� Ŭ�������� ���ǵȴ�� ���̷��� �̷��� ���� �Ҹ��ڷ� �����ؾ� �Ѵٰ� �Ѵ�.

	// �� �̹������� Object1�� new BaseClass()�� �����ư�, Object2�� new DerivedClass()�� �����ƴٰ� ���� �ȴ�. 
	// ���߾� ���̺� ������ ���� ���ذ� �� �� ������ 
	// ���� �̹����� ���ظ� ���߾��. �������� �� ���� ��Ź�帮�ڽ��ϴ� ;��;
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
	float GetX() const { return m_X; }
	float GetY() const { return m_Y; }

	void SetShape(wchar_t _shape) { m_Shape = _shape; }
	void SetX(float _x) { m_X = _x; }
	void SetY(float _y) { m_Y = _y; }

	// ����� �Ÿ��� ���ڷ� �޾Ƽ� �̵��� �����ϰ�,
    // ������ �̵��� �ߴ��� ���θ� bool������ ��ȯ�ϴ� �Լ�
	bool Move(Direction _dir, float _distance);

private:
protected: 
	// �� ������ �ڽ� Ŭ���������� ������ ������ �����̴�.
	// ������ �����ϴٴ� ���� ��Ȯ�� ���� �ǹ����� �� �𸣰ڽ��ϴ�.
	// RandomSpeedObj.m_X �̷� ������ �ڽ� Ŭ�������� �Ʒ��� ��� �������� ����� �� ���ٴ� ���ΰ���? 
	// ���� ��ǥ
	wchar_t m_Shape;
	float m_X;
	float m_Y;

	// �ӷ�
	float m_SpeedX;
	float m_SpeedY;

	// �̵����� ����
	bool m_IsRight;
	bool m_IsBottom;

};

