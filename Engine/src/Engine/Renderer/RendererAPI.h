#pragma once

namespace Engine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	private:
		static API s_API;
	public:
		virtual void Clear() = 0;

		inline static API GetAPI() { return s_API; }
	};

}