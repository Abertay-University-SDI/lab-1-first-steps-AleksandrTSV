#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_player.setRadius(10.f);
	m_player.setFillColor(sf::Color::Green);
	m_player.setPosition({ 300, 300 });

	m_food.setRadius(5.f);
	m_food.setFillColor(sf::Color::Red);
	spawnFood();
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
///////////////////////////////////////////////////////////////
	sf::Vector2f player_pos = m_player.getPosition();
	float player_radius = m_player.getRadius();
	sf::Vector2u windowSize = m_window.getSize();

	if (player_pos.x > windowSize.x - 2 * player_radius || player_pos.x < 0)
	{
		m_player.setPosition({ windowSize.x / 2.f, windowSize.y / 2.f });
	}
	if (player_pos.y > windowSize.y - 2 * player_radius || player_pos.y < 0)
	{
		m_player.setPosition({ windowSize.x / 2.f, windowSize.y / 2.f });
	}
///////////////////////////////////////////////////////////////
	float x_dist = (player_pos.x + player_radius) - (m_food.getPosition().x + m_food.getRadius());
	float y_dist = (player_pos.y + player_radius) - (m_food.getPosition().y + m_food.getRadius());

	float square_dist = (x_dist * x_dist) + (y_dist * y_dist);
	float rad_sum = player_radius + m_food.getRadius();

	if (square_dist < rad_sum * rad_sum) 
	{
		spawnFood();
		m_speed *= 1.1f;
	}
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player);
	m_window.draw(m_food);
	endDraw();
}

void Level::spawnFood() 
{
	sf::Vector2u windowSize = m_window.getSize();
	float x = rand() % windowSize.x;
	float y = rand() % windowSize.y;
	m_food.setPosition({ x,y });
}

