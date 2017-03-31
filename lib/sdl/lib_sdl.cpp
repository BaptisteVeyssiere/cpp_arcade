//
// lib_sdl.cpp for arcade in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Mar 25 23:29:39 2017 Nathan Scutari
// Last update Sun Mar 26 00:31:48 2017 Nathan Scutari
//

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include "lib_sdl.hpp"

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

void	lib_sdl::Loop_Display(const t_map &map) const
{

}

int	lib_sdl::Init(const std::string &game)
{
  int	i;
  std::string	file_name;
  char		**files;
  SDL_Surface	*tmp;

  /*  if ((files = load_textures(game)) == NULL)
      return (1);*/
  i = -1;
  while (files[++i])
    {
      file_name = get_name(files[i]);
      if ((tmp = IMG_Load(files[i])) == NULL)
	return (1);
      textures.emplace(file_name, tmp);
    }
  if ((win = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    return (1);
  return (0);
}

void	lib_sdl::Release()
{
  for (std::map<std::string, SDL_Surface *>::iterator it = textures.begin() ;
       it != textures.end() ; ++it)
    SDL_FreeSurface(it->second);
  SDL_Quit();
}
