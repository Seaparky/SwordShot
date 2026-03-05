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
#include "../../Editor/TGEditor/Scene/SceneUtil.h"
#include "tge/scene/SceneSerialize.h"
#include <tge/scene/SceneObjectDefinitionManager.h>
#include <tge/settings/settings.h>


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

	LoadEnvironment();

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

	for (Projectile* sword : myPlayer->mySwords)
	{
		sword->Update(aTimeDelta);
	}


	if (aInput.IsKeyPressed(VK_ESCAPE))
	{
		std::cout << "Paused" << std::endl;
		myPause->Enable();
	}

}

void GameWorld::Render()
{

	//cameraSpaceMatrix.myRow3 = myPlayer->GetPos();
	//cameraSpaceMatrix.myRow3.x += Tga::Engine::GetInstance()->GetWindowSize().x / 2;
	//cameraSpaceMatrix.myRow3.y += Tga::Engine::GetInstance()->GetWindowSize().y / 2;

	for (BackgroundObject obj : myEnvironmentBackground)
	{
		obj.Render(cameraSpaceMatrix);
	}

	for (Projectile* sword : myPlayer->mySwords)
	{
		sword->Render(cameraSpaceMatrix);
	}



	myPlayer->Render(cameraSpaceMatrix);

	if (myPause->GetActive())
	{
		myPause->Render();
	}

}

void GameWorld::LoadEnvironment()
{
	SceneObjectDefinitionManager aSceneObjectDefinitionManager;
	LoadScene("scene.Tgs", myEnvironment);
	aSceneObjectDefinitionManager.Init(Settings::GameAssetRoot().string().c_str());

	std::vector<Tga::ScenePropertyDefinition> sceneObjectProperties;

	for (const auto& sceneObject : myEnvironment.GetSceneObjects())
	{
		sceneObjectProperties.clear();
		sceneObject.second->CalculateCombinedPropertySet(aSceneObjectDefinitionManager, sceneObjectProperties);

		BackgroundObject obj;
		obj.Initialize(*sceneObject.second, sceneObjectProperties);
		myEnvironmentBackground.push_back(obj);

	}

}
