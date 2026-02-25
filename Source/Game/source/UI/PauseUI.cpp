#include "PauseUI.h"

PauseUI& PauseUI::GetInstance()
{
	static PauseUI instance;
	return instance;
}

PauseUI::~PauseUI()
{
}


bool PauseUI::GetActive()
{
	return myEnabled;
}

void PauseUI::Enable()
{
	myEnabled = true;
}

void PauseUI::Disable()
{
	myEnabled = false;
}

void PauseUI::Unpause()
{

	if (mousePos.x < myScreenButtons[0].myButtonMin.x)
	{
		std::cout << "Hit too left" << std::endl;
	}
	if (mousePos.y < myScreenButtons[0].myButtonMin.y)
	{
		std::cout << "Hit too low" << std::endl;
	}
	if (mousePos.x > myScreenButtons[0].myButtonMax.x)
	{
		std::cout << "Hit too right" << std::endl;
		std::cout << mousePos.x << std::endl;
		std::cout << myScreenButtons[0].myButtonMax.x << std::endl;
	}
	if (mousePos.y > myScreenButtons[0].myButtonMax.y)
	{
		std::cout << "Hit too high" << std::endl;
		std::cout << mousePos.y << std::endl;
		std::cout << myScreenButtons[0].myButtonMax.y << std::endl;
	}
	else
	{
		Disable();
		std::cout << "Button hit" << std::endl;
	}

}

void PauseUI::Menu(bool& aMenu)
{
	if (mousePos.x < myScreenButtons[1].myButtonMin.x)
	{
		std::cout << "Hit too left" << std::endl;
	}
	if (mousePos.y < myScreenButtons[1].myButtonMin.y)
	{
		std::cout << "Hit too low" << std::endl;
	}
	if (mousePos.x > myScreenButtons[1].myButtonMax.x)
	{
		std::cout << "Hit too right" << std::endl;
		std::cout << mousePos.x << std::endl;
		std::cout << myScreenButtons[1].myButtonMax.x << std::endl;
	}
	if (mousePos.y > myScreenButtons[1].myButtonMax.y)
	{
		std::cout << "Hit too high" << std::endl;
		std::cout << mousePos.y << std::endl;
		std::cout << myScreenButtons[1].myButtonMax.y << std::endl;
	}
	else
	{
		aMenu = false;
		std::cout << "Button hit" << std::endl;
	}

}

void PauseUI::Quit()
{
	if (mousePos.x < myScreenButtons[2].myButtonMin.x)
	{
		std::cout << "Hit too left" << std::endl;
	}
	if (mousePos.y < myScreenButtons[2].myButtonMin.y)
	{
		std::cout << "Hit too low" << std::endl;
	}
	if (mousePos.x > myScreenButtons[2].myButtonMax.x)
	{
		std::cout << "Hit too right" << std::endl;
		std::cout << mousePos.x << std::endl;
		std::cout << myScreenButtons[2].myButtonMax.x << std::endl;
	}
	if (mousePos.y > myScreenButtons[2].myButtonMax.y)
	{
		std::cout << "Hit too high" << std::endl;
		std::cout << mousePos.y << std::endl;
		std::cout << myScreenButtons[2].myButtonMax.y << std::endl;
	}
	else
	{
		myCurrentEngine->Shutdown();
		std::cout << "Button hit" << std::endl;
	}

}

void PauseUI::Render()
{
	for (const Button& var : myScreenButtons)
	{
		mySpriteDrawer->Draw(var.mySharedData, var.myInstanceData);
	}
}

void PauseUI::Update(Tga::InputManager& aInput, bool& aMenu)
{
	mousePos = aInput.GetMousePosition();

	for (Button& var : myScreenButtons)
	{
		var.myHalfWidth = var.myInstanceData.mySize.x / 2;
		var.myHalfHeight = var.myInstanceData.mySize.y / 2;
		var.myButtonMin = { var.myInstanceData.myPosition.x - var.myHalfWidth, var.myInstanceData.myPosition.y - var.myHalfHeight };
		var.myButtonMax = { var.myInstanceData.myPosition.x + var.myHalfWidth, var.myInstanceData.myPosition.y + var.myHalfHeight };
	}

	if (aInput.IsKeyReleased(VK_LBUTTON))
	{
		mousePos.y = 900 - mousePos.y;
		Unpause();
		Menu(aMenu);
		Quit();
	}
}

PauseUI::PauseUI()
{
	myCurrentEngine = Tga::Engine::GetInstance();
	mySpriteDrawer = &myCurrentEngine->GetGraphicsEngine().GetSpriteDrawer();

	//for (int i = 0; i < myScreenButtons.size();)
	//{
	//	myScreenButtons[i].mySharedData.myTexture = myCurrentEngine->GetTextureManager().GetTexture("Sprites/Restart.dds");
	//	myScreenButtons[i].myHalfHeight = myScreenButtons[i].myInstanceData.mySize.y / 2;
	//	myScreenButtons[i].myHalfWidth = myScreenButtons[i].myInstanceData.mySize.x / 2;
	//}

	for (Button& var : myScreenButtons)
	{
		var.mySharedData.myTexture = myCurrentEngine->GetTextureManager().GetTexture("UI/ButtonPlay.dds");
	}
	myScreenButtons[0].myInstanceData.myPosition = { 400,800 };
	myScreenButtons[0].myInstanceData.mySize = { 200,200 };

	myScreenButtons[1].myInstanceData.myPosition = { 400,500 };
	myScreenButtons[1].myInstanceData.mySize = { 200,200 };

	myScreenButtons[2].myInstanceData.myPosition = { 400,200 };
	myScreenButtons[2].myInstanceData.mySize = { 200,200 };


}
