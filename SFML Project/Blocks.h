#ifndef BLOCKS_H
#define BLOCKS_H
//#include <math.h>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bomb.h"

class Blocks
{
public: //tvär-tom
	static const int WIDTH = 16;
	static const int HIGHT = 11;
private:
	int **gameArea;
	sf::Texture Grass1Block;
	sf::RectangleShape grass1;
	sf::Texture Grass2Block;
	sf::RectangleShape grass2;
	sf::Texture stoneBlock;
	sf::RectangleShape stone;
	sf::Texture weaponBlock;
	sf::RectangleShape weapon;
	sf::Texture treeBottomBlock;
	sf::RectangleShape treeBottom;
	sf::Texture treeUpperBlock;
	sf::RectangleShape treeUpper;

	sf::Texture goFasterBlock;
	sf::RectangleShape goFaster;
	
	sf::Texture thunder6Block;
	sf::RectangleShape thunder6;
	sf::Texture thunder7Block;
	sf::RectangleShape thunder7;
	sf::Texture thunder8Block;
	sf::RectangleShape thunder8;


	sf::SoundBuffer bufferPowerup;
	sf::Sound powerupSound;

	Bomb bombP1;
	Bomb bombP2;
	
	void playPowerUpSound();
	bool intersectRectangle(const float & x1, const float & y1,const float & widht1,const float & hight1, const float & x2, const float & y2, const float & widht2, const float & hight2);

public:
	Blocks();
	~Blocks();

	void increasBombSize(bool isPlayer2);
	void putDownBomb(int x, int y, bool isPlayer2);
	bool getPlaced();

	void makeGameboard();
	int intersectRectangleCheck(const sf::Vector2f & box);
	void update(float  deltaTime);
	void draw(sf::RenderWindow & renderWindow);
	int getHeight() const;
	int getWidth() const;
};

#endif // !BLOCKS_H
