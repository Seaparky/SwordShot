#pragma once
#include <tge/engine.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/sprite/sprite.h>
#include "../LinearAlg/Matrix3x3.h"
#include "../LinearAlg/Vector2.h"




class SpriteObject
{
public:
	void Render(CommonUtilities::Matrix3x3<float> aCamera);


protected:

	struct VisualInfo
	{
		Tga::SpriteDrawer* mySpriteDrawer;
		Tga::Sprite2DInstanceData myInstanceData = {};
		Tga::SpriteSharedData mySharedData = {};
	};

	VisualInfo myVisual;
	CommonUtilities::Matrix3x3<float> myTransform;

};

