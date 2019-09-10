#include "engine_pch.h"

#include "Application.h"
#include "Input.h"

#include <Glad/glad.h>

namespace Engine {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		//NOTE: for now
		ENGINE_CORE_ASSERT(s_Instance == NULL, "Applciation already exists!");
		s_Instance = this;
		m_Running = true;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		
		m_TriangleVertexArray.reset(VertexArray::Create());

		//OpenGLVertexBuffer
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.2f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		//buffer layout
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float4, "a_Color" }
		};
		triangleVertexBuffer->SetLayout(layout);
		
			m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);
		
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer>  triangleIndexBuffer;
		triangleIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
		triangleIndexBuffer->Bind();
		m_TriangleVertexArray->AddIndexBuffer(triangleIndexBuffer);

		m_SquareVertexArray.reset(VertexArray::Create());
		float squareVertices[3 * 3] =
		{
			-0.9f, -0.9f, 0.0f,
			-0.7f,  0.9f, 0.0f,
			-0.5f, -0.9f, 0.0f
		};
		std::shared_ptr<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		BufferLayout squareLayout =
		{
			{ ShaderDataType::Float3, "a_Position" }
		};
		squareVertexBuffer->SetLayout(squareLayout);
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
		
		uint32_t squareIndices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
		squareIndexBuffer->Bind();
		m_SquareVertexArray->AddIndexBuffer(squareIndexBuffer);

		std::string vertex = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec4 o_Position;
			out vec4 o_aColor;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
				o_Position = gl_Position;
				o_aColor = a_Color;
			}	
		)";

		std::string fragment = R"(
			#version 330 core
		
			layout(location = 0) out vec4 o_Color;
			
			in vec4 o_Position;
			in vec4 o_aColor;
			
			void main()
			{
				o_Color = 0.5 * o_Position + 0.5;
				o_Color = o_aColor;
			}	
		)";

		m_Shader.reset(new Shader(vertex, fragment));

		std::string vertexSquare = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			
			out vec4 o_Position;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
				o_Position = gl_Position;
			}	
		)";

		std::string fragmentSquare = R"(
			#version 330 core
		
			layout(location = 0) out vec4 o_Color;
			
			in vec4 o_Position;
			
			void main()
			{
				o_Color = 0.5 * o_Position + 0.5;
			}
		)";

		m_ShaderSquare.reset(new Shader(vertexSquare, fragmentSquare));
	}	 

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClosed));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
			{
				break;
			}
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClosed(WindowClosedEvent& event)
	{
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			m_Shader->Bind();
			m_TriangleVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_TriangleVertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
			
			m_ShaderSquare->Bind();
			m_SquareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			auto [x, y] = Input::GetMousePosition();
			//ENGINE_CORE_TRACE("{0}, {1}", x, y);

			if (Input::IsKeyPressed(70))
				ENGINE_CORE_TRACE("F pressed");

			m_Window->OnUpdate();
		}
	}
}