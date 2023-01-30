#include "Header.h"

void Sprite::CreateMaskTexture(D3DCOLOR _color)
{
	if (szScene == 0)
	{
		assert(0);
		return;
	}

	maskWidth = textures[0]->info.Width;
	maskHeight = textures[0]->info.Height;

	if (FAILED(D3DXCreateTexture(Direct3D::GetInstance().pd3dDevice,
		maskWidth,
		maskHeight,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		&maskSrc)))
	{
		assert(0);
		return;
	}

	maskBit.resize(maskWidth * maskHeight);
	for (int i = 0; i < maskWidth * maskHeight; ++i)
		maskBit[i] = _color;

	//UpdateMaskTexture();
}

void Sprite::UpdateMaskTexture(int _x, int _y, D3DCOLOR _color)
{
	maskBit[_y * maskWidth + _x] = _color;

	/*D3DLOCKED_RECT rect;
	if (FAILED(maskSrc->LockRect(0, &rect, nullptr, D3DLOCK_DISCARD)))
	{
		assert(0);
		return;
	}

	unsigned char* pBits = static_cast<unsigned char*>(rect.pBits);
	pBits += rect.Pitch * _y;
	((D3DCOLOR*)pBits)[_x] = _color;

	maskSrc->UnlockRect(0);*/
}

void Sprite::UpdateMaskTexture()
{
	D3DLOCKED_RECT rect;
	if (FAILED(maskSrc->LockRect(0, &rect, nullptr, D3DLOCK_DISCARD)))
	{
		assert(0);
		return;
	}

	unsigned char* pBits = static_cast<unsigned char*>(rect.pBits);
	for (int i = 0; i < maskHeight; ++i)
	{
		memcpy(pBits, &maskBit[i * maskWidth], sizeof(D3DCOLOR) * maskWidth);
		pBits += rect.Pitch;
	}

	maskSrc->UnlockRect(0);
	
}

Sprite::~Sprite()
{
	if (maskSrc)
		maskSrc->Release();
}

void Sprite::LoadAll(const std::wstring& _filePath)
{
	filePath = _filePath;
	textures.clear();
	for (auto path : std::filesystem::directory_iterator(_filePath))
		textures.push_back(TextureManager::GetInstance().GetTexture(path.path()));
	szScene = static_cast<int>(textures.size());
}

void Sprite::Update(float _deltaTime)
{
	aniDeltaTime += _deltaTime;

	if (aniDeltaTime > aniTime)
	{
		aniDeltaTime -= aniTime;
		if (++scene >= szScene)
		{
			if (aniLoop)
			{
				scene = 0;
			}
			else 
				--scene;
		}
	}
}

void Sprite::Render(const SpriteRI& _ri)
{
	if (scene >= szScene)
	{
		assert(0);
		return;
	}

	auto pd3dDevice = Direct3D::GetInstance().pd3dDevice;
	auto pVB = Direct3D::GetInstance().pVB;
	auto pTexture = textures[scene];
	float fHeight = static_cast<float>(pTexture->info.Height);
	float fWidth = static_cast<float>(pTexture->info.Width);
	float u0 = -fWidth * _ri.center.x;
	float u1 = fWidth - fWidth * _ri.center.x;
	float v0 = -fHeight * _ri.center.y;
	float v1 = fHeight - fHeight * _ri.center.y;
	D3DCOLOR diffuse = D3DCOLOR_ARGB(int(_ri.a * 255.0f), int(_ri.r * 255.0f), int(_ri.g * 255.0f), int(_ri.b * 255.0f));
	CUSTOMVERTEX* pVertices;
	pVB->Lock(0, 0, (void**)&pVertices, 0);
	pVertices[0].position = D3DXVECTOR3(u0, v0, 0.0f);
	pVertices[0].uv = D3DXVECTOR2(0.0f, 1.0f);
	pVertices[0].diffuse = diffuse;
	pVertices[1].position = D3DXVECTOR3(u0, v1, 0.0f);
	pVertices[1].uv = D3DXVECTOR2(0.0f, 0.0f);
	pVertices[1].diffuse = diffuse;
	pVertices[2].position = D3DXVECTOR3(u1, v0, 0.0f);
	pVertices[2].uv = D3DXVECTOR2(1.0f, 1.0f);
	pVertices[2].diffuse = diffuse;
	pVertices[3].position = D3DXVECTOR3(u1, v1, 0.0f);
	pVertices[3].uv = D3DXVECTOR2(1.0f, 0.0f);
	pVertices[3].diffuse = diffuse;
	pVB->Unlock();

	if (maskSrc)
	{
		pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
		pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
		pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
		pd3dDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	}

	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, &_ri.scaleCen, 0.0f, &_ri.scale, &_ri.rotateCen, -D3DXToRadian(_ri.rotate), &_ri.pos);
	pd3dDevice->SetTransform(D3DTS_WORLD, &matrix);
	pd3dDevice->SetTexture(0, pTexture->src);
	pd3dDevice->SetTexture(1, maskSrc);
	pd3dDevice->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX));
	pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
