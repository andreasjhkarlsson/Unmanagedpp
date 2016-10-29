#pragma once

namespace Test
{
	class NotifyOnDestroy
	{
	private:
		bool& destroyed;
	public:
		NotifyOnDestroy(bool& onDestroy) : destroyed(onDestroy)
		{
			destroyed = false;
		}
		~NotifyOnDestroy()
		{
			destroyed = true;
		}
	};

	template <typename T>
	class Reflect
	{
	private:
		T data;
	public:
		Reflect(T data) : data(data) {}
		T get() { return data; }
	};
}