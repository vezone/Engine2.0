#include "engine_pch.h"
#include "Buffer.h"
#include "Engine/Renderer//Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{

	VertexBuffer* Engine::VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
					ENGINE_CORE_ASSERT(0, "RenderAPI: none");
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLVertexBuffer(vertices, size);
			}
		}
		ENGINE_CORE_ASSERT(0, "unknown render API !");
		return nullptr;
	}

	IndexBuffer* Engine::IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				ENGINE_CORE_ASSERT(0, "RenderAPI: none");
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLIndexBuffer(indices, count);
			}
		}
		ENGINE_CORE_ASSERT(0, "unknown render API !");
		return nullptr;
	}

}