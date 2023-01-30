#pragma once

class SpriteRI
{
public:

	D3DXVECTOR2 pos = { 0.0f, 0.0f };
	D3DXVECTOR2 scale = { 1.0f, 1.0f };
	D3DXVECTOR2 scaleCen = { 0.0f, 0.0f };
	float rotate = 0.0f;
	D3DXVECTOR2 rotateCen = { 0.0f, 0.0f };
	D3DXVECTOR2 center = { 0.5f, 0.5f };
	float a = 1.0f, r = 1.0f, g = 1.0f, b = 1.0f;

};

class Sprite
{
private:

	std::vector<Texture*> textures;

public:

	std::wstring filePath;
	int szScene = 0;
	int scene = 0;
	float aniTime = 0.05f;
	float aniDeltaTime = 0.0f;
	bool aniLoop = true;

public:

	LPDIRECT3DTEXTURE9 maskSrc = nullptr;
	std::vector<D3DCOLOR> maskBit;
	int maskWidth = 0;
	int maskHeight = 0;
	void CreateMaskTexture(D3DCOLOR _color);
	void UpdateMaskTexture(int _x, int _y, D3DCOLOR _color);
	void UpdateMaskTexture();

public:

	~Sprite();
	void LoadAll(const std::wstring& _filePath);
	void Update(float _deltaTime);
	void Render(const SpriteRI& _ri);

};