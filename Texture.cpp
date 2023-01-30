#include "Header.h"

Texture* TextureManager::GetTexture(std::wstring filePathWithName)
{
	auto tf = texMap.find(filePathWithName);
	if (tf != texMap.end())
		return tf->second;

	Texture* texture = new Texture();
	if (FAILED(D3DXCreateTextureFromFileEx(Direct3D::GetInstance().pd3dDevice,
		filePathWithName.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER,
		D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER,
		0,
		&texture->info,
		nullptr,
		&texture->src
	)))
	{
		assert(0);
		delete texture;
		return nullptr;
	}

	texMap.insert(std::make_pair(filePathWithName, texture));
	return texture;
}