#pragma once

namespace Unmanagedpp
{
	// Wraps a IUknown (COM) interface pointer
	// in a ref class to automatically handle AddRef/Release calls.
	template <typename T>
	public ref class ComPtr
	{
	private:
		// Store a T** instead of a T* so clients can pass
		// a T** to factory methods.
		T** ppIUnknown;
	public:
		ComPtr(T* iunknown) : ppIUnknown(new T*)
		{
			*ppIUnknown = nullptr;
			Reset(iunknown);
		}

		ComPtr() : ppIUnknown(new T*)
		{
			*ppIUnknown = nullptr;
		}

		ComPtr(const ComPtr<T>% rhs): ppIUnknown(new T*)
		{
			*ppIUnknown = nullptr;
			Reset(*rhs.ppIUnknown);
		}

		~ComPtr()
		{
			(*this).!ComPtr();
		}

		!ComPtr()
		{
			Reset();
			delete ppIUnknown;
		}

		void Reset()
		{
			Reset(nullptr);
		}

		// Set the interface pointer.
		void Reset(T* iunknown)
		{
			// Nothing needed if resetting to same object
			if (*ppIUnknown == iunknown)
				return;

			// Release old
			if (*ppIUnknown)
				(*ppIUnknown)->Release();
			// Replace
			*ppIUnknown = iunknown;

			// AddRef new
			if (*ppIUnknown)
				(*ppIUnknown)->AddRef();
		}

		// Many / most COM interfaces are created by passing a 
		// pointer to an interface pointer. This method allows access to such a ptr
		property T** Out
		{
			T** get()
			{
				return ppIUnknown;
			}
		}

		property T* Ptr
		{
			T* get()
			{

				return *ppIUnknown;
			}
		}

		T* operator-> ()
		{
			return *ppIUnknown;
		}

		ComPtr<T>% operator=(T* rhs)
		{
			Reset(rhs);
			return *this;
		}

		static operator T*(ComPtr<T> val) {
			return *val.ppIUnknown;
		}

		bool operator==(T* rhs)
		{
			return *ppIUnknown == rhs;
		}

		explicit operator bool()
		{
			return *ppIUnknown != nullptr;
		}
	};


}