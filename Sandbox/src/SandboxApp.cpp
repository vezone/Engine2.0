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
		if (Engine::Input::IsKeyPressed(ENGINE_KEY_T))
		{
			ENGINE_CORE_ERROR("T is pressed from EXAMPLE Layer *ghm-ghm* *sigh*");
		}
	}

	void OnEvent(Engine::Event& event) override
	{
		//ENGINE_TRACE("{0}", event.GetName());
	}

};

class Sandbox : public Engine::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() 
	{

	}

};


Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}
