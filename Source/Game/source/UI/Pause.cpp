#include "Pause.h"

Pause& Pause::GetInstance()
{
	static Pause instance;
	return instance;
}

Pause::~Pause()
{
}


bool Pause::GetActive()
{
	return myEnabled;
}

void Pause::Enable()
{
	myEnabled = true;
}

void Pause::Disable()
{
	myEnabled = false;
}

void Pause::Unpause()
{
	if (mousePos.x < myScreenButtons[0].myButtonMin.x)
	{
		std::cout << "Hit too left" << std::endl;
	}
	else if (mousePos.y < myScreenButtons[0].myButtonMin.y)
	{
		std::cout << "Hit too low" << std::endl;
	}
	else if (mousePos.x > myScreenButtons[0].myButtonMax.x)
	{
		std::cout << "Hit too right" << std::endl;
		std::cout << mousePos.x << std::endl;
		std::cout << myScreenButtons[0].myButtonMax.x << std::endl;
	}
	else if (mousePos.y > myScreenButtons[0].myButtonMax.y)
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

void Pause::Menu()
{
	if (mousePos.x < myScreenButtons[1].myButtonMin.x)
	{
		std::cout << "Hit too left" << std::endl;
	}
	else if (mousePos.y < myScreenButtons[1].myButtonMin.y)
	{
		std::cout << "Hit too low" << std::endl;
	}
	else if (mousePos.x > myScreenButtons[1].myButtonMax.x)
	{
		std::cout << "Hit too right" << std::endl;
		std::cout << mousePos.x << std::endl;
		std::cout << myScreenButtons[1].myButtonMax.x << std::endl;
	}
	else if (mousePos.y > myScreenButtons[1].myButtonMax.y)
	{
		std::cout << "Hit too high" << std::endl;
		std::cout << mousePos.y << std::endl;
		std::cout << myScreenButtons[1].myButtonMax.y << std::endl;
	}
	else
	{
		std::cout << "Button hit" << std::endl;
	}
}

void Pause::Quit()
{
	if (mousePos.x < myScreenButtons[2].myButtonMin.x)
	{
		std::cout << "Hit too left" << std::endl;
	}
	else if (mousePos.y < myScreenButtons[2].myButtonMin.y)
	{
		std::cout << "Hit too low" << std::endl;
	}
	else if (mousePos.x > myScreenButtons[2].myButtonMax.x)
	{
		std::cout << "Hit too right" << std::endl;
		std::cout << mousePos.x << std::endl;
		std::cout << myScreenButtons[2].myButtonMax.x << std::endl;
	}
	else if (mousePos.y > myScreenButtons[2].myButtonMax.y)
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

void Pause::Render()
{
	for (const Button& var : myScreenButtons)
	{
		mySpriteDrawer->Draw(var.mySharedData, var.myInstanceData);
	}
}

void Pause::Update(Tga::InputManager& aInput)
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
		Menu();
		Quit();
	}

	if (aInput.IsKeyPressed(VK_ESCAPE))
	{
		Disable();
	}
}

Pause::Pause()
{
	myCurrentEngine = Tga::Engine::GetInstance();
	mySpriteDrawer = &myCurrentEngine->GetGraphicsEngine().GetSpriteDrawer();


	myScreenButtons[0].mySharedData.myTexture = myCurrentEngine->GetTextureManager().GetTexture("Sprites/Doggy.dds");
	myScreenButtons[0].myInstanceData.myPosition = { 400,800 };
	myScreenButtons[0].myInstanceData.mySize = { 200,200 };

	myScreenButtons[1].mySharedData.myTexture = myCurrentEngine->GetTextureManager().GetTexture("UI/ButtonMainMenu.dds");
	myScreenButtons[1].myInstanceData.myPosition = { 400,500 };
	myScreenButtons[1].myInstanceData.mySize = { 200,200 };

	myScreenButtons[2].mySharedData.myTexture = myCurrentEngine->GetTextureManager().GetTexture("UI/ButtonQuit.dds");
	myScreenButtons[2].myInstanceData.myPosition = { 400,200 };
	myScreenButtons[2].myInstanceData.mySize = { 200,200 };


}
