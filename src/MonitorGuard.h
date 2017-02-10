#pragma once

namespace Unmanagedpp
{
	using namespace System;
	using namespace System::Threading;

	// Wraps a IUknown (COM) interface pointer
	// in a ref class to automatically handle AddRef/Release calls.
	public ref class MonitorGuard
	{
	private:
		Object^ obj;
	public:
		MonitorGuard(Object^ obj) : obj(obj)
		{
			if (obj)
				Monitor::Enter(obj);
		}

		~MonitorGuard()
		{
			(*this).!MonitorGuard();
		}

		!MonitorGuard()
		{
			if (obj)
				Monitor::Exit(obj);
			obj = nullptr;
		}
	};
}