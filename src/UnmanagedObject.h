#pragma once

#include <memory>

namespace Unmanagedpp
{

	template <typename T>
	public ref class UnmanagedObject
	{
	private:
		T* obj;
	public:

		UnmanagedObject(const T& obj) : obj(new T(obj))
		{

		}

		UnmanagedObject() : obj(new T)
		{

		}

		UnmanagedObject(const UnmanagedObject<T>% other) : obj(new T(*other))
		{
		}

		~UnmanagedObject()
		{
			(*this).!UnmanagedObject();
		}

		!UnmanagedObject()
		{
			delete obj;
		}

		void Reset(const T& newObj)
		{
			*obj = newObj;
		}


		property T& Obj
		{
			T& get()
			{
				return *obj;
			}
		}

		UnmanagedObject<T>% operator=(UnmanagedObject<T>% rhs)
		{
			Reset(*rhs);
			return *this;
		}

		UnmanagedObject<T>% operator=(const T& rhs)
		{
			Reset(rhs);
			return *this;
		}

		T operator->()
		{
			return *obj;
		}

		static T& operator*(UnmanagedObject<T>% rhs)
		{
			return *rhs.obj;
		}
		static const T& operator*(const UnmanagedObject<T>% rhs)
		{
			return *rhs.obj;
		}
	};

	namespace stl
	{
		template <typename T>
		using SharedPtr = UnmanagedObject<std::shared_ptr<T>>;

		template <typename T>
		using UniquePtr = UnmanagedObject<std::unique_ptr<T>>;
	}
}