//
// map.hpp for arcade in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Tue Mar 21 12:05:08 2017 Nathan Scutari
// Last update Thu Mar 30 23:56:08 2017 Baptiste Veyssiere
//

#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <stdint.h>
# include <vector>

enum class blockType : uint16_t
{
  EMPTY		= 0,
  BLOCK		= 1,
  OBSTACLE	= 2,
  EVIL_DUDE	= 3,
  EVIL_SHOOT	= 4,
  MY_SHOOT	= 5,
  POWERUP	= 6,
  PACGUM	= 7,
  SNAKTAIL	= 8,
  PLAYER	= 9
};

typedef struct				s_map
{
  size_t				width;
  size_t				height;
  std::vector<std::vector<blockType>>	map;
}					t_map;

#endif // __MAP_HPP__
