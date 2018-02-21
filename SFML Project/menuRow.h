#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class MenuRow
{
private:
	sf::Texture menu;
	sf::RectangleShape menuBlock;

	sf::Texture stat;
	sf::RectangleShape statBlock;

public:
	MenuRow();
	~MenuRow();
	void draw(sf::RenderWindow & renderWindow);

};

