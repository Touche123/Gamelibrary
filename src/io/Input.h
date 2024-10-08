#pragma once

#include <unordered_map>

struct GLFWwindow;

class Input {
public:
	static void Initialize(GLFWwindow* window);

	static bool IsKeyPressed(int key);
	static bool IsKeyDown(int key);
	static bool IsMouseButtonPressed(int button);
	static bool IsMouseButtonDown(int button);
	static bool IsMouseButtonReleased(int button);
	static double GetMouseX();
	static double GetMouseY();

	static void EndFrame();
private:
	static std::unordered_map<int, bool> keys;
	static std::unordered_map<int, bool> keysPressedLastFrame;
	static std::unordered_map<int, bool> mouseButtons;
	static std::unordered_map<int, bool> mouseButtonsPressedLastFrame;
	static double mouseX, mouseY;

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
};



