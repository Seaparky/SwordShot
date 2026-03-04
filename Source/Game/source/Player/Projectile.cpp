#include "Projectile.h"

Projectile::Projectile()
{
    myVisual.mySpriteDrawer = &Tga::Engine::GetInstance()->GetGraphicsEngine().GetSpriteDrawer();

    {
        myVisual.mySharedData.myTexture = Tga::Engine::GetInstance()->GetTextureManager().GetTexture("KenneyAssets/DotMatrix/Sprites/item0.png");
        myVisual.myInstanceData.myPosition = { 200.0f,250.0f };
        myVisual.myInstanceData.myColor = { 1,1,1 };
        myVisual.myInstanceData.myPivot = { 0.5f,0.5f };
        myVisual.myInstanceData.mySize = myVisual.mySharedData.myTexture->CalculateTextureSize();
        myVisual.myInstanceData.mySize *= {4};
    }

    {
        myPosition = { myVisual.myInstanceData.myPosition.x ,myVisual.myInstanceData.myPosition.y };
    }
}

Projectile::~Projectile()
{

}

void Projectile::Update(float aTimeDelta)
{
    if (!myActive) { return; }
    myPosition.y += 650 * aTimeDelta;
}

void Projectile::Render(CommonUtilities::Matrix3x3<float> aCamera)
{
    if (!myActive) { return; }
    CommonUtilities::Vector3<float> cameraPosition = CommonUtilities::Vector3<float>(myPosition.x, myPosition.y, 1) * aCamera;
    myVisual.myInstanceData.myPosition = CommonUtilities::Vector2<float>(cameraPosition.x, cameraPosition.y).ToTga();
    myVisual.mySpriteDrawer->Draw(myVisual.mySharedData, myVisual.myInstanceData);
}

void Projectile::SetPos(CommonUtilities::Vector2<float> aNewPosition)
{
    myPosition = aNewPosition;
}

void Projectile::Activate()
{
    myActive = true;
}
