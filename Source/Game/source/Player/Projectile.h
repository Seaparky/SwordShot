#pragma once
#include <tge/input/InputManager.h>
#include <tge/engine.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/sprite/sprite.h>
#include "../BaseClass/SpriteObject.h"
#include "../LinearAlg/Vector2.h"
#include "../LinearAlg/Matrix3x3.h"
#include "../Collisions/Sphere.h"

using namespace CommonUtilities;

class Projectile : public SpriteObject
{
public:

	Projectile();
	~Projectile();

	void Update(float aTimeDelta);

	void SetPos(CommonUtilities::Vector3<float> aNewPosition);

	void Activate();
private:


	CommonUtilities::Vector2<float> myPosition;
	Sphere<float> myHitBox;

	bool myActive = false;

};