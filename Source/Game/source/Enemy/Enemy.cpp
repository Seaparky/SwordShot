#include "Enemy.h"

Enemy::Enemy()
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

Enemy::~Enemy()
{
}

void Enemy::Update(float aTimeDelta)
{
    UNREFERENCED_PARAMETER(aTimeDelta);
}