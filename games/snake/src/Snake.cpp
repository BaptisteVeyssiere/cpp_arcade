//
// Snake.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:41:59 2017 Baptiste Veyssiere
// Last update Sat Apr  1 14:47:41 2017 Baptiste Veyssiere
//

#include "Snake.hpp"

Snake::Snake() {}

Snake::~Snake() {}

void	Snake::Game_loop(t_map &map) const
{
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 20; j++)
      map[i][j] = '+';
}
