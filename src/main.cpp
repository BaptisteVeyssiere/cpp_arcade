//
// main.cpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Wed Mar 22 23:14:28 2017 Baptiste Veyssiere
// Last update Sun Apr  9 06:16:15 2017 Baptiste Veyssiere
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
  gamedata.up = false;
  gamedata.down = false;
  gamedata.left = false;
  gamedata.right = false;
}

void		check_lib_change(t_gamedata &gamedata, IGraph **graph, IGame **game, Core_program &core)
{
  if (gamedata.next_graph)
    {
      if (++core.graph_selector == core.graph_list.size())
	core.graph_selector = 0;
      (*graph)->Release();
      delete *graph;
      core.load_graphic_lib("lib/" + core.graph_list[core.graph_selector] + "/lib_arcade_" + core.graph_list[core.graph_selector] + ".so");
      *graph = reinterpret_cast<IGraph *(*)()>(reinterpret_cast<long>(core.get_graphic_function("factory")))();
      (*graph)->Init(core.game_list[core.game_selector]);
    }
  else if (gamedata.prev_graph)
    {
      if (--core.graph_selector < 0)
	core.graph_selector = core.graph_list.size() - 1;
      (*graph)->Release();
      delete *graph;
      core.load_graphic_lib("lib/" + core.graph_list[core.graph_selector] + "/lib_arcade_" + core.graph_list[core.graph_selector] + ".so");
      *graph = reinterpret_cast<IGraph *(*)()>(reinterpret_cast<long>(core.get_graphic_function("factory")))();
      (*graph)->Init(core.game_list[core.game_selector]);
    }
  else if (gamedata.next_game)
    {
      if (++core.game_selector == core.game_list.size())
	core.game_selector = 0;
      core.load_game_lib("games/lib_arcade_" + core.game_list[core.game_selector] + ".so");
      (*game) = reinterpret_cast<IGame *(*)()>(reinterpret_cast<long>(core.get_game_function("factory")))();
      (*game)->Get_map(gamedata.map);
      (*graph)->Release();
      (*graph)->Init(core.game_list[core.game_selector]);
    }
  else if (gamedata.prev_game)
    {
      if (--core.game_selector < 0)
	core.game_selector = core.game_list.size() - 1;
      core.load_game_lib("games/lib_arcade_" + core.game_list[core.game_selector] + ".so");
      (*game) = reinterpret_cast<IGame *(*)()>(reinterpret_cast<long>(core.get_game_function("factory")))();
      (*game)->Get_map(gamedata.map);
      (*graph)->Release();
      (*graph)->Init(core.game_list[core.game_selector]);
    }
}

static void	main_loop(const std::string &libname)
{
  Core_program	core(libname);
  t_gamedata	gamedata;
  IGraph	*graph;
  IGame		*game;
  clock_t	t;
  clock_t	previous;
  int		i;
  unsigned int	score;

  i = -1;
  while (++i >= 0 && libname.find(core.graph_list[i]) == std::string::npos);
  core.graph_selector = i;
  init_gamedata(gamedata);
  core.Display_menu();
  core.load_game_lib("games/lib_arcade_" + core.game + ".so");
  i = -1;
  while (++i >= 0 && core.game.find(core.game_list[i]) == std::string::npos);
  core.game_selector = i;
  graph = reinterpret_cast<IGraph *(*)()>(reinterpret_cast<long>(core.get_graphic_function("factory")))();
  graph->Init(core.game);
  game = reinterpret_cast<IGame *(*)()>(reinterpret_cast<long>(core.get_game_function("factory")))();
  game->Get_map(gamedata.map);
  previous = clock();
  while (gamedata.exit_game == false)
    {
      if ((score = game->Game_loop(gamedata)) != 1)
	{
	  core.Add_Score(score);
	  graph->Release();
	  std::cout << "Your score is " << score << std::endl;
	  while (core.Get_selected_game());
	  graph->Init(core.game);
	  core.load_game_lib("games/lib_arcade_" + core.game + ".so");
	  i = -1;
	  while (++i >= 0 && core.game.find(core.game_list[i]) == std::string::npos);
	  core.game_selector = i;
	  game = reinterpret_cast<IGame *(*)()>(reinterpret_cast<long>(core.get_game_function("factory")))();
	  game->Get_map(gamedata.map);
	  game->Game_loop(gamedata);
	}
      graph->Loop_display(gamedata.map);
      init_gamedata(gamedata);
      graph->Get_key(gamedata);
      check_lib_change(gamedata, &graph, &game, core);
      t = clock();
      usleep((1000000 / FPS - (t - previous)) < 0 ? 0 : (1000000 / FPS - (t - previous)));
      previous = t;
    }
  core.Save_score();
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
