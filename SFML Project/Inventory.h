#pragma once
#include <SFML/Graphics.hpp>

class Inventory
{
private: 
	sf::Texture empty;
	sf::RectangleShape emptyBlock;

	sf::Texture ax;
	sf::RectangleShape axBlock;

	sf::Texture skillAnimation;
	sf::RectangleShape skillAnimationBlock;
	sf::IntRect currentFrame;

	sf::Texture energy;
	sf::RectangleShape energyBlock;


	int skill1 = -1;


	float timePerFrame =2;
	float timeOnThisFrame = 0; 

public:
	Inventory();
	~Inventory();
	void draw(sf::RenderWindow & renderWindow, int height, int with);
	int updateSkill1(float deltaTime);
	
};

