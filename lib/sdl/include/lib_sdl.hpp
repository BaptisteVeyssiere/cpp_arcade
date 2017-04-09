//
// lib_sdl.hpp for arcade in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Tue Mar 21 11:33:44 2017 Nathan Scutari
// Last update Sun Apr  9 01:20:55 2017 ilyas semmaoui
//

#ifndef __LIB_SDL_HPP__
# define __LIB_SDL_HPP__

#include <map>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "IGraph.hpp"
#include "gamedata.hpp"

class lib_sdl : public IGraph
{
  bool					first_loop;
  std::map<std::string, SDL_Surface *>	textures;
  SDL_Surface				*win;
  TTF_Font				*font;

private:
  lib_sdl(lib_sdl &other);
  lib_sdl	&operator=(lib_sdl &other);

  void		displayGui(const std::string &str1, const std::string &str2);
  
public:
  lib_sdl();
  virtual ~lib_sdl();

  void	Init(const std::string &game);
  void	Loop_display(const t_map &map);
  void	Get_key(t_gamedata &gamedata) const;
  bool	is_map_texture(std::string file_name) const;
  void	resize_textures(std::map<std::string, SDL_Surface *> &textures,
			bool &first_loop, int x_size, int y_size);
  void	Release();
};

#endif // __LIB_SDL_HPP__
