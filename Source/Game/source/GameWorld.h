#pragma once

#include <tge/sprite/sprite.h>
#include <tge/input/InputManager.h>
#include "Pause.h"
#include "Player/Player.h"
#include <vector>


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


	void Init();
	void Update(float aTimeDelta, Tga::InputManager& aInput);
	void Render();


private:
	Tga::Sprite2DInstanceData myTGELogoInstance = {};
	Tga::SpriteSharedData mySharedData = {};

	Player* myPlayer;
	Pause* myPause;

};