#include "Game.h"

Game::Game()
{
	player2 = new Player(true);
	player1 = new Player(false);
	gameArea.makeGameboard();

	if (!music.openFromFile("../Resources/music.flac"))
	{
		std::cout << "music faild to open\n";
	}
	music.setLoop(true);
	music.setVolume(50);
	music.play();

}

Game::~Game()
{
	delete player2;
	delete player1;
	//delete gameboard?
}

void Game::run()
{
	float deltaTime = 0;
	sf::Clock clock;

	
	sf::RenderWindow window(sf::VideoMode(gameArea.WIDTH*64, gameArea.HIGHT*64/*416, 288*/), "!-!");
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);

				std::cout << "mouse button" << ": " << " x: " + std::to_string(position.x) << " y: " + std::to_string(position.y) << "\n";
			
				if (position.x > 456 && position.x < 507 && position.y > 527 && position.y < 567)
				{
					skill1 = true;
				}
			}

			if (sf::Event::KeyPressed)
			{
				keyEventCheck();
			}
			if (sf::Event::KeyReleased)
			{
				if (keyEventCheck() == 1)
				{
					skill1 = true;
				}
			}
			
				
		}
		if (gameArea.getPlaced())
		{
			isPlayerInExplosion();
		}
		
		updateWindow(window, deltaTime);
		
	}
}
// ret 1 for spacebar
int Game::keyEventCheck()
{
	int ret = 0;
	//player1
	player1->moveLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
	player1->moveUp(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	player1->moveDown(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
	player1->moveRight(sf::Keyboard::isKeyPressed(sf::Keyboard::D));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//få mitt pnkten av spelaren. ta de värderna dividera med 64. gör om till int. sckicka in till spelplanen att den ska visa bomb.
		sf::Vector2f position = player1->getPosition();
		position.x = (position.x + 16) / 64;
		position.y = (position.y + 16) / 64;
		gameArea.putDownBomb(position.x, position.y, 0);
		//plant bomb
		ret = 1;
	}

	//player 2
	player2->moveLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
	player2->moveUp(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
	player2->moveDown(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
	player2->moveRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		sf::Vector2f position = player2->getPosition();
		position.x = (position.x + 16) / 64;
		position.y = (position.y + 16) / 64;
		gameArea.putDownBomb(position.x, position.y, 1);
		//plant bomb
	}

	return ret;
}

void Game::canPlayersMove(float deltaTime)
{
	int tutchP1 = 0;
	int tutchP2 = 0;
	//player 1
	if (player1->getLeft())
	{

		 tutchP1 = gameArea.intersectRectangleCheck(player1->getPosition());
		
		if (tutchP1 == 1 || tutchP1 == 2 || tutchP1 == 14 || tutchP1 == 15)
		{
			player1->moveRight(deltaTime);
		}
	}
	if (player1->getRight())
	{
		 tutchP1 = gameArea.intersectRectangleCheck(player1->getPosition());
		
		if (tutchP1 == 1 || tutchP1 == 2 || tutchP1 == 14 || tutchP1 == 15)
		{
			player1->moveLeft(deltaTime);
		}
		
	}
	if (player1->getUp())
	{
		
	
		 tutchP1 = gameArea.intersectRectangleCheck(player1->getPosition());
		
		
			if (tutchP1 == 1 || tutchP1 == 2 || tutchP1 == 14 || tutchP1 == 15)
			{
				player1->moveDown(deltaTime);
			}
		
		
	}
	if (player1->getDown())
	{
		tutchP1 = gameArea.intersectRectangleCheck(player1->getPosition());
		
			if (tutchP1 == 1 || tutchP1 == 2 || tutchP1 == 14 || tutchP1 == 15)
			{
				player1->moveUp(deltaTime);
			}
			
	}

	if (tutchP1 == 3)
	{
		P1_IncreasSpeed();
	}
	if (tutchP1 == 4)
	{
		gameArea.increasBombSize(false);
		score.uppdateScore(50, 0);
	}

	//player 2
	if (player2->getLeft())
	{
		tutchP2 = gameArea.intersectRectangleCheck(player2->getPosition());
		
		if (tutchP2 == 1 || tutchP2 == 2 || tutchP2 == 14 || tutchP2 == 15)
		{
			player2->moveRight(deltaTime);
		}
			
	}
	if (player2->getUp())
	{
		tutchP2 = gameArea.intersectRectangleCheck(player2->getPosition());
		
		if (tutchP2 == 1 || tutchP2 == 2 || tutchP2 == 14 || tutchP2 == 15)
		{
			player2->moveDown(deltaTime);
		}
	}
	if (player2->getDown())
	{
		tutchP2 = gameArea.intersectRectangleCheck(player2->getPosition());

		if (tutchP2 == 1 || tutchP2 == 2 || tutchP2 == 14 || tutchP2 == 15)
		{
			player2->moveUp(deltaTime);
		}
	}
	if (player2->getRight())
	{
		tutchP2 = gameArea.intersectRectangleCheck(player2->getPosition());
		
		if (tutchP2 == 1 || tutchP2 == 2 || tutchP2 == 14 || tutchP2 == 15)
		{
			player2->moveLeft(deltaTime);
		}
	}

	
	if (tutchP2 == 3)
	{
		P2_IncreasSpeed();
	}
	if (tutchP2 == 4)
	{
		gameArea.increasBombSize(true);
		score.uppdateScore(50, 1);
	}
	
}

void Game::isPlayerInExplosion()
{
	
		if (gameArea.intersectRectangleCheck(player1->getPosition()) >= 6)
		{
			player1->killPlayer();
			score.uppdateScore(200, 1);
		}

		if (gameArea.intersectRectangleCheck(player2->getPosition()) >= 6)
		{
			player2->killPlayer();
			score.uppdateScore(200, 0);
		}
	
}

void Game::P1_IncreasSpeed()
{
	player1->increasSpeed();
	score.uppdateScore(50, 0);
}

void Game::P1_IncreasBombSize()
{
	gameArea.increasBombSize(false);
	score.uppdateScore(50, 0);

}

void Game::P2_IncreasSpeed()
{
	gameArea.increasBombSize(true);
	score.uppdateScore(50, 1);

}

void Game::P2_IncreasBombSize()
{
	player2->increasBombSize();
	score.uppdateScore(50, 1);
}


void Game::updateWindow(sf::RenderWindow &renderWindow, float deltaTime)
{
	renderWindow.clear();
		
	player1->update(deltaTime);
	player2->update(deltaTime);
	canPlayersMove(deltaTime);

	
	gameArea.update(deltaTime);
	gameArea.draw(renderWindow);

	player2->draw(renderWindow);
	player1->draw(renderWindow);
	
	if (skill1)
	{
		skill1 = inv.updateSkill1(deltaTime);
	}
	inv.draw(renderWindow, gameArea.getHeight(), gameArea.getWidth());

	menRow.draw(renderWindow);
	
	score.update();
	score.draw(renderWindow);
	
	renderWindow.display();
}
