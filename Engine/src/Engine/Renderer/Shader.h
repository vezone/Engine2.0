#pragma once

#include <string>

namespace Engine
{
	class Shader
	{
	private:
		std::string m_Vertex;
		std::string m_Fragment;
		uint32_t m_RendererId;

	public:
		Shader(const std::string& vertex, const std::string& fragment);
		~Shader();

		void Bind() const;
		void Unbind() const;

	};
}