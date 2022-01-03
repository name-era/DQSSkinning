#pragma once

class App {
private:
	App(const App&);
	App& operator=(const App&);
public:
	App() {};
	~App() {};
	void Initialize() {};
	void Update(float deltaTime) {};
	void Render(float aspect) {};
	void Shutdown() {};
};