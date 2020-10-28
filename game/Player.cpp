#include "stdafx.h"
#include "Player.h"

void Player::initVariable()
{
	this->moving = false;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("PlayerSheet/PlayerMovementSheet.png"))
	{
		std::cout << "Error::PLAYER::Could not load" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 220, 200);

	this->sprite.setTextureRect(currentFrame);
	this->sprite.setScale(0.75f, 0.75f);
}

void Player::inintAnimation()
{
	this->animationTimer.restart();
}

Player::Player()
{
	this->initVariable();
	this->initTexture();
	this->initSprite();
	this->inintAnimation();
	
}

Player::~Player()
{


}

void Player::updateMovement()
{
	this->moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))		//left
	{
		this->sprite.move(-3.0f, 0.0f);
		this->moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))	//right
	{
		this->sprite.move(3.0f, 0.0f);
		this->moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))		//up
	{
		this->sprite.move(0.0f, -3.0f);
		this->moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))	//down
	{
		this->sprite.move(0.0f, 3.0f);
		this->moving = true;
	}
}

void Player::updateAnimation()
{
	if (this->moving == false) // Idle Animation
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.left += 40.0f;
			if (this->currentFrame.left >= 880.0f)
				this->currentFrame.left = 0;
		}

		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);
		
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimation();

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

}
