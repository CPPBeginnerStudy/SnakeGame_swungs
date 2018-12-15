#pragma once
class Object
{

public:
	//클래스 안에 클래스, 이넘 정의 가능
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

public:
	// 소멸자를 가상 소멸자로 선언한다
	// 이 클래스를 상속받은 클래스들의 멤버 변수나 함수가 
	// 각 상속받은 클래스에서 정의된대로 쓰이려면 이렇게 가상 소멸자로 선언해야 한다고 한다.

	// 위 이미지에서 Object1은 new BaseClass()로 생성됐고, Object2는 new DerivedClass()로 생성됐다고 보면 된다. 
	// 버추얼 테이블 개념은 얼추 이해가 된 것 같은데 
	// 참고 이미지는 이해를 못했어요. 수업에서 상세 설명 부탁드리겠습니다 ;ㅁ;
	Object();
	virtual ~Object();

	// 오브젝트 클래스 구성 함수
	// 사용할 일이 없을 거 같으니 제거
	//virtual void Init();
	//virtual void Release();
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
	wchar_t GetShape() const { return m_Shape; }
	float GetX() const { return m_X; }
	float GetY() const { return m_Y; }

	void SetShape(wchar_t _shape) { m_Shape = _shape; }
	void SetX(float _x) { m_X = _x; }
	void SetY(float _y) { m_Y = _y; }

	// 방향과 거리를 인자로 받아서 이동을 수행하고,
    // 실제로 이동을 했는지 여부를 bool값으로 반환하는 함수
	bool Move(Direction _dir, float _distance);

private:
protected: 
	// 이 범위는 자식 클래스에서도 접근이 가능한 범위이다.
	// 접근이 가능하다는 말이 정확히 무슨 의미인지 잘 모르겠습니다.
	// RandomSpeedObj.m_X 이런 식으로 자식 클래스에서 아래의 멤버 변수들을 사용할 수 없다는 뜻인가요? 
	// 모양과 좌표
	wchar_t m_Shape;
	float m_X;
	float m_Y;

	// 속력
	float m_SpeedX;
	float m_SpeedY;

	// 이동방향 구분
	bool m_IsRight;
	bool m_IsBottom;

};

