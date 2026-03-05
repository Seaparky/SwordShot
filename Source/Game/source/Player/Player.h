#pragma once
#include <tge/input/InputManager.h>
#include <tge/engine.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/sprite/sprite.h>
#include "../BaseClass/SpriteObject.h"
#include "nlohmann/json.hpp"
#include "../LinearAlg/Vector2.h"
#include "../LinearAlg/Matrix3x3.h"
#include "../Collisions/Sphere.h"

class Projectile;
class GameWorld;

using namespace CommonUtilities;
using namespace nlohmann;


class Player : public SpriteObject
{
public:

	static Player& GetInstance();

	void Update(float aTimeDelta, Tga::InputManager& aInput);

	CommonUtilities::Vector3<float> GetPos();

	std::vector<Projectile*> mySwords;

private:

	Player();

	void Movement(float aTimeDelta, Tga::InputManager& aInput);

	void Shoot();

	json mySource;

	CommonUtilities::Vector2<float> myPosition;
	Sphere<float> myHitBox;

	float mySpeed;

	int CurrentProjectile;

	GameWorld* EnemySource;

};

