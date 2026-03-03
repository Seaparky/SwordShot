#pragma once

#include <tge/engine.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/graphics/GraphicsStateStack.h>
#include <tge/settings/settings.h>
#include <tge/math/Vector.h>

#include <tge/model/ModelInstance.h>
#include <tge/model/ModelFactory.h>
#include <tge/texture/TextureManager.h>

#include <tge/sprite/sprite.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/drawers/DebugDrawer.h>
#include <tge/drawers/ModelDrawer.h>

#include <tge/scene/SceneObject.h>
#include <tge/scene/SceneObjectDefinition.h>
#include <tge/scene/SceneObjectDefinitionManager.h>
#include <tge/scene/ScenePropertyTypes.h>
#include <tge/scene/Scene.h>

#include <tge/script/BaseProperties.h>

#include <tge/input/inputManager.h>
#include <iostream>

#include <stdlib.h>
#include <cmath>
#include <vector>
#include <functional>

#include "../LinearAlg/Vector2.h"
#include "../LinearAlg/Matrix3x3.h"
#include "../Collisions/AABB3D.h"

class BackgroundObject
{
private:

	struct VisualInfo
	{
		Tga::SpriteDrawer* mySpriteDrawer;
		Tga::Sprite2DInstanceData myInstanceData = {};
		Tga::SpriteSharedData mySharedData = {};
	};

public:
	Tga::Vector3f myPosition;
	Tga::TextureResource* myTexture;

	VisualInfo myVisual;

	void Initialize(const Tga::SceneObject& aObject, std::vector<Tga::ScenePropertyDefinition>& aProps);

	void Render(CommonUtilities::Matrix3x3<float> aCamera);
};

