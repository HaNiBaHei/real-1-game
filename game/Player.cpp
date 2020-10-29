#include "stdafx.h"
#include "Player.h"

void Player::initVariable()
{
	this->animState = IDLE;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("PlayerSheet/Boss1.png"))
	{
		std::cout << "Error::PLAYER::Could not load" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 480, 480);

	this->sprite.setTextureRect(currentFrame);
	this->sprite.setScale(0.55f, 0.55f);
}

void Player::inintAnimation()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 2.f;
	this->velocityMin = 1.f;
	this->acceleration = 2.f;
	this->drag = 0.93f;
	this->gravity = 4.f;
	this->velocityMaxY = 2.f;
}

Player::Player()
{
	this->initVariable();
	this->initTexture();
	this->initSprite();
	this->inintAnimation();
	this->initPhysics();
	
}

Player::~Player()
{


}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	// Acceleration //
	this->velocity.x += dir_x * this->acceleration;
	

	// Limit velocity //
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.0f) ? -1.0f : 1.0f);

	}


}

void Player::updatePhysics()
{
	// GRAVITY //
	this->velocity.y += 1.0 * this->gravity; 
	if (std::abs(this->velocity.x) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.0f) ? -1.f : 1.f);

	}
	
	// Deceleration //
	this->velocity *= this->drag;

	// Limit deceleration //
	if (std::abs(this->velocity.x) < (this->velocityMin))
		this->velocity.x = 0.0f;
	if (std::abs(this->velocity.y) < (this->velocityMin))
		this->velocity.y = 0.0f;

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	this->animState = IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))		//left
	{
		this->move(-1.f, 0.0f);
		this->animState = MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))	//right
	{
		this->move(1.f, 0.0f);
		this->animState = MOVING_RIGHT;
	}
		
	
}

void Player::updateAnimation()
{
	if(this->animState == IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.0f;             // แถว IDLE //
			this->currentFrame.left += 480.0f;		   // frame //
			if (this->currentFrame.left >= 2880.0f)    // มีกี่ตัว //
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if(this->animState == MOVING_RIGHT)
	{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
	{
		this->currentFrame.top = 960.0f;			// แถว RUN //
		this->currentFrame.left += 480.0f;			// frame //
		if (this->currentFrame.left >= 2880.0f)		// มีกี่ตัว //
			this->currentFrame.left = 0;

	this->animationTimer.restart();
	this->sprite.setTextureRect(this->currentFrame);
	
		}
	this->sprite.setScale(0.55f, 0.55f);
	this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 960.0f;			// แถว RUN //
			this->currentFrame.left += 480.0f;			// frame //
			if (this->currentFrame.left >= 2880.0f)		// มีกี่ตัว //
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			this->sprite.setScale(-0.55f, 0.55f);
		}
		this->sprite.setScale(-0.55f, 0.55f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 0.55f, 0.f);
	}
	else 
		this->animationTimer.restart();
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimation();
	this->updatePhysics();

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(2.f);
	circ.setPosition(this->sprite.getPosition());

	target.draw(circ);
}
