#include <Engine.h>

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		ENGINE_INFO("Example ctor");
	}

	void OnUpdate() override
	{
		ENGINE_INFO("Example: OnUpdate()");
	}

	void OnEvent(Engine::Event& event) override
	{
		ENGINE_TRACE("{0}", event.GetName());
	}

};

class Sandbox : public Engine::Application
{
public:
	Sandbox() 
	{
		ENGINE_INFO("Sandbox ctor");
		PushLayer(new ExampleLayer());
		PushOverlay(new Engine::ImGuiLayer());
	}

	~Sandbox() 
	{

	}

};


Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}
