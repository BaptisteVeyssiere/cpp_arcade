//
// play.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/nibbler
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Apr  6 13:49:35 2017 Baptiste Veyssiere
// Last update Mon Apr 10 00:52:34 2017 Nathan Scutari
//

# include <iostream>
# include <vector>
# include <functional>
# include "Protocol.hpp"

void	where_am_i(arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  map = map;
  direction = direction;
  (*pac)->type = arcade::CommandType::WHERE_AM_I;
  std::cout.write(reinterpret_cast<char*>((*pac)), (sizeof(uint16_t)*2)*((*pac)->lenght+1));
}

void	get_map(arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  (*pac) = (*pac);
  direction = direction;
  map->type = arcade::CommandType::GET_MAP;
  std::cout.write(reinterpret_cast<char*>(map),sizeof(uint16_t)*3 + sizeof(uint16_t)*((map->width * map->height)));
}

void	go_up(arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  (*pac) = (*pac);
  map = map;
  direction = 0;
}

void	go_right(arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  (*pac) = (*pac);
  map = map;
  direction = 1;
}

void	go_down(arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  (*pac) = (*pac);
  map = map;
  direction = 2;
}

void	go_left(arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  (*pac) = (*pac);
  map = map;
  direction = 3;
}

void	play(arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  if (direction == 0) {
    if(map->tile[((*pac)->position[0].y-1) * 20 + (*pac)->position[0].x] == arcade::TileType::EMPTY ||
       map->tile[((*pac)->position[0].y-1) * 20 + (*pac)->position[0].x] == arcade::TileType::POWERUP ||
       map->tile[((*pac)->position[0].y-1) * 20 + (*pac)->position[0].x] == arcade::TileType::EVIL_DUDE)
      --((*pac)->position[0].y);
  } else if (direction == 3) {
    if ((*pac)->position[0].x == 0)
      (*pac)->position[0].x = 28;
    else if(map->tile[(*pac)->position[0].y * 20 + (*pac)->position[0].x - 1] == arcade::TileType::EMPTY ||
       map->tile[(*pac)->position[0].y * 20 + (*pac)->position[0].x - 1] == arcade::TileType::POWERUP ||
       map->tile[(*pac)->position[0].y * 20 + (*pac)->position[0].x - 1] == arcade::TileType::EVIL_DUDE)
      --((*pac)->position[0].x);
  } else if (direction == 1) {
    if ((*pac)->position[0].x == 28)
      (*pac)->position[0].x = 0;
    else if(map->tile[(*pac)->position[0].y * 20 + (*pac)->position[0].x + 1] == arcade::TileType::EMPTY ||
       map->tile[(*pac)->position[0].y * 20 + (*pac)->position[0].x + 1] == arcade::TileType::POWERUP ||
       map->tile[(*pac)->position[0].y * 20 + (*pac)->position[0].x + 1] == arcade::TileType::EVIL_DUDE)
      ++((*pac)->position[0].x);
  } else if (direction == 2) {
    if(map->tile[((*pac)->position[0].y+1) * 20 + (*pac)->position[0].x] == arcade::TileType::EMPTY ||
       map->tile[((*pac)->position[0].y+1) * 20 + (*pac)->position[0].x] == arcade::TileType::POWERUP ||
       map->tile[((*pac)->position[0].y+1) * 20 + (*pac)->position[0].x] == arcade::TileType::EVIL_DUDE)
      ++((*pac)->position[0].y);
  }
  if (map->tile[(*pac)->position[0].y * 20 + (*pac)->position[0].x] == arcade::TileType::POWERUP)
    {
      map->tile[(*pac)->position[0].y * 20 + (*pac)->position[0].x] = arcade::TileType::EMPTY;
    }
  direction = direction;
}

void	shoot(arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  map = map;
  (*pac) = (*pac);
  direction = direction;
}

void	go_forward(arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  map = map;
  (*pac) = (*pac);
  direction = direction;
}

void	illegal(arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  map = map;
  (*pac) = (*pac);
  direction = direction;
}

void	choose_function(char ch, arcade::GetMap *map, arcade::WhereAmI **pac, char &direction)
{
  std::vector<std::function<void(arcade::GetMap*, arcade::WhereAmI**, char&)>>	ptr =
    {
      where_am_i,
      get_map,
      go_up,
      go_down,
      go_left,
      go_right,
      go_forward,
      shoot,
      illegal,
      play
    };
  std::string	symlist = "0123456789";
  for (int i = 0; i < 10; i++)
    if (ch == symlist[i])
      ptr[i](map, pac, direction);
}

void	InitMap(arcade::GetMap *gmap)
{
  std::vector<std::string>	map;

  gmap->type = arcade::CommandType::GET_MAP;
  gmap->width = 29;
  gmap->height = 29;
  map.push_back("11111111111111111111111111111");
  map.push_back("10000000000000100000000000001");
  map.push_back("10111110111110101111101111101");
  map.push_back("10061000011000000011000016001");
  map.push_back("10101011011011011011011010101");
  map.push_back("10100000000000000000000000101");
  map.push_back("10101111011111011111011110101");
  map.push_back("10000000010000000001000000001");
  map.push_back("10111111010111111101011111101");
  map.push_back("10000001000100000100010000001");
  map.push_back("11111101010001010001010111111");
  map.push_back("22222100010111211101000122222");
  map.push_back("22222101010132223101010122222");
  map.push_back("11111101010122222101010111111");
  map.push_back("00000000000122222100000000000");
  map.push_back("11111101010132223101010111111");
  map.push_back("22222101010111111101010122222");
  map.push_back("22222100010000000001000122222");
  map.push_back("11111101010111011101010111111");
  map.push_back("10000001000000000000010000001");
  map.push_back("10111111010111111101011111101");
  map.push_back("10000000010000000001000000001");
  map.push_back("10101111011111011111011110101");
  map.push_back("10100000000000000000000000101");
  map.push_back("10101011011011011011011010101");
  map.push_back("10061000011000000011000016001");
  map.push_back("10111110111110101111101111101");
  map.push_back("10000000000000100000000000001");
  map.push_back("11111111111111111111111111111");
  int	y;
  int	x;

  y = -1;
  while (++y < 29) {
    x = -1;
    while (++x < 29) {
      if (map[y][x] == '1') {
	gmap->tile[y * 29 + x] = arcade::TileType::BLOCK;
      } else if (map[y][x] == '0') {
	gmap->tile[y * 29 + x] = arcade::TileType::EMPTY;
      } else if (map[y][x] == '2') {
	gmap->tile[y * 29 + x] = arcade::TileType::OTHER;
      } else if (map[y][x] == '3') {
	gmap->tile[y * 29 + x] = arcade::TileType::EVIL_DUDE;
      } else if (map[y][x] == '6') {
	gmap->tile[y * 29 + x] = arcade::TileType::POWERUP;
      }
    }
  }
}

void	InitPosition(arcade::WhereAmI **pac)
{
  (*pac)->type = arcade::CommandType::WHERE_AM_I;
  (*pac)->lenght = 1;
  (*pac)->position[0].x = 14;
  (*pac)->position[0].y = 17;
}

extern "C" void	Play(void)
{
  arcade::GetMap	*map;
  arcade::WhereAmI	*pac;
  char			direction;
  int			ch;
  char			buff[2];

  map = new arcade::GetMap[sizeof(arcade::GetMap) + (29 * 29 * sizeof(arcade::TileType))];
  InitMap(map);
  pac = new arcade::WhereAmI[sizeof(arcade::WhereAmI) + (sizeof(arcade::Position))];
  InitPosition(&pac);
  while (std::cin.read(buff, 2) && std::cin.good() == true)
    {
      ch = *reinterpret_cast<int*>(buff);
      choose_function(ch + '0', map, &pac, direction);
    }
  delete map;
  delete pac;
}
