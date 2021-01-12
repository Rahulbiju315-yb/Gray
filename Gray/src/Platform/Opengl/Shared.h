#pragma once

#include <utility>
namespace Gray
{
	// A handle to a shared (possibly empty) opengl resource.
	// The sharing is implemented via reference counting.
	// The shared resource gets deleted when no handle points to the resource.
	// Sharing occurs through copy construction / copy assignment / move construction / move assignment.
	// An empty resource cannot be shared. Attempting to copy/move construct from an empty resource will be 
	// equivalent to calling the default constructor and copy/move assigning an empty resoruce will do nothing.

	template<class T>
	class Shared
	{
	public:
		Shared() 
			: resource(T())
		{			
			refCount = new int;
			*refCount = 1; 
		}


		//Copy Constructs a resource. RefCount incremented.
		//Moving is same as copying. 
		Shared(const Shared<T>& src)
		{
			if (src->ID != 0)
			{
				refCount = src.refCount;
				resource.CopyFrom(src.resource);
				(*refCount)++;
			}
			else
			{
				refCount = new int;
				*refCount = 1; 
			}
		}
		Shared(Shared<T>&& src)
			: resource(T())
		{
			if (src->ID != 0)
			{
				refCount = src.refCount;
				resource.CopyFrom(src.resource);
				(*refCount)++;
			}
			else
			{
				refCount = new int;
				*refCount = 1; 
			}
		}

		//Releases ownership
		~Shared() { ReleaseOwnership(); }

		//Releases ownership of current resource.
		//Gains a shared ownership of the resource in src.
		//Moving same as copying.
		Shared<T>& operator=(const Shared<T>& src)
		{
			if (&src != this && src->ID != 0)
			{
				ReleaseOwnership();

				resource.CopyFrom(src.resource);

				refCount = src.refCount;
				(*refCount)++;
			}
			return *this;
		}

		Shared<T>& operator=(Shared<T>&&  src) noexcept
		{
			if (&src != this  && src->ID != 0)
			{
				ReleaseOwnership();

				resource.CopyFrom(src.resource);

				refCount = src.refCount;
				(*refCount)++;
			}
			return *this;
		}

		T* operator->() const
		{
			return &resource;
		}

		T& operator*() const
		{
			return resource;
		}

		T* Get() const
		{
			T* ptr = &resource;
			return ptr;
		}

		//Releases ownsership of current resource.
		//Deletes resources if no other object resferences the same resource.
		void ReleaseOwnership()
		{
			if (*refCount == 1)
			{
				resource.Free();
				delete refCount;
			}
			else
			{
				*refCount--;
			}
		}

	private:
		mutable T resource;
		int* refCount;
	};
}