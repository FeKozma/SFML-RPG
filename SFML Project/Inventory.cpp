#include "Inventory.h"
#include <iostream>


Inventory::Inventory()
{
	axBlock.setSize(sf::Vector2f(64.0f, 64.0f));
	if (ax.loadFromFile("../Resources/inventoryAx.png"))
	{
		axBlock.setTexture(&ax);
	}
	else
	{
		std::cout << "did not load inventoryAx texture\n";
	}
	
	emptyBlock.setSize(sf::Vector2f(64.0f, 64.0f));
	if (empty.loadFromFile("../Resources/inventory.png"))
	{
		emptyBlock.setTexture(&empty);
	}
	else
	{
		std::cout << "did not load emptyBlock texture\n";
	}

	skillAnimationBlock.setSize(sf::Vector2f(64, 64));
	if (skillAnimation.loadFromFile("../Resources/timer.png"))
	{
		skillAnimationBlock.setTexture(&skillAnimation);

		currentFrame.width = 64;
		currentFrame.height = 64;

		currentFrame.left = 0;
		currentFrame.top = 0;
		skillAnimationBlock.setTextureRect(currentFrame);

	}
	else
	{
		std::cout << "did not load skillAnimation texture\n";
	}

	energyBlock.setSize(sf::Vector2f(64, 64));
	if (energy.loadFromFile("../Resources/explosionBlock6.png"))
	{
		energyBlock.setTexture(&energy);
	}
}


Inventory::~Inventory()
{
}

void Inventory::draw(sf::RenderWindow & renderWindow, int height, int with)
{


	axBlock.setPosition(sf::Vector2f((float(((with / 2) - 3) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(axBlock);


	emptyBlock.setPosition(sf::Vector2f((float(((with / 2) - 2) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(emptyBlock);

	emptyBlock.setPosition(sf::Vector2f((float(((with / 2) - 1) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(emptyBlock);

	//emptyBlock.setPosition(sf::Vector2f((float(((with / 2) - 0) * 64)), (float((height - 1) * 64))));
	//renderWindow.draw(emptyBlock);




	emptyBlock.setPosition(sf::Vector2f((float(((with / 2) + 1) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(emptyBlock);

	energyBlock.setPosition(sf::Vector2f((float(((with / 2) + 1) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(energyBlock);

	emptyBlock.setPosition(sf::Vector2f((float(((with / 2) + 2) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(emptyBlock);

	emptyBlock.setPosition(sf::Vector2f((float(((with / 2) + 3) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(emptyBlock);

	if (skill1 != -1)
	{
		currentFrame.left = this->skill1 * 64;
		skillAnimationBlock.setTextureRect(currentFrame);

		skillAnimationBlock.setPosition(sf::Vector2f((float(((with / 2) + 1) * 64)), (float((height - 1) * 64))));
		renderWindow.draw(skillAnimationBlock);
	}
}

int Inventory::updateSkill1(float deltaTime)
{
	timeOnThisFrame -= deltaTime;

	//std::cout << std::to_string(deltaTime) + '\n';
	//std::cout << "timeOnThisFrame: " + std::to_string(timeOnThisFrame) + '\n';
	if (timeOnThisFrame < 0)
	{
		if (skill1 < 3)
		{
			skill1++;
			timeOnThisFrame += timePerFrame;

			return true;
		}
		else
		{
			skill1 = -1;
			timeOnThisFrame = 0;

			return false;
		}
	}

	
}

