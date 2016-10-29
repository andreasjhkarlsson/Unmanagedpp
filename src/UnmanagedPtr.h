#pragma once

namespace Unmanagedpp
{
	template <typename T>
	public ref class UnmanagedPtr
	{
	private:
		T* ptr;
		UnmanagedPtr(const UnmanagedPtr<T>% rhs);
	public:
		UnmanagedPtr(T* ptr) : ptr(ptr)
		{

		}

		UnmanagedPtr() : ptr(nullptr)
		{

		}

		~UnmanagedPtr()
		{
			(*this).!UnmanagedPtr();
		}

		!UnmanagedPtr()
		{
			Reset();
		}

		void Reset()
		{
			Reset(nullptr);
		}

		void Reset(T* newPtr)
		{
			if (ptr)
				delete ptr;
			ptr = newPtr;
		}

		property T* Ptr
		{
			T* get()
			{
				return ptr;
			}
		}

		T* operator-> ()
		{
			return Ptr;
		}

		UnmanagedPtr<T>% operator=(T* rhs)
		{
			Reset(rhs);
			return *this;
		}

		bool operator==(T* rhs)
		{
			return ptr == rhs;
		}

		explicit operator bool()
		{
			return Ptr != nullptr;
		}

		static const T& operator*(const UnmanagedPtr<T>% rhs)
		{
			return *rhs.Ptr;
		}

		static T& operator*(UnmanagedPtr<T>% rhs)
		{
			return *rhs.Ptr;
		}
	};

}