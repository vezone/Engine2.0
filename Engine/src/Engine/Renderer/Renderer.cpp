#include "engine_pch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Engine
{
	glm::mat4 Renderer::m_ViewProjectionMatrix;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		Renderer::m_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", Renderer::m_ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}