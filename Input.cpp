#include "Header.h"

void Input::SetKeyState(int _key, InputState _state)
{
	keyStates[_key] = _state;
}

InputState Input::GetKeyState(int _key)
{
	return InputState(keyStates[_key]);
}

void Input::KeyUpdate()
{
	for (int i = 0; i < 256; ++i)
	{
		if (keyStates[i] == InputState::DOWN)
			keyStates[i] = InputState::PRESS;

		if (keyStates[i] == InputState::UP)
			keyStates[i] = InputState::NONE;
	}
}
