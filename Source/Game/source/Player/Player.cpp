#include "Player.h"
#include "Projectile.h"
#include "../GameWorld.h"
#include "fstream"

Player& Player::GetInstance()
{
    static Player instance;
    return instance;
}

void Player::Update(float aTimeDelta, Tga::InputManager& aInput)
{
    UNREFERENCED_PARAMETER(aTimeDelta);
    UNREFERENCED_PARAMETER(aInput);

    Movement(aTimeDelta, aInput);

    if (aInput.IsKeyPressed(VK_SPACE)) { Shoot(); }
}


CommonUtilities::Vector3<float> Player::GetPos()
{
    return myTransform.myRow3;
}

Player::Player()
{
    myVisual.mySpriteDrawer = &Tga::Engine::GetInstance()->GetGraphicsEngine().GetSpriteDrawer();
    std::ifstream readStream("CharacterFiles/Player.Goob");
    mySource = json::parse(readStream);
    json visual = mySource["PlayerVisStruct"];
    readStream.close();
    
    {
        myVisual.mySharedData.myTexture = Tga::Engine::GetInstance()->GetTextureManager().GetTexture(visual["TextureSource"].get<std::string>().c_str());
        myVisual.myInstanceData.myPosition = { 200.0f,250.0f };
        myVisual.myInstanceData.myColor = { 1,1,1 };
        myVisual.myInstanceData.myPivot = { 0.5f,0.5f };
        myVisual.myInstanceData.mySize = myVisual.mySharedData.myTexture->CalculateTextureSize();
        myVisual.myInstanceData.mySize *= {4};
    }

    {
        myTransform.myRow3 = { myVisual.myInstanceData.myPosition.x ,myVisual.myInstanceData.myPosition.y, 0 };
    }

    int i = 0;
    while (i < 6)
    {
        Projectile* sword = new Projectile();
        mySwords.push_back(sword);
        i++;
    }

}

void Player::Movement(float aTimeDelta, Tga::InputManager& aInput)
{
    if (aInput.IsKeyHeld('A') || aInput.IsKeyHeld(VK_LEFT))
    {
        myTransform.myRow3.x -= 400 * aTimeDelta;
    }
    if (aInput.IsKeyHeld('D') || aInput.IsKeyHeld(VK_RIGHT))
    {
        myTransform.myRow3.x += 400 * aTimeDelta;
    }
    if (aInput.IsKeyHeld('W') || aInput.IsKeyHeld(VK_UP))
    {
        myTransform.myRow3.y += 400 * aTimeDelta;
    }    
    if (aInput.IsKeyHeld('S') || aInput.IsKeyHeld(VK_DOWN))
    {
        myTransform.myRow3.y -= 400 * aTimeDelta;
    }
}

void Player::Shoot()
{
    switch (CurrentProjectile)
    {
    case 0:
        mySwords[0]->SetPos(myTransform.myRow3);
        mySwords[0]->Activate();
        CurrentProjectile++;
        break;    
    case 1:
        mySwords[1]->SetPos(myTransform.myRow3);
        mySwords[1]->Activate();
        CurrentProjectile++;
        break;    
    case 2:
        mySwords[2]->SetPos(myTransform.myRow3);
        mySwords[2]->Activate();
        CurrentProjectile++;
        break;    
    case 3:
        mySwords[3]->SetPos(myTransform.myRow3);
        mySwords[3]->Activate();
        CurrentProjectile++;
        break;    
    case 4:
        mySwords[4]->SetPos(myTransform.myRow3);
        mySwords[4]->Activate();
        CurrentProjectile++;
        break;    
    case 5:
        mySwords[5]->SetPos(myTransform.myRow3);
        mySwords[5]->Activate();
        CurrentProjectile = 0;
        break;
    }
}
