//
// test.cpp for test in /home/scutar_n/rendu/CPP/cpp_arcade/lib/sdl
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Mon Apr  3 15:41:48 2017 Nathan Scutari
// Last update Wed Apr  5 09:30:13 2017 Nathan Scutari
//

#include <iostream>
#include "IGraph.hpp"
#include "lib_sdl.hpp"
#include "gamedata.hpp"
#include <unistd.h>

int	main(void)
{
  int			x;
  int			i;
  t_block		block;
  std::vector<t_block>	grid;
  t_map		map;
  IGraph	*lib = new lib_sdl;

  /**/
  block.type = blockType::PLAYER;
  block.sprite = 0;
  block.angle = 0;
  grid.push_back(block);
  map.width = 29;
  map.height = 29;
  /**/
  i = -1;
  x = -1;
  while (++x < 28)
    {
      block.angle += 90;
      grid.push_back(block);
    }
  while (++i < 29)
    map.map.push_back(grid);
  /**/

  lib->Init("../../games/snake");
  lib->Loop_display(map);
  sleep(4);
  return (0);
}
