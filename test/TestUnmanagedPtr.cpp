
#include <UnmanagedPtr.h>
#include "Helpers.h"
using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace Unmanagedpp;

namespace Test
{
	[TestClass]
	public ref class UnmanagedPtrTests
	{
	public:
		[TestMethod]
		void TestDereference()
		{
			int* a = new int;
			*a = 25;

			UnmanagedPtr<int> ptr(a);

			Assert::AreEqual(*ptr, 25);
		}

		[TestMethod]
		void TestAssignment()
		{
			int* a = new int;
			int* b = new int;

			*a = 100;
			*b = 200;

			UnmanagedPtr<int> ptr(a);

			ptr = b;

			Assert::AreEqual(*ptr, 200);
		}


		[TestMethod]
		void TestNullptr()
		{
			UnmanagedPtr<int> ptr;

			Assert::IsTrue(ptr.Ptr == nullptr);

		}

		[TestMethod]
		void TestBool()
		{
			UnmanagedPtr<int> ptr;

			Assert::IsFalse((bool)ptr);

			ptr = new int;

			Assert::IsTrue((bool)ptr);
		}

		[TestMethod]
		void TestDestroy()
		{
			bool aDestroyed = false, bDestroyed = false;
			auto a = new NotifyOnDestroy(aDestroyed);
			auto b = new NotifyOnDestroy(bDestroyed);

			{
				UnmanagedPtr<NotifyOnDestroy> ptr(a);
				ptr = b;
			}

			Assert::IsTrue(aDestroyed);
			Assert::IsTrue(bDestroyed);

		}

		[TestMethod]
		void TestArrow()
		{
			UnmanagedPtr<Reflect<int>> ptr(new Reflect<int>(88));

			Assert::AreEqual(ptr->get(), 88);
		}

		[TestMethod]
		void TestEquals()
		{
			int* a = new int;

			UnmanagedPtr<int> ptr(a);

			Assert::IsTrue(ptr == a);

		}

	};


}
