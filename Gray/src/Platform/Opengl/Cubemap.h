#pragma once

#include "NoCopy.h"
#include "Shared.h"
#include "WeakRef.h"

namespace Gray
{
	class Cubemap
	{
	public:
		void LoadCubeMap(const std::string& path, const std::string ext, int slot);
		void LoadCubeMap(const std::vector<std::string> paths);
		void LoadCubeMap(const std::string& path, int slot);
		
		void Bind(int slot) const;
		void Unbind() const;

		uint GetID() const;

	private:
		Cubemap();
		Cubemap(const Cubemap&) =  default;
		Cubemap(Cubemap&&) = default;

		Cubemap& operator=(const Cubemap&) = default;
		Cubemap& operator=(Cubemap&&) = default;

		void CopyFrom(const Cubemap& src);
		void Free();

		uint ID;

		friend class NoCopy<Cubemap>;
		friend class Shared<Cubemap>;
		friend class WeakRef<Cubemap>;
	};
}