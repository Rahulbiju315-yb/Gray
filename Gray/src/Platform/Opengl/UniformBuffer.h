#pragma once

#include "NoCopy.h"
#include "Shared.h"
#include "WeakRef.h"

namespace Gray
{
	class UniformBuffer
	{
	public:
		void Bind();
		void Unbind();

	private:
		uint id;

		UniformBuffer();

		void Free();
		void CopyFrom(const UniformBuffer& src);

		friend class NoCopy<UniformBuffer>;
		friend class Shared<UniformBuffer>;
		friend class WeakRef<UniformBuffer>;
	};
}