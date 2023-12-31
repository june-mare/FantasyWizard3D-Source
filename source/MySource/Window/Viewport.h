#pragma once
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>

class Viewport
{
private:
	Viewport()
		:x(0), y(0), width(1920), height(1280) {};
	Viewport(const Viewport&) = delete;
	Viewport& operator=(const Viewport&) = delete;
	~Viewport() = default;
	int x;      // ķšXĀW
	int y;      // ķšYĀW
	int width;  // 
	int height; // ģ
public:
	static Viewport& Instance()noexcept
	{
		static Viewport instance;
		return instance;
	}
	/*
	*
	*/
	glm::vec4 GetViewport()const noexcept;
	glm::vec2 GetViewSize()noexcept;
	int GetViewSizeX()noexcept;
	int GetViewSizeY()noexcept;
	float GetWindowAspect() noexcept;
	void ChangeScreenSize(int x, int y, int w, int h);
	void LoadScreenSize()const noexcept;
};