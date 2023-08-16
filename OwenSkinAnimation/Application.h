#pragma once


class Application
{
public:
	inline Application() {}
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	inline virtual ~Application() {}
	inline virtual void Init() {}
	inline virtual void Update(float elapseTime) {}
	inline virtual void Render(float aspectRatio) {}
	inline virtual void ShutDown() {}
};

