#include"Graphics.h"
#include"Common.h"
#include<InfernoException.h>

namespace Inferno
{
Graphics::Graphics()
	:m_d3d(nullptr), m_d3dDevice(nullptr), m_sprite(nullptr), m_backScreenColor(0,0,150)
{
}

void Graphics::Initialize(HWND hWnd)
{
	//D3Dオブジェクトを生成
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	//D3Dデバイスを生成するための構造体を設定する
	D3DPRESENT_PARAMETERS d3dp;
	ZeroMemory(&d3dp, sizeof(d3dp));
	d3dp.Windowed = TRUE;
	d3dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dp.EnableAutoDepthStencil = TRUE;
	d3dp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; //V-SYNCをする
								//D3DPRESENT_INTERVAL_DEFAULT;

	m_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dp,
		&m_d3dDevice
		);

	//スプライト作成
	if (FAILED(D3DXCreateSprite(m_d3dDevice, &m_sprite)))
	{
		throw GraphicsError(TEXT("スプライト作成に失敗。"));
	}

	//初期化が完了したら青クリアをする
	this->FlashBackScreen(0, 0, 128);
}

void Graphics::Finalize()
{
	SAFE_RELEASE(m_sprite);
	SAFE_RELEASE(m_d3dDevice);
	SAFE_RELEASE(m_d3d);
}

void Graphics::SetBackScreenColor(const int r, const int g, const int b)
{
	m_backScreenColor.Red = r;
	m_backScreenColor.Green = g;
	m_backScreenColor.Blue = b;
}

void Graphics::FlashBackScreen() const
{
	auto c = m_backScreenColor;

	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(c.Red, c.Green, c.Blue), 1.0f, 0);
	m_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Graphics::FlashBackScreen(const int r, const int g, const int b) const
{
	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(r,g,b), 1.0f, 0);
	m_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

bool Graphics::BeginScene() const
{
	auto c = m_backScreenColor;

	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(c.Red, c.Green, c.Blue), 1.0f, 0);
	return SUCCEEDED(m_d3dDevice->BeginScene());
}

void Graphics::EndScene() const
{
	m_d3dDevice->EndScene();
	m_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

bool Graphics::BeginSprite() const
{
	return SUCCEEDED(m_sprite->Begin(D3DXSPRITE_ALPHABLEND));
}

void Graphics::EndSprite() const
{
	m_sprite->End();
}

LPDIRECT3DDEVICE9 Graphics::GetDevice() const
{
	return m_d3dDevice;
}

LPD3DXSPRITE Graphics::GetSprite() const
{
	return m_sprite;
}

bool Graphics::LoadTexture(const std::string& filename,unsigned* width, unsigned* height, LP_TEXTURE* tex) const
{
	if (filename.empty())
	{
		tex = nullptr;
		return false;
	}

	HRESULT hr=0;
	D3DXIMAGE_INFO info;

	hr = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if (hr != D3D_OK)
	{
		throw GraphicsError("テクスチャが不正です。");
	}

	hr = D3DXCreateTextureFromFileEx(
		m_d3dDevice,
		filename.c_str(),
		info.Width,info.Height,
		1,0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&info,
		nullptr,
		tex
		);

	if (hr == D3DXERR_INVALIDDATA)
	{
		throw GraphicsError("テクスチャ生成失敗。");
	}

	*width = info.Width;
	*height = info.Height;

	return true;
}

void Graphics::TransformSprite(const Matrix* m) const
{
	m_sprite->SetTransform(&D3DXMATRIX(m->GetD3DMatrix()));
}

void Graphics::DrawSprite(const LP_TEXTURE tex, Vec2<float> center, const int alpha) const
{
	m_sprite->Draw(tex, NULL, &D3DXVECTOR3(center.x, center.y, 0),
		NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}

}