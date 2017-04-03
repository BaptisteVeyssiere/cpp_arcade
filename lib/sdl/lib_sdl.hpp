//
// lib_sdl.hpp for arcade in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Tue Mar 21 11:33:44 2017 Nathan Scutari
// Last update Mon Apr  3 15:44:33 2017 Nathan Scutari
//

#ifndef __LIB_SDL_HPP__
# define __LIB_SDL_HPP__

#include <map>
#include <string>
#include <SDL/SDL.h>
#include "IGraph.hpp"
#include "gamedata.hpp"

class lib_sdl : public IGraph
{
  std::map<std::string, SDL_Surface *>	textures;
  SDL_Surface				*win;

private:
  lib_sdl(lib_sdl &other);
  lib_sdl	&operator=(lib_sdl &other);

public:
  lib_sdl();
  virtual ~lib_sdl();

  void	Init(const std::string &game);
  void	Loop_display(const t_map &map) const;
  void	Get_key(t_gamedata &gamedata) const;
  void	Release();
};

#endif // __LIB_SDL_HPP__
