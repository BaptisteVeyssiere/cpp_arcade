//
// gamedata.hpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Mar 30 00:59:21 2017 Baptiste Veyssiere
// Last update Tue Apr  4 21:22:47 2017 Nathan Scutari
//

#ifndef __GAMEDATA_HPP__
# define  __GAMEDATA_HPP__

# include <cstdint>
# include <vector>

# define BLOCK_NBR	10

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
  PLAYER	= 9,
};

typedef struct	s_block
{
  blockType	type;
  unsigned char	sprite;
  int		angle;
}		t_block;

typedef struct                          s_map
{
  size_t                                width;
  size_t                                height;
  std::vector<std::vector<t_block>>	map;
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