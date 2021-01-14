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

		// Creates a handle to an empty resource.
		// The resource is created (via an appropriate glCreateX call)
		// when required (when buffer data is provided / texture is loaded / shader program is loaded 
		// for the first time). Once a handle acquires the resource it cannot be used to handle another resource.
		NoCopy()
			: resource(T())
		{
		}

		NoCopy(const NoCopy<T>&) = delete;

		// Moves the handle from src to current object. Makes the src handle an empty resource
		NoCopy(NoCopy<T>&& src) noexcept 
			: resource(*src.Get())
		{
			src->ID = 0;
		}

		~NoCopy() { resource.Free(); }

		NoCopy<T>& operator=(const NoCopy<T>&) = delete;

		// Releases the currently owned handle.
		// Moves the handle from rhs to current object. Makes the rhs handle an empty resource
		NoCopy<T>& operator=(NoCopy<T>&& rhs)
		{
			resource.Free();
			resource.CopyFrom(*rhs.Get());
			rhs->ID = 0;

			return *this;
		}

		T* operator->() { return Get(); }
		T& operator*() { return *Get(); }

		T* Get() { return &resource; }

	private:
		mutable T resource;
	};

}