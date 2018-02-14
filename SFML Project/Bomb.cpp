#include "Bomb.h"

void Bomb::takeAwayBomb()
{
	bombBlock.setPosition(sf::Vector2f(-64, -64)); //ha den där när ej "aktiv"
}

void Bomb::checkIfExplode(int **(&arr), int x, int y, bool left, bool right, bool up, bool down)
{
	int blockDestroy = 2;
	int blockStop = 1;
	bool stop = false;
	if (arr[x - up + down][y - right + left] == blockDestroy)// || (stop = (arr[x - up + down][y - right + left] != blockDestroy)))
	{
		arr[x - up + down][y - right+ left] = 6;

		if ( (arr[x - up*2 + down*2][y - right *2 + left*2] == blockDestroy))// || (stop = (arr[x - up*2 + down*2][y - right * 2 + left * 2] != blockDestroy))))
		{
			arr[x - up*2 + down*2][y - right * 2 + left * 2] = 6;

			if ((arr[x - up*3 + down*3][y - right * 3 + left * 3] == blockDestroy))// || (stop = (arr[x - up*3 + down*3][y - right * 3 + left * 3] != blockDestroy))))
			{
				arr[x - up*3 + down*3][y - right * 3 + left * 3] = 6;
				
				if ( (bombSize > 3) && (arr[x - up * 4 + down * 4][y - right * 4 + left *4] == blockDestroy))// || (stop = (arr[x - up * 4 + down * 4][y - right * 4 + left * 4] != blockDestroy))))
				{
					arr[x - up * 4 + down * 4][y - right * 4 + left * 4] = 6;

					if ( (bombSize > 4) && (arr[x - up * 5 + down * 5][y - right * 5 + left * 5] == blockDestroy))// || (stop = (arr[x - up * 5 + down * 5][y - right * 5 + left * 5] != blockDestroy))))
					{
						arr[x - up * 5 + down * 5][y - right * 5 + left * 5] = 6;

						if ((bombSize > 5) && (arr[x - up * 6 + down * 6][y - right * 6 + left * 6] == blockDestroy))// || (stop = (arr[x - up * 6 + down * 6][y - right * 6 + left * 6] != blockDestroy))))
						{
							arr[x - up * 6 + down * 6][y - right * 6 + left * 6] = 6;
						}
					}
				}
			}
			
		}
	}
}

Bomb::Bomb()
{
	//srand((unsigned)time(0));
	bombSize = 3;

	timeToExplode = 2;
	timePerFrame = timeToExplode/6;
	timeTotalOnThisFrame = timePerFrame; //will show the first image imiditly
	imageCount = 0;
	
	placed = false;
	bombBlock.setSize(sf::Vector2f(64, 64));
	if (bomb.loadFromFile("../Resources/block5.png"))
	{
		bombBlock.setTexture(&bomb);
	}
	bufferExplosion.loadFromFile("../Resources/bomb.wav");
	explosionSound.setVolume(20);
}

Bomb::~Bomb()
{
}

void Bomb::playBombSound() 
{
	explosionSound.setBuffer(bufferExplosion);
	explosionSound.play();
}

bool Bomb::getPlaced() const
{
	return placed;
}

void Bomb::setPlaced(bool placed)
{
	this->placed = placed;
}

void Bomb::increasBombSize()
{
	bombSize++;
}

void Bomb::setBomb(const int x,const int y)
{
	if (x != 0 && y != 0 && !placed)
	{
		bombBlock.setPosition(sf::Vector2f(x * 64, y * 64));
		placed = true;
	}
}

bool Bomb::updateBobm(float deltaTime, int **(&arr), const int & WIdTH, const int & HIGHT)
{
	bool bombExplode = false;
	//only call when placed = true

	timeToExplode -= deltaTime;

		bombExplode = true;
		
		timeTotalOnThisFrame += deltaTime;
		if (timeTotalOnThisFrame >= timePerFrame)
		{
			timeTotalOnThisFrame -= timePerFrame;
			
			if (imageCount == 0)	//put down flames
			{
				

				sf::Vector2f bombPos = bombBlock.getPosition();
				int x = (bombPos.x / 64);
				int y = (bombPos.y / 64);

				
				arr[x][y] = 6;
				
				checkIfExplode(arr, x, y, 1, 0, 0, 0);
				checkIfExplode(arr, x, y, 0, 1, 0, 0);
				checkIfExplode(arr, x, y, 0, 0, 1, 0);
				checkIfExplode(arr, x, y, 0, 0, 0, 1);

				imageCount++;

				playBombSound();
				
				bombBlock.setPosition(sf::Vector2f(-64, -64)); //ta bort bomben
			}
			else//update flames
			{
				for (int x = 0; x < WIdTH; x++)
				{
					for (int y = 0; y < HIGHT; y++)
					{
						if (arr[x][y] == 8)
						{
							arr[x][y] = 2;
							this->placed = false;
							imageCount = -1;
						}
						else if (arr[x][y] == 6 + imageCount -1)
						{
							arr[x][y] = 6 + imageCount;

						}
						
					}

				}
				imageCount++;

			}
		}
	

	
	
	return bombExplode;
}

void Bomb::draw(sf::RenderWindow & renderWindow)
{
	renderWindow.draw(bombBlock);
}




