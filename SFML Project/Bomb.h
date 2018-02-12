#ifndef BOMB_H
#define BOMB_H
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bomb
{
private:
	float timeToExplode;
	float timePerFrame;
	float timeTotalOnThisFrame;
	int imageCount;

	int bombSize;
	bool placed;

	sf::Texture bomb;
	sf::RectangleShape bombBlock;

	sf::SoundBuffer bufferExplosion;
	sf::Sound explosionSound;

	void takeAwayBomb();
	void checkIfExplode(int **(&arr), int x, int y, bool left, bool right, bool up, bool down);
public:
	Bomb();
	~Bomb();

	void playBombSound();

	bool getPlaced() const;
	void setPlaced(bool placed);
	void increasBombSize();
	void setBomb(const int x,const int y);
	bool updateBobm(float deltaTime, int **(&arr), const int & WIdTH, const int & HIGHT);
	void draw(sf::RenderWindow & renderWindow);

};

#endif // !BOMB_H
