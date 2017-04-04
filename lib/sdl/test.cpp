//
// test.cpp for test in /home/scutar_n/rendu/CPP/cpp_arcade/lib/sdl
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Mon Apr  3 15:41:48 2017 Nathan Scutari
// Last update Tue Apr  4 12:08:10 2017 Nathan Scutari
//

#include "IGraph.hpp"
#include "lib_sdl.hpp"
#include "gamedata.hpp"
#include <unistd.h>

int	main(void)
{
  t_block		block;
  std::vector<t_block>	grid;
  t_map		map;
  IGraph	*lib = new lib_sdl;

  /**/
  block.type = blockType::EMPTY;
  block.sprite = 0;
  grid.push_back(block);
  map.map.push_back(grid);
  map.width = 1;
  map.height = 1;
  /**/

  lib->Init("../../games/snake");
  lib->Loop_display(map);
  sleep(4);
  return (0);
}
