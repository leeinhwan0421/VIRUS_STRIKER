#pragma once

enum InputState
{
	NONE,
	DOWN,
	PRESS,
	UP
};

class Input : public Singleton<Input>
{
public:

	bool IfKeyPressed = false;
	int keyStates[256] = { };

	bool IsKeyPressed()
	{
		IfKeyPressed = true;
	}

	void SetKeyState(int _key, InputState _state);
	InputState GetKeyState(int _key);
	void KeyUpdate();

};