#include "Header.h"

Sound::Sound(std::wstring _pathWithName, int _szSound)
{
	static int IDX = 0;
	soundIDX = ++IDX;
	szSound = _szSound;
	for (int i = 0; i < _szSound; ++i)
	{
		WCHAR buffer[256];
		swprintf_s(buffer, TEXT("open %s alias %d_%d"), _pathWithName.c_str(), soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
		swprintf_s(buffer, TEXT("play %d_%d from 0"), soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
		swprintf_s(buffer, TEXT("pause %d_%d"), soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
	}
}

Sound::~Sound()
{
	for (int i = 0; i < szSound; ++i)
	{
		WCHAR buffer[256];
		swprintf_s(buffer, TEXT("close %d_%d"), soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
	}
}

void Sound::Play(bool _loop)
{
	WCHAR buffer[255];
	swprintf_s(buffer, L"play %d_%d from 0%s", soundIDX, curSound, _loop ? L" repeat" : L"");
	mciSendString(buffer, 0, 0, 0);
	if (++curSound >= szSound) curSound = 0;
}

void Sound::Stop()
{
	for (int i = 0; i < szSound; ++i)
	{
		WCHAR buffer[255];
		swprintf_s(buffer, L"stop %d_%d", soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
	}
}

void Sound::SetVolume(int _volume)
{
	for (int i = 0; i < szSound; ++i)
	{
		WCHAR buffer[255];
		swprintf_s(buffer, L"setaudio %d_%d volume to %d", soundIDX, i, _volume);
		mciSendString(buffer, 0, 0, 0);
	}
}

void SoundManager::Create(std::wstring _pathWithName, int _szSound)
{
	auto sf = sounds.find(_pathWithName);
	if (sf != sounds.end()) return;
	sounds.insert({ _pathWithName, new Sound({_pathWithName, _szSound }) });
}

void SoundManager::Play(std::wstring _pathWithName, bool _loop)
{
	auto sf = sounds.find(_pathWithName);
	if (sf == sounds.end()) return;
	sf->second->Play(_loop);
}

void SoundManager::Stop(std::wstring _pathWithName)
{
	auto sf = sounds.find(_pathWithName);
	if (sf == sounds.end()) return;
	sf->second->Stop();
}

void SoundManager::StopAll()
{
	for (auto sound : sounds)
		sound.second->Stop();
}

void SoundManager::SetVolume(std::wstring _pathWithName, int _volume)
{
	auto sf = sounds.find(_pathWithName);
	if (sf == sounds.end()) return;
	sf->second->SetVolume(_volume);
}
