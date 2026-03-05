#include "Projectile.h"

Projectile::Projectile()
{
    myVisual.mySpriteDrawer = &Tga::Engine::GetInstance()->GetGraphicsEngine().GetSpriteDrawer();

    {
        myVisual.mySharedData.myTexture = Tga::Engine::GetInstance()->GetTextureManager().GetTexture("KenneyAssets/DotMatrix/Sprites/item0.png");
        myVisual.myInstanceData.myPosition = { 200.0f,-2500.0f };
        myVisual.myInstanceData.myColor = { 1,1,1 };
        myVisual.myInstanceData.myPivot = { 0.5f,0.5f };
        myVisual.myInstanceData.mySize = myVisual.mySharedData.myTexture->CalculateTextureSize();
        myVisual.myInstanceData.mySize *= {4};
    }

    {
        myTransform.myRow3 = { myVisual.myInstanceData.myPosition.x ,myVisual.myInstanceData.myPosition.y, 0 };
    }
}

Projectile::~Projectile()
{

}

void Projectile::Update(float aTimeDelta)
{
    if (!myActive) { return; }
    myTransform.myRow3.y += 650 * aTimeDelta;
}

void Projectile::SetPos(CommonUtilities::Vector3<float> aNewPosition)
{
    myTransform.myRow3 = aNewPosition;
}

void Projectile::Activate()
{
    myActive = true;
}
