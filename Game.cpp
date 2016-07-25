#include "Game.h"
#include <iostream>


Game::Game()
{
	rw_window.create(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "GameProject", sf::Style::Close);
	sf_v_view.setSize(SCR_WIDTH, SCR_HEIGHT);
	sf_v_view.setCenter(SCR_WIDTH / 2, SCR_HEIGHT / 2);

	for (int y = 0, i = 0; y < 8; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			map_texture[i].loadFromFile("Graphics/Tileset.png", sf::IntRect(sf::Vector2i(TILE_SIZE*y, TILE_SIZE*x), 
																sf::Vector2i(TILE_SIZE, TILE_SIZE)));
			i++;
		}
	}

	i_width = rw_window.getSize().x / TILE_SIZE + 2;
	i_height = rw_window.getSize().y / TILE_SIZE + 2;

	sf::Sprite standard(map_texture[0]);

	sprite_map_matrix.resize(i_height);
	for (int i = 0; i < i_height; i++)
		sprite_map_matrix[i].resize(i_width, standard);

	v2f_player = sf::Vector2f(16 * TILE_SIZE, 16 * TILE_SIZE);

	setMap("Test_map.txt");
}

void Game::setMap(std::string name)
{
	if (!c_level.loadFromFile(name))
	{
		std::cout << "Nie wczytano mapy \n";
		return;
	}
	updateMap();
	rw_window.setView(sf_v_view);
}

void Game::updateMap()
{
	sf::Vector2i fixed(v2f_player.x / TILE_SIZE, v2f_player.y / TILE_SIZE);
	player_view.setCenter(fixed.x * TILE_SIZE + TILE_SIZE / 2, fixed.y * TILE_SIZE + TILE_SIZE / 2);

	sf::Vector2f min = sf::Vector2f(player_view.getCenter().x - player_view.getSize().x / 2, player_view.getCenter().y - player_view.getSize().y / 2);

	int leftBorder = min.x / TILE_SIZE;
	int rightBorder = leftBorder + i_width;
	
	if (min.x < 0)
	{
		int difference = abs(min.x);
		min.x += difference;
		player_view.move(difference, 0);

		leftBorder = min.x / TILE_SIZE;
	}

	else if (leftBorder > 0 && rightBorder - 1 < c_level.us_width - 1)
	{
		min.x -= TILE_SIZE;
		player_view.move(-TILE_SIZE, 0);

		leftBorder = min.x / TILE_SIZE;
	}
	else if (rightBorder - 1 >= c_level.us_width - 1)
	{
		int difference = player_view.getCenter().x + player_view.getSize().x / 2 - (c_level.us_width - 1)*TILE_SIZE;
		
		difference = -difference - TILE_SIZE;
		min.x += difference;

		leftBorder = min.x / TILE_SIZE;
		player_view.setCenter((leftBorder + (i_width) / 2)*TILE_SIZE + TILE_SIZE, player_view.getCenter().y);
	}
	else if(leftBorder == 0)
		player_view.move(-TILE_SIZE / 2, 0);

	int upBorder = min.y / TILE_SIZE;
	int downBorder = upBorder + i_height;

	if (min.y < 0)
	{
		int difference = abs(min.y);
		min.y += difference;
		player_view.move(0, difference);

		upBorder = min.y / TILE_SIZE;
	}
	else if (upBorder > 0 && downBorder - 1 < c_level.us_height - 1)
	{
		min.y -= TILE_SIZE;
		player_view.move(0, -TILE_SIZE);
	}
	else if (downBorder - 1 >= c_level.us_height - 1)
	{
		int difference = player_view.getCenter().y + player_view.getSize().y / 2 - (c_level.us_height - 1)*TILE_SIZE;

		difference = -difference - TILE_SIZE;

		min.y += difference;

		upBorder = min.y / TILE_SIZE;

		player_view.setCenter(player_view.getCenter().x, (upBorder + (i_height)/ 2)*TILE_SIZE + TILE_SIZE);

		if (downBorder - 1 == c_level.us_height - 1)
			player_view.move(0, -TILE_SIZE / 2);
	}
	else if (upBorder == 0)
		player_view.move(0, -TILE_SIZE / 2);
	

	for (int y = 0, h = upBorder; y < i_height; y++)
	{
		for (int x = 0, v = leftBorder; x < i_width; x++)
		{
			sprite_map_matrix[y][x].setPosition(v*TILE_SIZE, h*TILE_SIZE);
			sprite_map_matrix[y][x].setTexture(map_texture[c_level.map_matrix[h][v].e_type]);
			v++;
		}

		h++; 
	}
	std::cout << "Player position " << v2f_player.x / TILE_SIZE << "  " << v2f_player.y / TILE_SIZE << std::endl;
	std::cout << "upBorder " << upBorder << " downBorder " << downBorder << std::endl;
	std::cout << "level height" << c_level.us_height  << std::endl;
}
void Game::draw()
{
	rw_window.clear();

	for (int y = 0; y < i_height; y++)
		for (int x = 0; x < i_width; x++)
			rw_window.draw(sprite_map_matrix[y][x]);

	rw_window.display();
}

void Game::start()
{
	sf::Time lastUpdate = sf::Time::Zero;
	sf::
		Clock time;

	while (rw_window.isOpen())
	{
		sf::Event event;
		while (rw_window.pollEvent(event))
		{
			if (event.type == event.Closed)
				rw_window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::D)
				{
					v2f_player.x += TILE_SIZE;
					sf_v_view.move(TILE_SIZE, 0);
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					v2f_player.x -= TILE_SIZE;
					sf_v_view.move(-TILE_SIZE, 0);
				}
				else if (event.key.code == sf::Keyboard::W)
				{
					v2f_player.y -= TILE_SIZE;
					sf_v_view.move(0, -TILE_SIZE);
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					v2f_player.y += TILE_SIZE;
					sf_v_view.move(0, TILE_SIZE);
				}
				updateMap();
				rw_window.setView(sf_v_view);
			}
		}

		draw();
	}
}

