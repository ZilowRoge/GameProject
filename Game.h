#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Level.h"
const int TILE_SIZE = 32;
const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;

class Game
{
public:
	Game();
	~Game() {};
	
	void start();

public:
	void draw();
	void update(float) {};
	void setMap(std::string);
	void updateMap();


	sf::RenderWindow rw_window;
	sf::View sf_v_view;

	int i_width = 0;
	int i_height = 0;

	sf::Texture map_texture[Level::Count];

	Level c_level;
	std::vector<std::vector<sf::Sprite>> sprite_map_matrix;

	sf::Vector2f v2f_player;

};

