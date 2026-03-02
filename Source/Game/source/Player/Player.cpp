#include "Player.h"
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
}


void Player::Render(CommonUtilities::Matrix3x3<float> aCamera)
{
    CommonUtilities::Vector3<float> cameraPosition = CommonUtilities::Vector3<float>(myPosition.x, myPosition.y, 1) * aCamera;
    myVisual.myInstanceData.myPosition = CommonUtilities::Vector2<float>(cameraPosition.x, cameraPosition.y).ToTga();
    myVisual.mySpriteDrawer->Draw(myVisual.mySharedData, myVisual.myInstanceData);
}

CommonUtilities::Vector2<float> Player::GetPos()
{
    return myPosition;
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
        myVisual.myInstanceData.mySize *= {2};
    }

    {
        myPosition = { myVisual.myInstanceData.myPosition.x ,myVisual.myInstanceData.myPosition.y };
    }

}

void Player::Movement(float aTimeDelta, Tga::InputManager& aInput)
{
    if (aInput.IsKeyHeld('A'))
    {
        myPosition.x -= 100 * aTimeDelta;
    }
    if (aInput.IsKeyHeld('D'))
    {
        myPosition.x += 100 * aTimeDelta;
    }
    if (aInput.IsKeyHeld('W'))
    {
        myPosition.y += 100 * aTimeDelta;
    }    
    if (aInput.IsKeyHeld('S'))
    {
        myPosition.y -= 100 * aTimeDelta;
    }
}
