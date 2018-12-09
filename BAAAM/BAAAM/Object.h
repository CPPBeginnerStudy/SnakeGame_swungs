#pragma once
class Object
{
public:
	// 소멸자를 가상 소멸자로 선언한다
	// 이 클래스를 상속받은 클래스들의 멤버 변수나 함수가 
	// 각 상속받은 클래스에서 정의된대로 쓰이려면 이렇게 가상 소멸자로 선언해야 한다고 한다.
	Object();
	virtual ~Object();

	// 오브젝트 클래스 구성 함수
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	// 여기서 const는 무슨 뜻일까요? 
	// getshape 함수로 반환하더라도 변형은 불가능하다는 뜻인가. 
	// const가 들어가있는 순서가..
	char GetShape() const { return m_Shape; }
	short GetX() const { return m_X; }
	short GetY() const { return m_Y; }

	void SetShape(char _shape) { m_Shape = _shape; }
	void SetX(short _x) { m_X = _x; }
	void SetY(short _y) { m_Y = _y; }


private:
	// 모양과 좌표
	char m_Shape;
	short m_X;
	short m_Y;

	// 이동방향 구분
	bool m_IsRight;
	bool m_IsBottom;

};

