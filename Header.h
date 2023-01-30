#pragma once

#pragma warning (disable : 26495)
#pragma warning (disable : 4100)

#include <Windows.h>
#include <vector>
#include <map>
#include <string>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <crtdbg.h>
#include <queue>
#include <thread>
#include <random>
#include <ctime>

// file �����ؾ���,, DirectX sdk version ����Ʈ ��Ű�� ��!!!
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
// ���̺귯�� ���� C++ ��Ŀ ������ !!
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib")

#define SAFE_RELEASE(x) if (x) x->Release()

#include "Singleton.h"
#include "Direct3D.h"
#include "Sound.h"
#include "Texture.h"
#include "Sprite.h"
#include "MathUtility.h"
#include "Input.h"

#include "Object.h"
#include "Map.h"
#include "Entity.h"
#include "Enemy.h"
#include "Item.h"
#include "Player.h"
#include "Boss.h"
#include "Virus_Speed.h"
#include "Virus_Big.h"
#include "Virus_Flash.h"

// UI Object
#include "Number.h"
#include "Str.h"
#include "Heart.h"
// ��¥ �ƹ��ų� ����ֱ⸸ �ϴ� Ui 
#include "UiSprite.h"

// Item
#include "SpeedItem.h"
#include "HealItem.h"
#include "invincible.h"
#include "DefenseItem.h"
#include "RandomItem.h"

#include "Scene.h"
#include "GameScene.h"
#include "RankScene.h"
#include "TitleScene.h"
#include "CreditScene.h"
#include "IntroScene.h"
#include "HelpScene.h"
#include "EndScene.h"