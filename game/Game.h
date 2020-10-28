#pragma once
#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;

	void intitWindow();
	void initPlayer();

public:
	//function

	Game();
	virtual ~Game();

	//fucntion
	void updatePlayer();
	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;
};

