#include "Player.h"

Player& Player::GetInstance()
{
    static Player instance;
    return instance;
}

void Player::Update(float aTimeDelta, Tga::InputManager aInput)
{
    UNREFERENCED_PARAMETER(aTimeDelta);
    UNREFERENCED_PARAMETER(aInput);

}

void Player::Render()
{
    myVisual.mySpriteDrawer->Draw(myVisual.mySharedData, myVisual.myInstanceData);
}

Player::Player()
{
    myVisual.mySpriteDrawer = &Tga::Engine::GetInstance()->GetGraphicsEngine().GetSpriteDrawer();

}
