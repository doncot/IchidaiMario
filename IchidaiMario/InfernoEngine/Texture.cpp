#include<Texture.h>
#include"Graphics.h"
#include"Common.h"

using namespace std;

namespace Inferno{
Texture::Texture()
:m_tex(nullptr), m_width(0), m_height(0)
{
}

Texture::~Texture()
{
	SAFE_RELEASE(m_tex);
}

void Texture::LoadImageFile(const Graphics& g, const string& filename)
{
	m_name = filename;
	g.LoadTexture(filename, &m_width, &m_height, &m_tex);
}

unsigned Texture::GetWidth() const
{
	return m_width;
}

unsigned Texture::GetHeight() const
{
	return m_height;
}

LP_TEXTURE Texture::GetTexture() const
{
	return m_tex;
}

const string Texture::GetName() const
{
	return m_name;
}

/*
Rect Texture::GetSubRegion(const int n) const
{
	return m_subRegions.at(n).rect;
}
*/

Texture& Texture::operator=(const Texture& tex)
{
	//自己代入をチェック
	if (this == &tex) return *this;

	//LP_TEXTUREの参照カウンタを足す
	m_tex = tex.m_tex;
	m_tex->AddRef();

	//スタックオブジェクトをそのままコピー
	this->m_name = tex.m_name;
	this->m_width = tex.m_width;
	this->m_height = tex.m_height;
	//this->m_subRegions = tex.m_subRegions;

	return *this;
}

}