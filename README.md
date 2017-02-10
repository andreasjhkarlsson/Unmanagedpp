# Unmanaged++

C++/CLI is great for wrapping and consuming regular C++ libraries for use in .net.

However, C++/CLI places some constraints on data type usage. For example, only managed objects and POD-types may be used as fields in managed classes.

This library provides helpers for wrapping C++ types inside C++/CLI compatible types.

## Example

```C++
#include <string>
#include <iostream>
#include <UnmanagedPtr.h>
#include <UnmanagedObject.h>

using namespace Unmanagedpp;

public ref class MyDotNetClass
{
private:
	UnmanagedPtr<std::string> ownedPtrString;
	UnmanagedObject<std::string> ownedString;
	stl::SharedPtr<std::string> sharedString;
public:
	MyDotNetClass() :
		ownedPtrString(new std::string("C++")),
		ownedString(std::string("CLI")),
		sharedString(std::shared_ptr<std::string>(new std::string("C++/CLI")))
	{
		std::cout << ownedPtrString->c_str() << std::endl;
		std::cout << ownedString.Obj.c_str() << std::endl;
		std::cout << sharedString->c_str() << std::endl;
	}
};
```

For more usage, see the test project.

## Setup

The library is currently header only, so including the headers is the only step needed.

## License

The library is licensed under the MIT license.
