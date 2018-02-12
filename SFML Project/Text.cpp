#include "Text.h"

Text::Text()
{
	if (!font.loadFromFile("../Resources/font.ttf"))
	{
		std::cout << "did not load font\n";
	}
	player1Score = 0;
	player2Score = 0;
	text.setString("player 1: 0 player 2: 0");
	text.setPosition(sf::Vector2f(50, 250));
	text.setFont(font);
	text.setScale(sf::Vector2f(0.6, 0.6));
}

Text::~Text()
{
}

void Text::uppdateScore(int points,bool isPlayer2)
{
	if (isPlayer2)
	{
		player2Score += points;
	}
	else
	{
		player1Score += points;
	}
}

void Text::update()
{
	text.setString("player 1:  " + std::to_string(player1Score) +'\n'+ "player 2: " + std::to_string(player2Score));
}

void Text::draw(sf::RenderWindow & renderWindow)
{
	renderWindow.draw(text);
}
