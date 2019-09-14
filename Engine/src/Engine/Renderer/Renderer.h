#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include <glm/glm.hpp>
namespace Engine
{
	class Renderer
	{
	private:
		static glm::mat4 m_ViewProjectionMatrix;
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}