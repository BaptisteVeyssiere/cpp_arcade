//
// gamedata.hpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Mar 30 00:59:21 2017 Baptiste Veyssiere
// Last update Sun Apr  2 01:08:34 2017 Baptiste Veyssiere
//

#ifndef __GAMEDATA_HPP__
# define  __GAMEDATA_HPP__

# include <cstdint>
# include <vector>
# include <cstddef>

enum class blockType : uint16_t
{
  EMPTY         = 0,
  BLOCK         = 1,
  OBSTACLE      = 2,
  EVIL_DUDE     = 3,
  EVIL_SHOOT    = 4,
  MY_SHOOT      = 5,
  POWERUP       = 6,
  PACGUM        = 7,
  SNAKTAIL      = 8,
  PLAYER        = 9
};

typedef struct                          s_map
{
  size_t                                width;
  size_t                                height;
  std::vector<std::vector<blockType>>   map;
}                                       t_map;

typedef struct	s_gamedata
{
  t_map		map;
  bool		prev_graph;
  bool		next_graph;
  bool		prev_game;
  bool		next_game;
  bool		restart;
  bool		menu;
  bool		exit_game;
}		t_gamedata;

#endif // !__GAMEDATA_HPP__
