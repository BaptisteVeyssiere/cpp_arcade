//
// main.cpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Wed Mar 22 23:14:28 2017 Baptiste Veyssiere
// Last update Sat Apr  1 14:29:49 2017 Baptiste Veyssiere
//

#include "Core_program.hpp"

static void	init_gamedata(t_gamedata &data)
{
  gamedata.prev_graph = false;
  gamedata.next_graph = false;
  gamedata.prev_game = false;
  gamedata.next_game = false;
  gamedata.restart = false;
  gamedata.menu = false;
  gamedata.exit_game = false;
}

static void	main_loop(const std::string &libname)
{
  Core_program	core(libname);
  t_gamedata	data;
  IGraph	*graph;
  IGame		*game;

  init_gamedata(data);
  graph = static_cast<Igraph *()>core.get_graphic_function("factory")();
  graph->Init("");
  game = static_cast<IGame *()>core.get_game_function("factory")();
  while (data.exit_game == false)
    {
      game->Game_loop(data->map);
      graph->Loop_display();
      graph->Get_key(data);
    }
  graph->Release();
}

int	main(int ac, char **av)
{
  if (ac != 2)
    {
      std::cout << "USAGE: " << av[0] << " PATH_TO/lib_arcade_xxx.so" << std::endl;
      return (0);
    }
  main_loop(av[1]);
  return (0);
}
