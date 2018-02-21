#include "Blocks.h"

Blocks::Blocks()
{
	srand((unsigned)time(0));

	gameArea = new int*[WIDTH];
	for (int i = 0; i < WIDTH; i++)
	{
		gameArea[i] = new int[HIGHT];
	}
	grass1.setSize(sf::Vector2f(64.0f, 64.0f));
	grass2.setSize(sf::Vector2f(64.0f, 64.0f));
	stone.setSize(sf::Vector2f(64.0f, 64.0f));
	treeBottom.setSize(sf::Vector2f(64.0f, 64.0f));
	treeUpper.setSize(sf::Vector2f(64.0f, 64.0f));
	goFaster.setSize(sf::Vector2f(64.0f, 64.0f));
	weapon.setSize(sf::Vector2f(64.0f, 64.0f));
	
	thunder6.setSize(sf::Vector2f(64.0f, 64.0f));
	thunder7.setSize(sf::Vector2f(64.0f, 64.0f));
	thunder8.setSize(sf::Vector2f(64.0f, 64.0f));



	if (Grass1Block.loadFromFile("../Resources/block2.png"))
	{
		grass1.setTexture(&Grass1Block);
	}
	else
	{
		std::cout << "did not load grass1 texture\n";
	}

	if(treeBottomBlock.loadFromFile("../Resources/tree15.png"))
	{
		treeBottom.setTexture(&treeBottomBlock);
	}
	else
	{
		std::cout << "did not load treeBottom texture\n";
	}
	if (treeUpperBlock.loadFromFile("../Resources/tree14.png"))
	{
		treeUpper.setTexture(&treeUpperBlock);
	}
	else
	{
		std::cout << "did not load treeBottom texture\n";
	}

	if (Grass2Block.loadFromFile("../Resources/block11.png"))
	{
		grass2.setTexture(&Grass2Block);
	}
	else
	{
		std::cout << "did not load grass2 texture\n";
	}

	if (stoneBlock.loadFromFile("../Resources/block1.png"))
	{
		stone.setTexture(&stoneBlock);
	}
	else
	{
		std::cout << "did not load stone texture\n";
	}
	if (weaponBlock.loadFromFile("../Resources/block3.png"))
	{
		weapon.setTexture(&weaponBlock);
	}
	else
	{
		std::cout << "did not load weaponBlock texture\n";
	}
	if (goFasterBlock.loadFromFile("../Resources/block4.png"))
	{
		goFaster.setTexture(&goFasterBlock);
	}
	else
	{
		std::cout << "did not load goFaster texture\n";
	}
	
	if (thunder6Block.loadFromFile("../Resources/thunder6.png"))
	{
		thunder6.setTexture(&thunder6Block);
	}
	else
	{
		std::cout << "did not load thunder6 texture\n";
	}

	if (thunder7Block.loadFromFile("../Resources/thunder7.png"))
	{
		thunder7.setTexture(&thunder7Block);
	}
	else
	{
		std::cout << "did not load thunder7 texture\n";
	}

	if (thunder8Block.loadFromFile("../Resources/thunder8.png"))
	{
		thunder8.setTexture(&thunder8Block);
	}
	else
	{
		std::cout << "did not load thunder8 texture\n";
	}



	if (!bufferPowerup.loadFromFile("../Resources/PowerUp.wav"))
	{
		std::cout << "error loading power up sound\n";
	}

}

Blocks::~Blocks()
{
	for (int i = 0; i < WIDTH; i++)
	{
		delete[] gameArea[i];
	}
	delete[] gameArea;
}


void Blocks::increasBombSize(bool isPlayer2)
{
	if (isPlayer2)
	{
		bombP2.increasBombSize();
	}
	else
	{
		bombP1.increasBombSize();
	}
}

void Blocks::putDownBomb(int x, int y, bool isPlayer2)
{
	if (isPlayer2)
	{
		bombP2.setBomb(x, y);
	}
	else
	{
		bombP1.setBomb(x, y);
	}
}

bool Blocks::getPlaced()
{
	return bombP1.getPlaced() || bombP2.getPlaced();
}

void Blocks::playPowerUpSound()
{
	powerupSound.setBuffer(bufferPowerup);
	powerupSound.play();
}


void Blocks::makeGameboard()
{


	for (int y = 0; y < WIDTH; y++)
	{
		for (int x = 0; x < HIGHT; x++)
		{
			if (y == 0 || x == 0 || y == WIDTH - 1 || x == HIGHT - 1)
			{
				gameArea[y][x] = 1;
			}
			else {

				gameArea[y][x] = 2;
	
			}
		}
	}
	gameArea[WIDTH/3][HIGHT/2] = 3;
	gameArea[WIDTH / 2][HIGHT / 2] = 15;
	gameArea[WIDTH / 2][(HIGHT / 2) - 1] = 14;
	

}

bool Blocks::intersectRectangle(const float & x1, const float & y1, const float & widht1, const float & hight1, const float & x2, const float & y2, const float & widht2, const float & hight2)
{
	return x2 < x1 + widht1 &&
		x2 + widht2 > x1 &&
		y2 < y1 + hight1 &&
		y2 + hight2 > y1;
}

int Blocks::intersectRectangleCheck(const sf::Vector2f & box)
{
	int retValue = 0;
	int typeBlock = 0;
	for (int x = 0; x < WIDTH && retValue == 0; x++)
	{
		for (int y = 0; y < HIGHT && retValue == 0; y++)   //and retValue ==0
		{
			typeBlock = gameArea[x][y];
			if (typeBlock == 3 || typeBlock == 4)
			{
				if (intersectRectangle(box.x, box.y, 64, 64, x * 64 +3, y * 64 +3, 64 - 10, 64 - 10))
				{
					retValue = gameArea[x][y];
					gameArea[x][y] = 2;
					playPowerUpSound();
				}
			}
			else if (typeBlock == 1 || typeBlock == 14 || typeBlock == 15)// && typeBlock != 2 && typeBlock != 5)
			{
				if (intersectRectangle(box.x + 1, box.y + 1, 64 - 5, 64 - 5, x * 64 + 1, y * 64 + 1, 64 -5, 64 - 5))
				{
					retValue = gameArea[x][y];
				}
				
			}
		}
	}
	return retValue;
}

void Blocks::update(float deltaTime)
{
	if (bombP1.getPlaced())
	{
		bombP1.updateBobm(deltaTime, gameArea, WIDTH, HIGHT);
	}
	if (bombP2.getPlaced())
	{
		bombP2.updateBobm(deltaTime, gameArea, WIDTH, HIGHT);
	}
}

void Blocks::draw(sf::RenderWindow & renderWindow)
{
	int typeBlock = 0;
	for (int x = 0; x < WIDTH ; x++)
	{
		for (int y = 0; y < HIGHT ; y++)
		{
			typeBlock = this->gameArea[x][y];
				if (typeBlock == 2)
				{
					grass1.setPosition(sf::Vector2f((float(x * 64)), (float(y * 64))));
					renderWindow.draw(grass1);
				}
				else if (typeBlock == 0 || typeBlock == 12)
				{
					gameArea[x][y] = 2;
					grass1.setPosition(sf::Vector2f((float(x * 64)), (float(y * 64))));
					renderWindow.draw(grass1);
				}
				else if(typeBlock == 1)
				{
					stone.setOrigin(sf::Vector2f(64 / 2, 64 / 2));
					stone.setRotation(0);
					if (x == 0 && y != HIGHT -1)
					{
						stone.setRotation(90);

					}
					if (y == 0)
					{
						stone.setRotation(180);
					}
					if (x == WIDTH-1 && y != 0 && y != HIGHT -1)
					{
						stone.setRotation(180 + 90);

					}
					stone.setPosition(sf::Vector2f((float((x * 64)+32)), (float((y * 64) + 32))));
					renderWindow.draw(stone);
				}
				else if (typeBlock == 3)
				{
					weapon.setPosition(sf::Vector2f((float(x * 64)), (float(y * 64))));
					renderWindow.draw(weapon);
				}
				else if (typeBlock == 4)
				{
					goFaster.setPosition(sf::Vector2f((float(x * 64)), (float(y * 64))));
					renderWindow.draw(goFaster);
				}
				else if (typeBlock == 6)
				{
					thunder6.setPosition(sf::Vector2f((float(x * 64)), (float(y * 64))));
					renderWindow.draw(thunder6);
				}
				else if (typeBlock == 7)
				{
					thunder7.setPosition(sf::Vector2f((float(x * 64)), (float(y * 64))));
					renderWindow.draw(thunder7);
				}
				else if (typeBlock == 8)
				{
					thunder8.setPosition(sf::Vector2f((float(x * 64)), (float(y * 64))));
					renderWindow.draw(thunder8);
				}
				else if (typeBlock == 11)
				{
					grass2.setPosition(sf::Vector2f((float(x * 64)), (float(y * 64))));
					renderWindow.draw(grass2);
				}
				else if (typeBlock == 14)
				{
					treeUpper.setPosition(sf::Vector2f((float(x * 64)), (float(y * 64))));
					renderWindow.draw(treeUpper);

				}
				else if (typeBlock == 15)
				{
					treeBottom.setPosition(sf::Vector2f((float(x * 64)), (float(y * 64))));
					renderWindow.draw(treeBottom);

				}
				else
				{
					std::cout << "typeBlock: " << std::to_string(typeBlock) << '\n';
				}
				//print block on x*64 y*64
			
		}
	}
	if (bombP1.getPlaced())
	{
		bombP1.draw(renderWindow);
	}
	if (bombP2.getPlaced())
	{
		bombP2.draw(renderWindow);
	}
}

int Blocks::getHeight() const
{
	return this->HIGHT;
}

int Blocks::getWidth() const
{
	return this->WIDTH;
}

