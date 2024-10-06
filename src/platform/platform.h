#pragma once

class Platform {
public:
	virtual ~Platform() = default;
	virtual bool Init() = 0;
	virtual void PollEvents() = 0;
	virtual void SwapBuffers() = 0;
	virtual bool ShouldClose() = 0;
	virtual void GetWindowSize(int& width, int& height) = 0;
	virtual float GetDeltaTime() = 0;

protected:
	int screen_width;
	int screen_height;
};