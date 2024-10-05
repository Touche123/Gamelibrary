#include "platform_glfw.h"

bool GLFWPlatform::Init() {
	if (!glfwInit()) {
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1600, 900, "GLFW Window", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Set the user pointer to 'this' instance so we can access it in the static callback
	glfwSetWindowUserPointer(window, this);

	// Set the framebuffer size callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	return true;
}

void GLFWPlatform::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Get the GLFWPlatform instance from the user pointer
	GLFWPlatform* platform = static_cast<GLFWPlatform*>(glfwGetWindowUserPointer(window));

	if (platform) {
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		// 
		// Update the viewport and platform's screen size
		glViewport(0, 0, width, height);
		platform->screen_width = width;
		platform->screen_height = height;
	}
}

void GLFWPlatform::PollEvents() {
	glfwPollEvents();

	auto currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void GLFWPlatform::SwapBuffers() {
	glfwSwapBuffers(window);
}

bool GLFWPlatform::ShouldClose() {
	return glfwWindowShouldClose(window);
}

void GLFWPlatform::GetWindowSize(int& width, int& height) {
	glfwGetWindowSize(window, &width, &height);
}

float GLFWPlatform::GetDeltaTime() {
	return deltaTime;
}

GLFWPlatform::~GLFWPlatform() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

