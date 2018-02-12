#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Blocks.h"
#include "Text.h"
#include <iostream>


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
private:
	Player* player1;
	Player* player2;
	Blocks gameArea;
	Text score;

	sf::Music music;

public:

	Game();
	~Game();
	void run();


	void keyEventCheck();
	void canPlayersMove(float deltaTime);
	void isPlayerInExplosion();

	void P1_IncreasSpeed();
	void P1_IncreasBombSize();

	void P2_IncreasSpeed();
	void P2_IncreasBombSize();
	

	void updateWindow(sf::RenderWindow &renderWindow, float deltaTime);

};

#endif // !"GAME_H"
