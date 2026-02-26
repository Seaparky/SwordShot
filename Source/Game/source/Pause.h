#pragma once
#include <array>
#include <tge/engine.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/sprite/sprite.h>
#include <tge/input/InputManager.h>



class Pause
{
public:

	struct Button
	{
		Tga::Sprite2DInstanceData myInstanceData = {};
		Tga::SpriteSharedData mySharedData = {};
		Tga::Vector2f myButtonMin = { 0,0 };
		Tga::Vector2f myButtonMax = { 0,0 };
		float myHalfWidth;
		float myHalfHeight;
	};

	static Pause& GetInstance();
	~Pause();

	bool GetActive();

	void Enable();
	void Disable();

	void Unpause();
	void Menu();
	void Quit();

	void Render();

	void Update(Tga::InputManager& aInput);



private:
	Pause();

	bool myEnabled = false;

	Tga::Engine* myCurrentEngine;
	Tga::SpriteDrawer* mySpriteDrawer;

	std::array<Button, 3> myScreenButtons;

	Tga::Vector2f mousePos;
};

