/*
オリジナルテクスチャ（をあれやコレする）クラス
※ライブラリ側からは実装非依存にする
*/
#pragma once
#include<d3d9.h> //こいつらは本当は追い出したい(実装隠蔽)
#include<d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include<string>
#include<vector>
#include"Graphics.h"
#include"MyTypes.h"

namespace Inferno{
//テクスチャを内部的に区切るために使う
struct SubRegion
{
	int id; //ID。0を描画で指定すると全体を表示する
	Rect rect;
};

class Texture{
public:
	Texture();
	virtual ~Texture();

	//テクスチャを画像ファイルよりロード
	void LoadImageFile(const Graphics& g, const std::string& filename);

	unsigned GetWidth() const;
	unsigned GetHeight() const;
	LP_TEXTURE GetTexture() const;
	const std::string GetName() const;
	//Rect GetSubRegion(const int n) const;

	//LP_TEXTUREがあるから、deepcopyが必要
	Texture& operator=(const Texture& tex);

private:
	LP_TEXTURE m_tex; //LP_TEXTURE自体がItextureインターフェイスへのポインタ
	std::string m_name;
	unsigned m_width;	//結局これ使うんかい！！
	unsigned m_height; 
	//vector<SubRegion> m_subRegions; //テクスチャの中の分割したやつを記憶
};

/*
複数のテクスチャを扱うクラス
*/
class MultiTexture : public Texture
{
	~MultiTexture() {}
};

}