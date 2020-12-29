#pragma once

namespace Gray
{
	enum class RBType //Render buffer Type
	{
		StencilRB,
		DepthRB,
		DepthStencilRB
	};

	class RenderBuffer
	{
	public:
		RenderBuffer();
		RenderBuffer(const RenderBuffer&) = delete;
		RenderBuffer(RenderBuffer&&) noexcept;

		~RenderBuffer();

		RenderBuffer& operator=(const RenderBuffer&) = delete;

		void CreateBuffer(RBType type, int width, int height) const;
		void Bind() const;
		void Unbind() const;
		uint GetID() const;

	private:
		uint ID;
	};

	uint RBTypeToUINT(RBType type);
}