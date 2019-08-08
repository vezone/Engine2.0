#pragma once

#include "Core.h"
#include "Window.h"
#include "Engine/LayerStack.h"
#include "Engine/imgui/ImGuiLayer.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

namespace Engine {
	
	class ENGINE_API Application
	{
	private:
		bool m_Running;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

	private:
		static Application* s_Instance;
		bool OnWindowClosed(WindowClosedEvent& event);
		
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	};

	Application* CreateApplication();

}