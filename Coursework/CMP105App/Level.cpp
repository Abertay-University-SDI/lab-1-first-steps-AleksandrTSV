#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_player.setRadius(10);
	m_player.setFillColor(sf::Color::Green);
	m_player.setPosition({ 300, 300 });
}

// handle user input
void Level::handleInput(float dt)
{
	if (m_input.isLeftMousePressed())
	{
		std::cout << "left mouse pressed" << std::endl;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::D))
	{
		//m_player.move({ m_speed * dt,0.f });
		m_direction = Direction::RIGHT;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::A))
	{
		//m_player.move({ -m_speed * dt,0.f });
		m_direction = Direction::LEFT;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
	{
		//m_player.move({ 0.f,-m_speed * dt });
		m_direction = Direction::UP;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
	{
		m_direction = Direction::DOWN;
		//m_player.move({ 0.f,m_speed * dt });
	}
}

// Update game objects
void Level::update(float dt)
{
	switch (m_direction)
	{
	case Direction::UP:
		m_player.move({ 0.f,-m_speed * dt });
		break;

	case Direction::DOWN:
		m_player.move({ 0.f, m_speed * dt });
		break;

	case Direction::LEFT:
		m_player.move({ -m_speed * dt, 0.f });
		break;

	case Direction::RIGHT:
		m_player.move({ m_speed * dt, 0.f });
		break;
	}

	sf::Vector2f pos = m_player.getPosition();
	float radius = m_player.getRadius();
	sf::Vector2u windowSize = m_window.getSize();

	if (pos.x > windowSize.x - 2 * radius || pos.x < 0)
	{
		m_player.setPosition({ windowSize.x / 2.f, windowSize.y / 2.f });
	}
	if (pos.y > windowSize.y - 2 * radius || pos.y < 0)
	{
		m_player.setPosition({ windowSize.x / 2.f, windowSize.y / 2.f });
	}
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player);
	endDraw();
}

