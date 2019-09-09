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

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		
		//OpenGLVertexBuffer
		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f 
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, 9 * sizeof(float)));
		m_VertexBuffer->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		
		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_IndexBuffer->Bind();

		std::string vertex = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			
			out vec4 o_Position;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
				o_Position = gl_Position;
			}	
		)";

		std::string fragment = R"(
			#version 330 core
		
			layout(location = 0) out vec4 o_Color;
			
			in vec4 o_Position;

			void main()
			{
				o_Color = 0.5 * o_Position + 0.5;
			}	
		)";

		m_Shader.reset(new Shader(vertex, fragment));
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

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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