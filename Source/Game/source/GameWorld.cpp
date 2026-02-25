#include "GameWorld.h"

#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>
#include <tge/engine.h>
#include <atomic>
#include <condition_variable>

using namespace Tga;

bool myUpdateFinished = false;
bool myRenderFinished = false;

std::condition_variable myUpdateCondition;
std::condition_variable mySwapCondition;
std::mutex myUpdateMutex;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::SHUTDOWNPLXPLOX()
{
	myUpdateCondition.notify_all();
}

void GameWorld::Init()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();

	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };
	{
		mySharedData.myTexture = engine.GetTextureManager().GetTexture("Sprites/tge_logo_w.dds");

		myTGELogoInstance.myPivot = { 0.5f, 0.5f };
		myTGELogoInstance.myPosition = Tga::Vector2f{ 0.5f, 0.5f }*resolution;
		myTGELogoInstance.mySize = Tga::Vector2f{ 0.75f, 0.75f }*resolution.y;
		myTGELogoInstance.myColor = Tga::Color(1, 1, 1, 1);
	}
	RenderCommand KurokoCommand;
	KurokoCommand.myData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Kuroko.dds");
	KurokoCommand.myInstance.myPosition = Tga::Vector2f{ 0.25f, 0.1f } *resolution;
	KurokoCommand.myInstance.mySize = engine.GetTextureManager().GetTexture("Sprites/Kuroko.dds")->CalculateTextureSize();
	myFirstRenderThread.push_back(KurokoCommand);
	RenderCommand KurokoTwoCommand;
	KurokoTwoCommand.myData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Doggy.dds");
	KurokoTwoCommand.myInstance.myPosition = Tga::Vector2f{ 0.75f, 0.1f } *resolution;
	KurokoTwoCommand.myInstance.mySize = engine.GetTextureManager().GetTexture("Sprites/Doggy.dds")->CalculateTextureSize();
	myUpdateCommandPointer->push_back(KurokoTwoCommand);
}

void GameWorld::Update(float aTimeDelta, Tga::InputManager& aInput)
{
	UNREFERENCED_PARAMETER(aInput);
	UNREFERENCED_PARAMETER(aTimeDelta);

	Tga::Engine& engine = *Tga::Engine::GetInstance();

	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };

	myUpdateCommandPointer->clear();
	for (int x = 0; x < 1;x++)
	{
		for (int y = 0;y < 2;y++)
		{
			RenderCommand KurokoCommand;
			KurokoCommand.myData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Kuroko.dds");
			KurokoCommand.myInstance.myPosition = Tga::Vector2f{ 0.25f, 0.1f } *resolution;
			KurokoCommand.myInstance.mySize = engine.GetTextureManager().GetTexture("Sprites/Kuroko.dds")->CalculateTextureSize();
			myUpdateCommandPointer->push_back(KurokoCommand);
			RenderCommand KurokoTwoCommand;
			KurokoTwoCommand.myData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Doggy.dds");
			KurokoTwoCommand.myInstance.myPosition = Tga::Vector2f{ 0.75f, 0.1f } *resolution;
			KurokoTwoCommand.myInstance.mySize = engine.GetTextureManager().GetTexture("Sprites/Doggy.dds")->CalculateTextureSize();
			myUpdateCommandPointer->push_back(KurokoTwoCommand);
		}
	}
	myUpdateFinished = true;
	std::unique_lock lock(myUpdateMutex);
	myUpdateCondition.wait(lock);
}

void GameWorld::Render()
{
	myRenderFinished = false;

	auto& engine = *Tga::Engine::GetInstance();
	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());
		for (const auto& command : *myRenderCommandPointer)
		{
			myRenderFinished = false;
			spriteDrawer.Draw(command.myData, command.myInstance);
			myRenderFinished = true;
		}
	myRenderFinished = true;
	
	while (myUpdateFinished == false)
	{
	}

	if (myRenderFinished && myUpdateFinished)
	{
		std::swap(myRenderCommandPointer, myUpdateCommandPointer);
	}
	myRenderFinished = false;
	myUpdateFinished = false;
	myUpdateCondition.notify_all();
	// Debug draw pivot
#ifndef _RETAIL
	{
		Tga::DebugDrawer& dbg = engine.GetDebugDrawer();
		Tga::Color c1 = myTGELogoInstance.myColor;
		dbg.DrawCircle(myTGELogoInstance.myPosition, 5.f, (c1.myR + c1.myG + c1.myB) / 3 > 0.3f ? Tga::Color(0, 0, 0, 1) : Tga::Color(1, 1, 1, 1));
	}
#endif
}
