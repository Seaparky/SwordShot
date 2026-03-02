#include "GameWorld.h"

#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>
#include <tge/engine.h>
#include <atomic>
#include <condition_variable>
#include "LinearAlg/Matrix3x3.h"
#include "LinearAlg/Vector3.h"

using namespace Tga;

CommonUtilities::Matrix3x3<float> cameraSpaceMatrix;

GameWorld::GameWorld()
{
	myPause = &Pause::GetInstance();
	myPlayer = &Player::GetInstance();
}

GameWorld::~GameWorld()
{
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

}

void GameWorld::Update(float aTimeDelta, Tga::InputManager& aInput)
{
	UNREFERENCED_PARAMETER(aInput);
	UNREFERENCED_PARAMETER(aTimeDelta);

	if (myPause->GetActive())
	{
		myPause->Update(aInput);
		return;
	}

	myPlayer->Update(aTimeDelta, aInput);

	cameraSpaceMatrix.myRow3 = CommonUtilities::Vector3<float>(myPlayer->GetPos().x * -1.0f, myPlayer->GetPos().y * -1.0f, 1);

	cameraSpaceMatrix.myRow3.x += Tga::Engine::GetInstance()->GetWindowSize().x / 2;
	cameraSpaceMatrix.myRow3.y += Tga::Engine::GetInstance()->GetWindowSize().y / 2;

	if (aInput.IsKeyPressed(VK_ESCAPE))
	{
		std::cout << "Paused" << std::endl;
		myPause->Enable();
	}

}

void GameWorld::Render()
{
	if (myPause->GetActive())
	{
		myPause->Render();
	}

	myPlayer->Render(cameraSpaceMatrix);


}
