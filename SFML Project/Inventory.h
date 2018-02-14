#pragma once
#include <SFML/Graphics.hpp>

class Inventory
{
private: 
	sf::Texture empty;
	sf::RectangleShape emptyBlock;

	sf::Texture ax;
	sf::RectangleShape axBlock;
public:
	Inventory();
	~Inventory();
	void draw(sf::RenderWindow & renderWindow, int height, int with);
};

