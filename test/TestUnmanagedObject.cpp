
#include <UnmanagedObject.h>
#include "Helpers.h"
using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace Unmanagedpp;

namespace Test
{
	[TestClass]
	public ref class UnmanagedObjectTests
	{
	public:
		[TestMethod]
		void TestReference()
		{
			UnmanagedObject<Reflect<int>> obj(Reflect<int>(14));

			Assert::AreEqual((*obj).get(), 14);						
		}

		[TestMethod]
		void TestAssignment()
		{
			UnmanagedObject<Reflect<int>> obj(Reflect<int>(0));

			obj = Reflect<int>(81);

			Assert::AreEqual((*obj).get(), 81);
		}

		[TestMethod]
		void TestMemory()
		{
			bool aDestroyed = false, bDestroyed = false;
			{
				std::shared_ptr<NotifyOnDestroy> a, b;

				a.reset(new NotifyOnDestroy(aDestroyed));
				b.reset(new NotifyOnDestroy(bDestroyed));

				stl::SharedPtr<NotifyOnDestroy> obj(a);

				obj = b;

				obj = a;

				obj = a;

				stl::SharedPtr<NotifyOnDestroy> obj2(obj);

				obj2 = b;

				Assert::IsFalse(aDestroyed);
				Assert::IsFalse(bDestroyed);
			}

			Assert::IsTrue(aDestroyed);
			Assert::IsTrue(bDestroyed);
		}

		[TestMethod]
		void TestArrow()
		{
			stl::SharedPtr<Reflect<int>> obj( std::shared_ptr<Reflect<int>>(new Reflect<int>(33)));

			Assert::AreEqual(obj->get(), 33);
		}

	};

}
