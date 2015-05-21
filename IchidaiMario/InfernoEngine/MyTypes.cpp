#include"MyTypes.h"

namespace Inferno
{
void Matrix::LoadIdentity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}

void Matrix::Transform2D(const float x, const float y)
{
	m[3][0] += x;
	m[3][1] += y;
}

const D3DMATRIX Matrix::GetD3DMatrix() const
{
	D3DMATRIX dm;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			dm.m[i][j] = m[i][j];
		}
	}

	return dm;
}

Rect::Rect(const int width, const int height)
{
	SetSize(width, height);
}

Rect::Rect(const Vec2<int>& p, const int width, const int height)
{
	m_center = p;
	SetSize(width, height);
}

//Win32‚ÌRECT‚ð•Ô‚·
RECT Rect::GetMSRECT() const
{
	RECT r;
	r.top = m_center.y - m_height / 2;
	r.left = m_center.x - m_width / 2;
	r.right = m_center.x + m_width / 2;
	r.bottom = m_center.y + m_height / 2;
	return r;
}

Vec2<int> Rect::Center() const { return m_center; }
int Rect::Top() const {	return m_center.y - m_height / 2; }
int Rect::Left() const { return m_center.x - m_width / 2; }
int Rect::Right() const { return m_center.x + m_width / 2; }
int Rect::Bottom() const { return m_center.y + m_height / 2; }
int Rect::Height() const { return m_height; }
int Rect::Width() const { return m_width; }

Vec2<int> Rect::UpperLeft() const {	return Vec2<int>(Left(), Top()); }
Vec2<int> Rect::UpperRight() const { return Vec2<int>(Right(), Top()); }
Vec2<int> Rect::BottomLeft() const { return Vec2<int>(Left(), Bottom()); }
Vec2<int> Rect::BottomRight() const { return Vec2<int>(Right(), Bottom()); }

void Rect::SetSize(const int width, const int height)
{
	m_width = width;
	m_height = height;
}

void Rect::AMove(const Vec2<int>& v)
{
	m_center = v;
}

void Rect::AMove(const int x, const int y)
{
	m_center.x = x;
	m_center.y = y;
}

void Rect::RMove(const int x, const int y)
{
	m_center.x += x;
	m_center.y += y;
}

void Rect::SetPosofULCorner(const int x, const int y)
{
	m_center.x = x + Width() / 2;
	m_center.y = y + Height() / 2;
}

}