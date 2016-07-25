#include "Level.h"



Level::Level()
{
	us_startX = 0;
	us_startY = 0;

	us_width = 0;
	us_height = 0;
}


Level::~Level()
{
}

bool Level::loadFromFile(std::string level_name)
{
	std::fstream file;
	file.open("Maps/" + level_name);

	if (!file.is_open()) return false;

	file >> us_width >> us_height;
	std::cout << us_width << " "<< us_height;
	if (us_width == 0 && us_height == 0)
	{
		file.close();
		return false;
	}
	map_matrix.resize(us_height);

	for (int i = 0; i < map_matrix.size(); i++)
		map_matrix[i].resize(us_width);

	for (int y = 0; y < us_height; y++)
	{
		for (int x = 0; x < us_width; x++)
		{
			short tmp;
			file >> tmp;
			map_matrix[y][x] = getTile(tmp);
		}
	}

	while (!file.eof())
	{
		std::string name;
		file >> name;

		unsigned short x, y;
		file >> x >> y;

		if (name == "[START]")
		{
			map_matrix[y][x].str_interaction = name;

			if (us_startX == 0 && us_startY == 0)
			{
				us_startX = x;
				us_startY = y;
			}
		}

	
	}
	file.close();
	std::cout << "\nLevel.loadFromFile END" << std::endl;
	return true;

}
Level::Tile Level::getTile(short tile_id)
{

	Tile tile;
	tile.e_type = (TileType)tile_id;

	switch ((TileType)tile_id)
	{
		case Level::Grass_1:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Dirt_1:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Sand_1:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Gravel_1:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Wood_1:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Wood_2:
			tile.b_collideable = false;
			tile.b_iteractable = false;
			break;
		case Level::Wood_3:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Wood_4:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Stone_road_1:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Stone_road_2:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Stone_road_3:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Stone_road_4:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Wall_1:
			tile.b_collideable = true;
			tile.b_iteractable = false;
		break;
		case Level::Stone_floor_1:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Stone_floor_2:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		case Level::Stone_floor_3:
			tile.b_collideable = false;
			tile.b_iteractable = false;
		break;
		
		default:
		break;

		
	}
	return tile;
}