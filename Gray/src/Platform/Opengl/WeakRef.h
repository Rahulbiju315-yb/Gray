#pragma once

#include <utility>

namespace Gray
{
	// A reference to a handle. WeakRef does not own the resource,
	// neither does it share ownership with any other handle. It merely
	// reference another handle to a (possibly empty or non existent) resource.

	// Note that unlike in a NoCopy or Shared handle, the resource maybe non existent,
	// ie in a deleted state. Therefore a WeakRef to a resource must be used only in a 
	// scope where the said resource is guaranteed (by the scope of its other handle(s)) 
	// to exist. Due to the uncertainty of existence of a resource handled by a WeakRef,
	// only const operation maybe performed on a resource from a WeakRef. This implies that
	// one cannot modify the state of the resource via a WeakRef. To be able to do this, use
	// a NoCopy or Shared instead.

	template<class T>
	class WeakRef
	{
	public:
		WeakRef() 
			: resource(T())
		{
		}

		WeakRef(const T* resPtr) 
			: resource(*resPtr)
		{
		}

		WeakRef(const NoCopy<T>& handle) 
			: resource(*handle.Get())
		{
			
		}

		WeakRef(const Shared<T> handle)
			: resource(*handle.Get())
		{

		}
		
		WeakRef(const WeakRef<T>&) = default;
		WeakRef(WeakRef&&) = default;
		WeakRef& operator=(const WeakRef&) = default;
		WeakRef& operator=(WeakRef&&) = default;

		T& operator*() const { return resource; }
		T* Get() const { return &resource; }
		T* operator->() const { return Get(); }

	private:
		T resource;
	};
}