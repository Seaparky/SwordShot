#pragma once

#include <tge/sprite/sprite.h>
#include <tge/input/InputManager.h>
#include <vector>
#include <thread>

struct RenderCommand
{
	Tga::Sprite2DInstanceData myInstance;
	Tga::SpriteSharedData myData;
};

class GameWorld
{
public:
	GameWorld(); 
	~GameWorld();

	void SHUTDOWNPLXPLOX();

	void Init();
	void Update(float aTimeDelta, Tga::InputManager& aInput);
	void Render();


private:
	Tga::Sprite2DInstanceData myTGELogoInstance = {};
	Tga::SpriteSharedData mySharedData = {};

	std::vector<RenderCommand> myFirstRenderThread;
	std::vector<RenderCommand> mySecondRenderThread;

	std::vector<RenderCommand>* myRenderCommandPointer = &myFirstRenderThread;
	std::vector<RenderCommand>* myUpdateCommandPointer = &mySecondRenderThread;


};