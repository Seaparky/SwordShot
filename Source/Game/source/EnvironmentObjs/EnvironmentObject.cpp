#include "EnvironmentObject.h"

using namespace Tga;

void BackgroundObject::Initialize(const SceneObject& aObject, std::vector<ScenePropertyDefinition>& aProps)
{
	Engine* engine = Engine::GetInstance();
	TextureManager& myTextureManager = engine->GetTextureManager();
	myVisual.mySpriteDrawer = &Tga::Engine::GetInstance()->GetGraphicsEngine().GetSpriteDrawer();
	myPosition = aObject.GetPosition();

	auto t = aObject.GetTransform();

	for (ScenePropertyDefinition& property : aProps)
	{
		if (property.name == "SpriteModel"_tgaid)
		{
			CopyOnWriteWrapper<SceneSprite>* cowWrapper = property.value.Get<CopyOnWriteWrapper<SceneSprite>>();
			const SceneSprite& spriteValue = cowWrapper->Get();
			myVisual.mySharedData.myTexture = myTextureManager.GetTexture(spriteValue.textures[0].GetString());

			myVisual.myInstanceData.myPosition = Tga::Vector2f{ myPosition.x, myPosition.y };
			myVisual.myInstanceData.mySize = myVisual.mySharedData.myTexture->CalculateTextureSize();
			myVisual.myInstanceData.mySize *= {6.3f};
		}
	}
}

void BackgroundObject::Render(CommonUtilities::Matrix3x3<float> aCamera)
{
	CommonUtilities::Vector3<float> cameraPosition = CommonUtilities::Vector3<float>(myPosition.x, myPosition.y, 1) * aCamera;
	myVisual.myInstanceData.myPosition = CommonUtilities::Vector2<float>(cameraPosition.x, cameraPosition.y).ToTga();
	myVisual.mySpriteDrawer->Draw(myVisual.mySharedData, myVisual.myInstanceData);
}

