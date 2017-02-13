
#include <ComPtr.h>
#include <Windows.h>
#include "Helpers.h"
using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace Unmanagedpp;

namespace Test
{

	class TestComObject : public IUnknown
	{
	private:
		ULONG refCount = 0;
	public:
		STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
		{
			return E_ABORT; // N/A
		}
		STDMETHODIMP_(ULONG) AddRef()
		{
			return ++refCount;
		}
		STDMETHODIMP_(ULONG) Release()
		{
			ULONG newRefCount = --refCount;
			if (newRefCount == 0)
				delete this;
			return newRefCount;
		}

		int RefCount()
		{
			return refCount;
		}

		int OneLess(int n)
		{
			return n - 1;
		}
	};


	[TestClass]
	public ref class ComPtrTests
	{
	public:
		[TestMethod]
		void TestReference()
		{
			TestComObject *a = new TestComObject();
			ComPtr<TestComObject> b(a);
			Assert::IsTrue(a == b.Ptr);
		}

		[TestMethod]
		void TestArrow()
		{
			ComPtr<TestComObject> b(new TestComObject());
			Assert::AreEqual(b->OneLess(10), 9);
		}

		[TestMethod]
		void TestRefCount()
		{
			TestComObject *a = new TestComObject();
			{
				ComPtr<TestComObject> b(a);
				Assert::AreEqual(a->RefCount(), 1);

				a->AddRef();
				b = nullptr;
				Assert::AreEqual(a->RefCount(), 1);

				b = a;
				Assert::AreEqual(a->RefCount(), 2);
			}
			Assert::AreEqual(a->RefCount(), 1);
		}

		[TestMethod]
		void TestOutPtr()
		{
			ComPtr<TestComObject> b;

			*b.Out = new TestComObject();

			Assert::AreEqual(b->OneLess(4), 3);
		}

		[TestMethod]
		void TestEmpty()
		{
			ComPtr<TestComObject> b;

			Assert::IsTrue(b.Ptr == nullptr);
		}

		[TestMethod]
		void TestEquals()
		{
			auto a = new TestComObject();
			ComPtr<TestComObject> b(a);

			Assert::IsTrue(b == a);
		}

		[TestMethod]
		void TestBool()
		{
			auto a = new TestComObject();
			ComPtr<TestComObject> b;

			Assert::IsFalse((bool)b);

			b = a;

			Assert::IsTrue((bool)b);			
		}

		[TestMethod]
		void TestCopy()
		{
			auto a = new TestComObject();

			ComPtr<TestComObject> b(a);

			ComPtr<TestComObject> c = b;

			Assert::AreEqual(2, a->RefCount());
			Assert::IsTrue(b.Ptr == c.Ptr);
		}

		[TestMethod]
		void TestConversion()
		{
			auto a = new TestComObject();
			ComPtr<TestComObject> b(a);

			Assert::IsTrue(a == (TestComObject*)b);
		}

	};

}
