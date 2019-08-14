#include "engine_pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Engine
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ENGINE_ASSERT(windowHandle, "window handle is null !");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_ASSERT(status, "Failed to init GLAD");

		ENGINE_INFO("OpenGL info:\n\t\tGraphic device: {0}\n\t\tRenderer driver: {1}\n\t\tGL version: {2}\n", 
			glGetString(GL_RENDERER),
			glGetString(GL_VENDOR), 
			glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}