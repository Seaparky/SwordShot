#include "SpriteObject.h"

void SpriteObject::Render(CommonUtilities::Matrix3x3<float> aCamera)
{
    CommonUtilities::Vector3<float> worldPosition = myTransform.myRow3 * myTransform;
    CommonUtilities::Vector3<float> posRelativeCamera = myTransform.myRow3 * myTransform * -aCamera;

    CommonUtilities::Vector3<float> cameraPosition = CommonUtilities::Vector3<float>(myTransform.myRow3.x, myTransform.myRow3.y, 1) * aCamera;
    //myVisual.myInstanceData.myPosition = CommonUtilities::Vector2<float>(posRelativeCamera.x, posRelativeCamera.y).ToTga();
    myVisual.myInstanceData.myPosition = CommonUtilities::Vector2<float>(cameraPosition.x, cameraPosition.y).ToTga();
    myVisual.mySpriteDrawer->Draw(myVisual.mySharedData, myVisual.myInstanceData);
}
