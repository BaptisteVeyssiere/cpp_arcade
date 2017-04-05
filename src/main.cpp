//
// main.cpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Wed Mar 22 23:14:28 2017 Baptiste Veyssiere
// Last update Wed Apr  5 10:22:09 2017 Baptiste Veyssiere
//

#include <iostream>
#include <ctime>
#include "Core_program.hpp"
#include "IGraph.hpp"
#include "IGame.hpp"

static void	init_gamedata(t_gamedata &gamedata)
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
  t_gamedata	gamedata;
  IGraph	*graph;
  IGame		*game;
  clock_t	t;

  init_gamedata(gamedata);
  core.load_game_lib("games/snake/lib_arcade_snake.so");
  graph = reinterpret_cast<IGraph *(*)()>(reinterpret_cast<long>(core.get_graphic_function("factory")))();
  graph->Init("snake");
  game = reinterpret_cast<IGame *(*)()>(reinterpret_cast<long>(core.get_game_function("factory")))();
  game->Get_map(gamedata.map);
  t = clock();
  while (gamedata.exit_game == false)
    {
      if (game->Game_loop(gamedata))
	break;
      graph->Loop_display(gamedata.map);
      graph->Get_key(gamedata);
      t = clock() - t;
      usleep((1000000 / FPS - t) < 0 ? 0 : (1000000 / FPS - t));
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
