#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "platform.h"

class GLFWPlatform : public Platform {

public:
	bool Init() override;
	void PollEvents() override;
	void SwapBuffers() override;
	bool ShouldClose() override;
	void GetWindowSize(int& width, int& height) override;
	float GetDeltaTime() override;
	GLFWwindow* GetWindow() { return window; }
	~GLFWPlatform() override;

private:
	GLFWwindow* window;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	float deltaTime, currentFrame, lastFrame;
};