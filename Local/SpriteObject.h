#pragma once
#include <tge/engine.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/sprite/sprite.h>
#include "../Source/Game/source/LinearAlg/Matrix3x3.h"




class SpriteObject
{
public:
	void Render(CommonUtilities::Matrix3x3<float> aCamera);


private:

	struct VisualInfo
	{
		Tga::SpriteDrawer* mySpriteDrawer;
		Tga::Sprite2DInstanceData myInstanceData = {};
		Tga::SpriteSharedData mySharedData = {};
	};

protected:

	VisualInfo myVisual;
	CommonUtilities::Matrix3x3<float> myTransform;

};

