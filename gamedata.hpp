//
// gamedata.hpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Mar 30 00:59:21 2017 Baptiste Veyssiere
// Last update Thu Mar 30 01:43:01 2017 Baptiste Veyssiere
//

#ifndef __GAME_DATA__
# define  __GAME_DATA__

#include "map.hpp"

typedef struct	s_gamedata
{
  int		ch;
  t_map		map;
  bool		prev_graph;
  bool		next_graph;
  bool		prev_game;
  bool		next_game;
  bool		restart;
  bool		menu;
  bool		exit_game;
}		t_gamedata;

#endif // !__GAME_DATA__
