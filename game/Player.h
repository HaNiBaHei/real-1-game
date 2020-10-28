#pragma once
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	bool moving;
	sf::Clock animationTimer;

	//Animation
	sf::IntRect currentFrame;
	//Movement 

	//core

	//hp

	void initVariable();
	void initTexture();
	void initSprite();
	void inintAnimation();

public:
	Player();
	virtual ~Player();

	//Function
	void updateMovement();
	void updateAnimation();
	void update();
	void render(sf::RenderTarget& target);
};

