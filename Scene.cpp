#include "Header.h"

void Scene::Update(float _deltaTime)
{
	obm.Update(_deltaTime);
	obum.Update(_deltaTime);
	OnUpdate(_deltaTime);
}

void Scene::FixedUpdate(float _fixedDeltaTime)
{
	obm.FixedUpdate(_fixedDeltaTime);
	obum.FixedUpdate(_fixedDeltaTime);
	OnFixedUpdate(_fixedDeltaTime);
}

void Scene::Render()
{
	obm.Render();
	OnRender();
}

void Scene::UiRender()
{
	obum.Render();
	OnUiRender();
}

SceneManager::SceneManager()
{
	spriteLoading.LoadAll(TEXT("Assets/Ui/Loading"));
	spriteLoadingRI.a = 0.99999f;
}

Scene* SceneManager::GetActiveScene()
{
	return curScene;
}

void SceneManager::AddScene(const std::wstring& _name, Scene* _newScene)
{
	auto sf = sceneMap.find(_name);
	if (sf != sceneMap.end())
		RemoveScene(_name);

	sceneMap.insert(make_pair(_name, _newScene));
}

void SceneManager::ChangeScene(const std::wstring& _name)
{
	auto sf = sceneMap.find(_name);
	if (sf != sceneMap.end())
		nextScene = sf->second;
}

void SceneManager::RemoveScene(const std::wstring& _name)
{
	auto sf = sceneMap.find(_name);
	if (sf != sceneMap.end())
	{
		delete sf->second;
		sceneMap.erase(_name);
	}
}

void SceneManager::Update(float _deltaTime)
{
	isResetDeltaTime = false;
	if (nextScene)
	{
		spriteLoadingRI.a += _deltaTime * 2.0f;
		if (spriteLoadingRI.a >= 1.0f)
		{
			spriteLoadingRI.a = 1.0f;
			curScene = nextScene;
			curScene->OnActiveScene();
			isResetDeltaTime = true;
			nextScene = nullptr;
		}
	}
	else
	{
		spriteLoadingRI.a -= _deltaTime * 2.0f;
		if (spriteLoadingRI.a <= 0.0f)
			spriteLoadingRI.a = 0.0f;
	}

	spriteLoading.Update(_deltaTime);

	if (curScene)
		curScene->Update(_deltaTime);
}

void SceneManager::FixedUpdate(float _fixedDeltaTime)
{
	if (curScene)
		curScene->FixedUpdate(_fixedDeltaTime);
}

void SceneManager::Render()
{
	if (curScene)
		curScene->Render();
}

void SceneManager::UiRender()
{
	if (curScene)
		curScene->UiRender();

	spriteLoading.Render(spriteLoadingRI);
}
