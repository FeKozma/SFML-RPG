#include "menuRow.h"

MenuRow::MenuRow()
{
	menuBlock.setSize(sf::Vector2f(2*64.0f, 64.0f));
	if (menu.loadFromFile("../Resources/menu.png"))
	{
		menuBlock.setTexture(&menu);
	}
	else
	{
		std::cout << "did not load menu texture\n";
	}
	statBlock.setSize(sf::Vector2f(2 * 64.0f, 64.0f));
	if (stat.loadFromFile("../Resources/stat.png"))
	{
		statBlock.setTexture(&stat);
	}
	else
	{
		std::cout << "did not load stat texture\n";
	}
}

MenuRow::~MenuRow()
{
}

void MenuRow::draw(sf::RenderWindow & renderWindow)
{
	menuBlock.setPosition(sf::Vector2f(0.0, 0.0));
	renderWindow.draw(menuBlock);

	statBlock.setPosition(sf::Vector2f(64 * 2, 0));
	renderWindow.draw(statBlock);
}
