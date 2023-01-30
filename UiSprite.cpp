#include "Header.h"

UiSprite::UiSprite(std::wstring _filePath)
{
	sprite.LoadAll(_filePath);
}

void UiSprite::Update(float _deltaTime)
{
}

void UiSprite::LateUpdate(float _deltaTime)
{
}

void UiSprite::FixedUpdate(float _fixedDeltaTime)
{
}

void UiSprite::Render()
{
	sprite.Render(spriteRI);
}

void UiSprite::OnCollision(const CollisionBody& body)
{
}
