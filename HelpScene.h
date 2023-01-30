#pragma once

class HTPs : public Scene
{
private:
	Sprite HTP;
	SpriteRI HTPRI;

	Sprite HTPkBackground;
	SpriteRI HTPkBackgroundRI;

	int htpnumber = 0;
public:
	HTPs(int _htpnumber);
	// Scene을(를) 통해 상속됨
	virtual void OnActiveScene() override;
	virtual void OnUpdate(float _deltaTime) override;
	virtual void OnFixedUpdate(float _fixedDeltaTime) override {};
	virtual void OnRender() override;
	virtual void OnUiRender() override {};
};

class HelpScene : public Scene
{
private:

	Sprite HTPkBackground;
	SpriteRI HTPkBackgroundRI;

	Sprite HTPMain;
	SpriteRI HTPMainRI;

	Sprite Menu[3];
	SpriteRI MenuRI[3];

	Sprite CurSor;
	SpriteRI CurSorRI;

	unsigned int NowCurSor = 0;

	bool NowHelp = false;

public:

	HelpScene();
	// Scene을(를) 통해 상속됨
	virtual void OnActiveScene() override;
	virtual void OnUpdate(float _deltaTime) override;
	virtual void OnFixedUpdate(float _fixedDeltaTime) override;
	virtual void OnRender() override;
	virtual void OnUiRender() override;
};