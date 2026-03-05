#pragma once

#include <tge/sprite/sprite.h>
#include <tge/input/InputManager.h>
#include <tge/scene/Scene.h>
#include "UI/Pause.h"
#include "Player/Player.h"
#include "Player/Projectile.h"
#include "BaseClass/SpriteObject.h"
#include "EnvironmentObjs/EnvironmentObject.h"
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

	void LoadEnvironment();
	
	Tga::Sprite2DInstanceData myTGELogoInstance = {};
	Tga::SpriteSharedData mySharedData = {};

	std::vector<BackgroundObject> myEnvironmentBackground;

	Player* myPlayer;
	Pause* myPause;

	std::vector<SpriteObject> Sprites;

	Tga::Scene myEnvironment;

};