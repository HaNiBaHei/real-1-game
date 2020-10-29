#include "stdafx.h"
#include "Game.h"

void Game::intitWindow()
{
	this->window.create(sf::VideoMode(1280,720), "Bloody Sword", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings());
	this->window.setFramerateLimit(144);
}

void Game::initPlayer()
{
	this->player = new Player();
}

Game::Game()
{
	this->intitWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollsion()
{
	// Collision bottom of screen //
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
			);
	}
}

void Game::update()
{
	// Polling Window Event
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) 
			this->window.close();

		if (this->ev.type == sf::Event::KeyReleased &&
			(
				this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S
				)
			)
		{
			this->player->resetAnimationTimer();
		}
	}

	this->updatePlayer();

	this->updateCollsion();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear(sf::Color::Blue);

	//Render game
	this->renderPlayer();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	
	return this->window;
}
