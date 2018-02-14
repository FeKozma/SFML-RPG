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
}


Inventory::~Inventory()
{
}

void Inventory::draw(sf::RenderWindow & renderWindow, int height, int with)
{


	axBlock.setPosition(sf::Vector2f((float(((with / 2) - 2) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(axBlock);

	emptyBlock.setPosition(sf::Vector2f((float(((with / 2) - 1) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(emptyBlock);

	emptyBlock.setPosition(sf::Vector2f((float(((with / 2) - 0) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(emptyBlock);

	emptyBlock.setPosition(sf::Vector2f((float(((with / 2) + 1) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(emptyBlock);

	emptyBlock.setPosition(sf::Vector2f((float(((with / 2) + 2) * 64)), (float((height - 1) * 64))));
	renderWindow.draw(emptyBlock);
}
