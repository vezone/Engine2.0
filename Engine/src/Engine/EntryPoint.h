#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	ENGINE_CORE_WARN("Testing client logger!");
	ENGINE_INFO("2+3 = {0}", 5);

	auto application = Engine::CreateApplication();
	application->Run();
	delete application;
	return 0;
}

#endif

