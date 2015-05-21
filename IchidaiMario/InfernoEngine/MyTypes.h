/*
自作の数学系あれやこれや
*/
#pragma once
#include<Windows.h>
#include<d3d9.h>

namespace Inferno
{
//二次元座標
template<typename T> struct Vec2 //テンプレートはヘッダーに実装を書くのが正解
{
	T x;
	T y;
	Vec2() : x(0), y(0) {}
	Vec2(T x_, T y_) : x(x_), y(y_) {}

	const Vec2<T> operator+(const Vec2<T>& vec) const
	{
		Vec2<T> result = *this;
		result.x += vec.x;
		result.y += vec.y;
		return result;
	}

	const Vec2<T> operator+(Vec2<T>& vec) const
	{
		return this->operator+(vec);
	}

	void operator+=(const Vec2<T>& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
	}

	void operator+=(Vec2<T>& vec)
	{
		this->operator+=(vec);
	}

	bool operator==(const Vec2<T>& vec) const
	{
		//浮動小数点系は使わない
		if (this->x == vec.x && this->y == vec.y)
		{
			return true;
		}
		else return false;
	}

	bool operator==(Vec2<T>& vec) const
	{
		this->operator==(vec);
	}
};

class Matrix
{
public:
	void LoadIdentity();
	void Transform2D(const float x, const float y);
	const D3DMATRIX GetD3DMatrix() const;

private:
	float m[4][4];
};

//MyRECT
class Rect
{
public:
	Rect() : m_center(0, 0), m_height(0), m_width(0) {}
	Rect(const int width, const int height);
	Rect(const Vec2<int>& p, const int width, const int height);

	//Win32のRECTを返す
	RECT GetMSRECT() const;

	int Top() const;
	int Right() const;
	int Left() const;
	int Bottom() const;
	Vec2<int> UpperLeft() const;
	Vec2<int> UpperRight() const;
	Vec2<int> BottomLeft() const;
	Vec2<int> BottomRight() const;

	void SetSize(const int Width, const int Height);
	void AMove(const Vec2<int>& v);
	void AMove(const int x, const int y);
	void RMove(const int x, const int y);
	void SetPosofULCorner(const int x, const int y);
	int Width() const;
	int Height() const;
	Vec2<int> Center() const;


	//const Rect operator=(const Rect& r);

private:
	Vec2<int> m_center;
	int m_height;
	int m_width;
};


//以下Rect関連のユーテリティ
//幅と高さよりRectを作る（0を中心に作る）
Rect SetRectFromWH(const unsigned width, const unsigned height);
Vec2<int> GetCenterOfRect(const Rect& r);
long GetWidthOfRect(const Rect& r);
long GetHeightOfRect(const Rect& r);
Rect AddRect(const Rect& r1, const Rect& r2);

//Color
struct Color
{
	Color() : Red(0), Green(0), Blue(0) {}
	Color(int red,int green,int blue) : Red(red), Green(green), Blue(blue) {}

	int Red;
	int Green;
	int Blue;
};


}