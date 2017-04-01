//
// Snake.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:41:59 2017 Baptiste Veyssiere
// Last update Sun Apr  2 01:35:06 2017 Baptiste Veyssiere
//

#include "Snake.hpp"

Snake::Snake() {}

Snake::~Snake() {}

void	Snake::Game_loop(t_map &game_map) const
{
  std::vector<std::vector<blockType>>   map =
    {
      {blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK},
      {blockType::BLOCK,blockType::PACGUM,blockType::POWERUP,blockType::MY_SHOOT,blockType::EVIL_SHOOT,blockType::EVIL_DUDE,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::BLOCK},
      {blockType::BLOCK,blockType::OBSTACLE,blockType::SNAKTAIL,blockType::EMPTY,blockType::BLOCK,blockType::BLOCK,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::BLOCK},
      {blockType::BLOCK,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::BLOCK,blockType::BLOCK,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::BLOCK},
      {blockType::BLOCK,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::BLOCK,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::BLOCK},
      {blockType::BLOCK,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::BLOCK,blockType::BLOCK,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::BLOCK},
      {blockType::BLOCK,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::BLOCK,blockType::BLOCK,blockType::EMPTY,blockType::EMPTY,blockType::EMPTY,blockType::BLOCK},
      {blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK,blockType::BLOCK}
    };

  game_map.map = map;
  game_map.width = map[0].size();
  game_map.height = map.size();
}

extern "C" IGame	*factory()
{
  return (new Snake);
}
