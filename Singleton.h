#pragma once

// singleton pattern

template <typename T>
class Singleton
{
protected:

	Singleton() {}
	Singleton(const Singleton&) = delete;
	void operator = (const Singleton&) = delete;

public:

	static T& GetInstance()
	{
		static T* instance = new T();
		return *instance;
	}
};
