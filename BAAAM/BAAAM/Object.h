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
    /// > 함수 바로 뒤에 const가 붙는 경우는, 해당 함수가 멤버변수를 수정하지 않는다는 의미입니다.
    /// > 함수에서 반환한 값에 영향을 주는 것은 아니고, 함수 내부에서의 불변성을 뜻합니다.
    /// > const 객체에서는 const 함수만을 호출할 수 있습니다.
    /// > (그 객체의 상태를 변경하지 않는다는 것이 보장되기 때문에)
    /// > 예)
    /// > const Obejct a;
    /// > a.GetShape();     // ok
    /// > a.SetShape(' ');  // error
	char GetShape() const { return m_Shape; }
	short GetX() const { return m_X; }
	short GetY() const { return m_Y; }
	short GetSpeed() const { return m_Speed; }


	void SetShape(char _shape) { m_Shape = _shape; }
	void SetX(short _x) { m_X = _x; }
	void SetY(short _y) { m_Y = _y; }
	void SetSpeed(short _speed) { m_Speed = _speed; }

private:
	// 모양과 좌표
	char m_Shape;
	short m_X;
	short m_Y;

	// 속도
	short m_Speed;
	short m_SpeedMin;
	short m_SpeedMax;

	// 이동방향 구분
	bool m_IsRight;
	bool m_IsBottom;

};

