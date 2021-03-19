#pragma once

#include <utility>

namespace Gray
{
	
	// A handle to a (possibly empty) opengl resource.
	// The handle is non-copyable and when it goes out of scope it deletes the resource along with itself.
	// Therefore copy constructor and copy assignment operator are deleted.
	// Move constructor and move assignment are supported to enable transfer of the handle.

	// Note : an empty resource signifies that its ID is 0.
	template <class T>
	class NoCopy
	{
	public:

		// Creates a handle to a resource T.
		// The resource T is created (via an appropriate glCreateX call)
		// when the constructor of NoCopy<T> gets called. 
		// Once a handle is acquired it cannot changed.
		NoCopy()
			: resource(T())
		{
		}

		NoCopy(const NoCopy<T>&) = delete;

		// Moves constructs the handle from src. Makes the src handle an empty resource
		NoCopy(NoCopy<T>&& src) noexcept 
			: resource(*src.Get())
		{
			src->ID = 0;
		}

		~NoCopy() { resource.Free(); resource.ID = 0; }

		NoCopy<T>& operator=(const NoCopy<T>&) = delete;

		// Releases the currently owned handle.
		// Moves the handle from rhs to current object. Makes the rhs handle an empty resource
		NoCopy<T>& operator=(NoCopy<T>&& rhs) noexcept
		{
			if (resource.ID != rhs->ID)
			{
				resource.Free();
				resource.CopyFrom(*rhs.Get());
				rhs->ID = 0;
			}
			return *this;
		}

		T* operator->() const { return Get(); }
		T& operator*() const { return *Get(); }

		T* Get() const { return &resource; }

	private:
		mutable T resource;
	};

}