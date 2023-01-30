#pragma once

class Scene
{
public:

	// object manager
	ObjectManager obm;
	// object ui manager
	ObjectManager obum;

public:
	void Update(float _deltaTime);
	void FixedUpdate(float _fixedDeltaTime);
	void Render();
	void UiRender();

public:
	virtual ~Scene() {}
	virtual void OnActiveScene() = 0;
	virtual void OnUpdate(float _deltaTime) = 0;
	virtual void OnFixedUpdate(float _fixedDeltaTime) = 0;
	virtual void OnRender() = 0;
	virtual void OnUiRender() = 0;
};

class SceneManager : public Singleton<SceneManager>
{
private:

	std::map<std::wstring, Scene*> sceneMap;
	Scene *curScene = nullptr, *nextScene = nullptr;
	Sprite spriteLoading;
	SpriteRI spriteLoadingRI;
	bool isResetDeltaTime = false;

public:

	SceneManager();
	Scene* GetActiveScene();
	bool IsResetDeltaTime() { return isResetDeltaTime; };
	void AddScene(const std::wstring& _name, Scene* _newScene);
	void ChangeScene(const std::wstring& _name);
	void RemoveScene(const std::wstring& _name);

public:
	void Update(float _deltaTime);
	void FixedUpdate(float _fixedDeltaTime);
	void Render();
	void UiRender();
};
