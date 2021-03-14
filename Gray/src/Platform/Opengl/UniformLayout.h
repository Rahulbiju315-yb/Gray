#pragma once

namespace Gray
{
	enum class VarType
	{
		Float,
		Int,
		Bool,
		Vec3,
		Vec4,
		Mat4
	};

	class UniformLayout
	{
	public:
		void Push(VarType tpye, const std::string& name);

	private:
		std::unordered_map<std::string, uint> offsetMap;
		uint allignedOffset;
	};
}