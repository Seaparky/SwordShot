#pragma once
#include <tge/input/InputManager.h>
#include <tge/engine.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/sprite/sprite.h>
#include "nlohmann/json.hpp"
#include "../LinearAlg/Vector2.h"
#include "../LinearAlg/Matrix3x3.h"
#include "../Collisions/AABB3D.h"


using namespace CommonUtilities;
using namespace nlohmann;


struct VisualInfo
{
	Tga::SpriteDrawer* mySpriteDrawer;
	Tga::Sprite2DInstanceData myInstanceData = {};
	Tga::SpriteSharedData mySharedData = {};
};


class Player
{
public:

	static Player& GetInstance();

	void Update(float aTimeDelta, Tga::InputManager& aInput);

	void Render(CommonUtilities::Matrix3x3<float> aCamera);

	CommonUtilities::Vector2<float> GetPos();

private:

	Player();

	void Movement(float aTimeDelta, Tga::InputManager& aInput);

	json mySource;

	CommonUtilities::Vector2<float> myPosition;
	AABB3D<float> myHitBox;

	VisualInfo myVisual;

	float mySpeed;

};

