#pragma once

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;
	D3DCOLOR diffuse;
	D3DXVECTOR2 uv;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class Direct3D : public Singleton<Direct3D>
{
public:
	LPDIRECT3D9             pD3D = NULL;

	LPDIRECT3DDEVICE9       pd3dDevice = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	LPD3DXLINE				pLine = NULL;

	HWND wnd;
	std::wstring nameOfWindowClass = TEXT("VIRUS_STRIKER_CLASS");
	std::wstring nameOfWindow = TEXT("VIRUS STRIKER");
	int wndWidth = 1921;
	int wndHeight = 1081;
	float gameWidth = 1921.0f;
	float gameHeight = 1081.0f;
	int fps = 0;

	D3DXVECTOR2 cameraPos = { 0.0f, 0.0f }, destCameraPos = { 0.0f, 0.0f};
	D3DXVECTOR2 cameraScale = { 1.0f, 1.0f }, destCameraScale = { 1.0f, 1.0f };
	D3DXVECTOR2 cameraQuaken = { 0.0f, 0.0f }, destCameraQuaken = { 0.0f, 0.0f };
	D3DXMATRIX matView, matProj;

	HRESULT InitD3D(HWND hWnd);
	VOID Update(float _deltaTime);
	VOID FixedUpdate(float _fixedDeltaTime);
	VOID Render();
	VOID CleanUp();
};