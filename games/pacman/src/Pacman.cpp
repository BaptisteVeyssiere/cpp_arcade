//
// Pacman.cpp for Pac in /home/scutar_n/rendu/CPP/cpp_arcade/games/pacman/src
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Fri Apr  7 17:27:31 2017 Nathan Scutari
// Last update Sat Apr  8 01:00:38 2017 Nathan Scutari
//

#include "Pacman.hpp"

Pacman::Pacman()
{
}

Pacman::~Pacman() {}

void	Pacman::Init_map(std::vector<std::string> &map)
{
  map.push_back("11111111111111111111111111111");
  map.push_back("10000000000000100000000000001");
  map.push_back("10111110111110101111101111101");
  map.push_back("10001000011000000011000010001");
  map.push_back("10101011011011011011011010101");
  map.push_back("10100000000000000000000000101");
  map.push_back("10101111011111011111011110101");
  map.push_back("10000000010000000001000000001");
  map.push_back("10111111010111111101011111101");
  map.push_back("10000001000100000100010000001");
  map.push_back("11111101010001010001010111111");
  map.push_back("00000100010111111101000100000");
  map.push_back("00000101010100000101010100000");
  map.push_back("11111101010100000101010111111");
  map.push_back("00000000000100000100000000000");
  map.push_back("11111101010100000101010111111");
  map.push_back("00000101010111111101010100000");
  map.push_back("00000100010000000001000100000");
  map.push_back("11111101010111011101010111111");
  map.push_back("10000001000000000000010000001");
  map.push_back("10111111010111111101011111101");
  map.push_back("10000000010000000001000000001");
  map.push_back("10101111011111011111011110101");
  map.push_back("10100000000000000000000000101");
  map.push_back("10101011011011011011011010101");
  map.push_back("10001000011000000011000010001");
  map.push_back("10111110111110101111101111101");
  map.push_back("10000000000000100000000000001");
  map.push_back("11111111111111111111111111111");
}

void	Pacman::Get_map(t_map &game_map)
{
  t_block			data;
  std::vector<std::string>	map;
  std::vector<t_block>		map_line;

  srand(time(NULL));
  game_map.map.clear();
  game_map.width = 29;
  game_map.height = 29;
  Init_map(map);
  data.sprite = 0;
  data.angle = 0;
  for (int y = 0 ; y < 29 ; ++y)
    {
      map_line.clear();
      for (int x = 0 ; x < 29 ; ++x)
	{
	  if (map[y][x] == '0')
	    data.type = blockType::EMPTY;
	  else
	    data.type = blockType::BLOCK;
	  map_line.push_back(data);
	}
      game_map.map.push_back(map_line);
    }
}

int	Pacman::Game_loop(t_gamedata &data)
{
  return (0);
}

extern "C" IGame	*factory()
{
  return (new Pacman);
}
