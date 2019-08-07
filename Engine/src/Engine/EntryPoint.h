#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	ENGINE_CORE_INFO("Welcome to Engine!");

	auto application = Engine::CreateApplication();
	application->Run();
	delete application;
	return 0;
}

#endif

