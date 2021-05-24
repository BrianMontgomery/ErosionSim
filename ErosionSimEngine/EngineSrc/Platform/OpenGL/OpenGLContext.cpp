#include "ErosionSimPCH.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Eros {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		EROSIONSIM_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		EROSIONSIM_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EROSIONSIM_CORE_ASSERT(status, "Failed to initialize Glad!");

		EROSIONSIM_CORE_INFO("OpenGL Info:");
		EROSIONSIM_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		EROSIONSIM_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		EROSIONSIM_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		EROSIONSIM_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 4), "Eros requires at least OpenGL version 4.4!");
	}

	void OpenGLContext::SwapBuffers()
	{
		EROSIONSIM_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}