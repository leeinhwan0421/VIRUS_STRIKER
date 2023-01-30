#pragma once

class Sound
{
private:

	int soundIDX = 0;
	int curSound = 0;
	int szSound = 0;

public:

	Sound(std::wstring _pathWithName, int _szSound);
	~Sound();

	void Play(bool _loop);
	void Stop();
	void SetVolume(int _volume);

};

class SoundManager : public Singleton<SoundManager>
{
private:

	std::map<std::wstring, Sound*> sounds;

public:

	void Create(std::wstring _pathWithName, int _szSound);
	void Play(std::wstring _pathWithName, bool _loop = false);
	void Stop(std::wstring _pathWithName);
	void StopAll();

	/* 0 ~ 1000 */
	void SetVolume(std::wstring _pathWithName, int _volume);

};