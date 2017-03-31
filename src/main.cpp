//
// main.cpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Wed Mar 22 23:14:28 2017 Baptiste Veyssiere
// Last update Fri Mar 31 14:48:38 2017 Baptiste Veyssiere
//

#include "Ncurses.hpp"

int		main(void)
{
  Ncurses	ncur;
  t_map		obj;
  t_gamedata	data;
  std::vector<std::vector<blockType>>	map =
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
  char	ch;

  data.prev_graph = false;
  data.next_graph = false;
  data.next_game = false;
  data.prev_game = false;
  data.menu = false;
  data.restart = false;
  data.exit_game = false;
  obj.height = map.size();
  obj.width = map[0].size();
  obj.map = map;
  ncur.Init("pacman");
  ncur.Loop_display(obj);
  ncur.Get_key(data);
  ncur.Release();
  if (data.prev_graph)
    std::cout << "'2' key pressed" << std::endl;
  else if (data.next_graph)
    std::cout << "'3' key pressed" << std::endl;
  else if (data.prev_game)
    std::cout << "'4' key pressed" << std::endl;
  else if (data.next_game)
    std::cout << "'5' key pressed" << std::endl;
  else if (data.restart)
    std::cout << "'8' key pressed" << std::endl;
  else if (data.menu)
    std::cout << "'9' key pressed" << std::endl;
  else if (data.exit_game)
    std::cout << "'escape' key pressed" << std::endl;
}
