
#include <MonitorGuard.h>
#include "Helpers.h"

using namespace System;
using namespace System::Threading;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace Unmanagedpp;

namespace Test
{

	public ref class Counter
	{
	private:
		volatile int* shared;
		int times;
		Object^ lock;
		Thread^ thread;

		void count()
		{
			for (int i = 0; i < times; i++)
			{
				MonitorGuard guard(lock);

				int current = *shared;
				// Introduce delay to make sure something break if we haven't got exclusive access to shared
				Thread::Sleep(10); 
				*shared = current + 1;
			}
		}

	public:

		Counter(int* shared, int times, Object^ lock):
			shared(shared), times(times), lock(lock)
		{
			thread = gcnew Thread(gcnew ThreadStart(this, &Counter::count));
		}

		void Start()
		{
			thread->Start();
		}

		void Join()
		{
			thread->Join();
		}
	};


	[TestClass]
	public ref class MonitorGuardTests
	{
	public:
		[TestMethod]
		void TestIntegrity()
		{

			array<Counter^>^ counters = gcnew array<Counter^>(10);

			int count = 0;
			Object^ lock = gcnew Object();

			for (int i = 0; i < counters->Length; i++)
			{
				Counter^ counter = gcnew Counter(&count, 10, lock);
				counter->Start();
				counters[i] = counter;
			}

			for (int i = 0; i < counters->Length; i++)
			{
				counters[i]->Join();
			}

			// 10 counters should have counted up 10 times each.
			Assert::AreEqual(100, count);
		}

	};

}
