#include "engine_pch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "../../Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case Renderer::API::None:
			{
				ENGINE_CORE_ASSERT(0, "RenderAPI: none");
			}
			case Renderer::API::OpenGL:
			{
				return new OpenGLVertexArray();
			}
		}
		ENGINE_CORE_ASSERT(0, "unknown render API !");
		return nullptr;
	}
}