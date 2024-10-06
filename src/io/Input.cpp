#include "Input.h"
#include <GLFW/glfw3.h>

std::unordered_map<int, bool> Input::keys;
std::unordered_map<int, bool> Input::keysPressedLastFrame;
std::unordered_map<int, bool> Input::mouseButtons;
std::unordered_map<int, bool> Input::mouseButtonsPressedLastFrame;

double Input::mouseX = 0;
double Input::mouseY = 0;

void Input::Initialize(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		keys[key] = true;
		keysPressedLastFrame[key] = true;
	} else if (action == GLFW_RELEASE) {
		keys[key] = false;
		keysPressedLastFrame[key] = false;
	}
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		mouseButtons[button] = true;
		mouseButtonsPressedLastFrame[button] = true;
	} else if (action == GLFW_RELEASE)
	{
		mouseButtons[button] = false;
	}
}

void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	mouseX = xpos;
	mouseY = ypos;
}

bool Input::IsKeyPressed(int key) {
	return keys[key];
}

bool Input::IsKeyDown(int key) {
	if (keysPressedLastFrame[key])
	{
		keysPressedLastFrame[key] = false;
		return true;
	} return false;
}

bool Input::IsMouseButtonPressed(int button)
{
	return mouseButtons[button];
}

bool Input::IsMouseButtonReleased(int button) {
	if (!mouseButtons[button] && mouseButtonsPressedLastFrame[button])
		return true;
	return false;
}

bool Input::IsMouseButtonDown(int button) {
	return mouseButtons[button];
}

double Input::GetMouseX()
{
	return mouseX;
}

double Input::GetMouseY()
{
	return mouseY;
}

void Input::EndFrame() {
	// Reset pressed states for next frame
	for (int i = 0; i < 3; ++i) {
		mouseButtonsPressedLastFrame[i] = mouseButtons[i];
	}
}