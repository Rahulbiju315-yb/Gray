#pragma once

#include "EmptyStates.h"
#include <utility>

namespace Gray
{
	// A reference to a (possibly invalid) handle. WeakRef does not own the resource,
	// neither does it share ownership with any other handle. It merely
	// reference another handle to a (possibly non existent) resource.

	// Note that unlike in a NoCopy or Shared handle, the resource maybe non existent,
	// ie in a deleted state. Therefore a WeakRef to a resource must be used only in a 
	// scope where the said resource is guaranteed (by the scope of its owner handle(s)) 
	// to exist.

	template<class T>
	class WeakRef
	{
	public:
		WeakRef() 
			: WeakRef<T>( Empty<T>() )
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

		T& operator*() const 
		{ 
			assert(!(resource.ID == ( (*Empty<T>()).ID )));
			return resource; 
		}

		T* Get() const 
		{ 
			assert(!(resource.ID == ( (*Empty<T>()).ID )));
			return &resource; 
		}

		T* operator->() const 
		{ 
			return Get(); 
		}

	private:
		mutable T resource;
	};
}