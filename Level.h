#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
class Level
{
	public:
		bool loadFromFile(std::string);
		enum TileType
		{
			Grass_1, Dirt_1, Sand_1, Gravel_1, Wood_1, Wood_2, Wood_3,
			Wood_4, Stone_road_1, Stone_road_2, Stone_road_3, Stone_road_4,
			Wall_1, Stone_floor_1, Stone_floor_2, Stone_floor_3, Count
		};
	
		struct Tile
		{
			TileType e_type;
			std::string str_interaction;

			bool b_collideable;
			bool b_iteractable;
		};

		std::vector<std::vector<Tile>> map_matrix;

		unsigned short us_startX;
		unsigned short us_startY;


		Level();
		~Level();

		unsigned short us_width;
		unsigned short us_height;
	private:
		

		Tile getTile(short);

};

