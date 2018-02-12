#ifndef TEXT_H
#define TEXT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>

class Text
{
private:
	sf::Font font;
	sf::Text text;
	int player1Score;
	int player2Score;
public:
	Text();
	~Text();

	void uppdateScore(int points, bool isPlayer2);

	void update();
	void draw(sf::RenderWindow & renderWindow);
};

#endif // !Text
