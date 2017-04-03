//
// lib_sdl.cpp for arcade in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Mar 25 23:29:39 2017 Nathan Scutari
// Last update Mon Apr  3 22:57:47 2017 Nathan Scutari
//

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "lib_sdl.hpp"
#include "technical_spec.hpp"

lib_sdl::lib_sdl()
{
  if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) == -1)
    throw std::exception();
}

lib_sdl::~lib_sdl()
{
}

std::string	get_name(std::string str)
{
  size_t	pos_s;
  size_t	pos_e;
  std::string	name;

  if ((pos_s = str.find_last_of("/")) == std::string::npos)
    return (name);
  if ((pos_e = str.find_last_of(".")) == std::string::npos)
    return (name);
  return (str.substr(pos_s + 1, (pos_e - pos_s - 1)));
}

std::string	tile_to_file(t_block const &tile)
{
  std::string	file;
  int		value;

  value = static_cast<int>(tile.type);
  file = std::to_string(value);
  file += "-";
  file += tile.sprite + 48;
  std::cout << file << std::endl;
  return (file);
}

void	lib_sdl::Loop_display(const t_map &map) const
{
  int		y;
  int		x;
  int		x_size;
  int		y_size;
  std::string	file;
  SDL_Rect	pos;
  SDL_Surface	*tmp;

  x_size = WINSIDE / map.width;
  y_size = WINSIDE / map.height;
  y = -1;
  while (++y < map.height)
    {
      x = -1;
      while (++x < map.width)
	{
	  pos.x = x * x_size;
	  pos.y = y * y_size;
	  file = tile_to_file(map.map[y][x]);
	  if (textures.find(file) == textures.end())
	    throw std::exception();
	  tmp = textures.at(file);
	  SDL_BlitSurface(tmp, NULL, win, &pos);
	}
    }
  SDL_Flip(win);
}

void	lib_sdl::Init(const std::string &game)
{
  std::string	file_name;
  std::vector<std::string>	files;
  SDL_Surface	*tmp;

  get_directory_filenames(game, files);
  while (files.size() > 0)
    {
      file_name = get_name(files.back());
      if ((tmp = IMG_Load(files.back().c_str())) != NULL)
	textures.emplace(file_name, tmp);
      files.pop_back();
    }
  if ((win = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    throw std::exception();
}

void	lib_sdl::Get_key(t_gamedata &gamedata) const
{

}

void	lib_sdl::Release()
{
  for (std::map<std::string, SDL_Surface *>::iterator it = textures.begin() ;
       it != textures.end() ; ++it)
    SDL_FreeSurface(it->second);
  SDL_Quit();
}
