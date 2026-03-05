#pragma once
#include <tge/input/InputManager.h>
#include <tge/engine.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/sprite/sprite.h>
#include "nlohmann/json.hpp"
#include "../BaseClass/SpriteObject.h"
#include "../LinearAlg/Vector2.h"
#include "../LinearAlg/Matrix3x3.h"
#include "../Collisions/Sphere.h"

using namespace nlohmann;

class Enemy : public SpriteObject
{
public:

	Enemy();
	~Enemy();

	void Update(float aTimeDelta);


private:


	CommonUtilities::Vector2<float> myPosition;
	Sphere<float> myHitBox;
};

