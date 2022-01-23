#pragma once
#include <glm/glm.hpp>
#include <windows.h>

class Gui {

public:
	Gui() {};
	~Gui() {};

	void Initialize(HWND* hwnd);
	void Shutdown();
	void Render();

private:
	bool _showDemoWindow = true;
};