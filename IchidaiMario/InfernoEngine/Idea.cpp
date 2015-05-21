#include<GameElements.h>
#include"Common.h"
#include"Graphics.h"

namespace Inferno
{
Idea::Idea()
: m_tex(nullptr), m_width(0), m_height(0) {}

Idea::~Idea()
{}

void Idea::SetTexture(const Texture& tex)
{
	m_tex = &tex;
	//描画基準の計算
	m_width = m_tex->GetWidth();
	m_height = m_tex->GetHeight();

	m_drawBase.x = m_width / 2;
	m_drawBase.y = m_height / 2;
}

const Texture* Idea::GetTexture() const
{
	return m_tex;
}

bool Idea::IsTextureSet() const
{
	return m_tex != nullptr;
}

Vec2<int> Idea::GetDrawBase() const
{
	return m_drawBase;
}

int Idea::GetWidth() const
{
	return m_width;
}

int Idea::GetHeight() const
{
	return m_height;
}

void Idea::SetActiveRange(const Rect& screen, int margin)
{
	//少し行って戻るケースもあるので、少し多めに画面外にはみ出したら検出
	Rect tempRect;
	tempRect.SetSize(screen.Width() + margin * 2, screen.Height() + margin * 2);
	//右上にセット
	tempRect.SetPosofULCorner(0, 0);
	m_activeRange = tempRect;
}

}