//
// lib_sdl.cpp for arcade in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Mar 25 23:29:39 2017 Nathan Scutari
// Last update Thu Apr  6 16:26:36 2017 Nathan Scutari
//

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "lib_sdl.hpp"
#include "technical_spec.hpp"
#include "library_error.hpp"

lib_sdl::lib_sdl()
{
  if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) == -1)
    throw library_error("SDL_Init failed\n");
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
    return (str.substr(pos_s + 1));
  return (str.substr(pos_s + 1, (pos_e - pos_s - 1)));
}

std::string	tile_to_file(t_block const &tile)
{
  std::string	file;
  int		value;

  value = static_cast<int>(tile.type);
  if (value == 0)
    return (file);
  file = std::to_string(value);
  file += "-";
  file += tile.sprite + 48;
  return (file);
}

bool	lib_sdl::is_map_texture(std::string file_name) const
{
  size_t	pos_s;
  int		i;

  if ((pos_s = file_name.find_last_of("-")) == std::string::npos ||
      pos_s == file_name.size() - 1 || pos_s == 0)
    return (false);
  i = -1;
  while (++i < pos_s)
    if (file_name[i] < '0' || file_name[i] > '9')
      return (false);
  while (++i < file_name.size())
    if (file_name[i] < '0' || file_name[i] > '9')
      return (false);
  return (true);
}

void	lib_sdl::resize_textures(std::map<std::string, SDL_Surface *> &textures,
				 bool &first_loop, int x_size, int y_size)
{
  double	x_resize;
  double	y_resize;
  SDL_Surface	*tmp;

  first_loop = false;
  if (textures.find("bg") == textures.end())
    throw library_error("Couldn't find background texture \"bg\"");
  for (std::map<std::string, SDL_Surface *>::iterator it = textures.begin() ;
       it != textures.end() ; ++it)
    {
      if (is_map_texture(it->first))
	{
	  tmp = it->second;
	  x_resize = static_cast<double>(x_size) / static_cast<double>(tmp->w);
	  y_resize = static_cast<double>(y_size) / static_cast<double>(tmp->h);
	  it->second = zoomSurface(tmp, x_resize, y_resize, 1);
	  SDL_FreeSurface(tmp);
	}
    }
}

void	lib_sdl::Loop_display(const t_map &map)
{
  int		y;
  int		x;
  double	x_size;
  double	y_size;
  std::string	file;
  SDL_Rect	pos;
  SDL_Surface	*tmp;

  x_size = static_cast<double>(WINSIDE) / static_cast<double>(map.width);
  y_size = static_cast<double>(WINSIDE) / static_cast<double>(map.height);
  y = -1;
  if (first_loop)
    resize_textures(textures, first_loop, x_size, y_size);
  SDL_BlitSurface(textures["bg"], NULL, win, 0);
  while (++y < map.height)
    {
      x = -1;
      while (++x < map.width)
	{
	  pos.x = static_cast<double>(x) * x_size;
	  pos.y = static_cast<double>(y) * y_size;
	  file = tile_to_file(map.map[y][x]);
	  if (file.size() > 0 && textures.find(file) == textures.end())
	    {
	      std::cout << file << std::endl;
	      throw std::exception();
	    }
	  if (file.size() > 0 && map.map[y][x].angle != 0)
	    {
	      tmp = rotozoomSurface(textures.at(file), map.map[y][x].angle, 1, 1);
	      SDL_BlitSurface(tmp, NULL, win, &pos);
	      SDL_FreeSurface(tmp);
	    }
	  else if (file.size() > 0)
	    SDL_BlitSurface(textures.at(file), NULL, win, &pos);
	}
    }
  SDL_Flip(win);
}

void	lib_sdl::Init(const std::string &game)
{
  char		center[] = "SDL_VIDEO_WINDOW_POS=center";
  std::string	file_name;
  std::vector<std::string>	files;
  SDL_Surface	*tmp;

  file_name = "games/" + game;
  get_directory_filenames(file_name, files);
  while (files.size() > 0)
    {
      file_name = get_name(files.back());
      if ((tmp = IMG_Load(files.back().c_str())) != NULL)
	textures.emplace(file_name, tmp);
      files.pop_back();
    }
  SDL_putenv(center);
  if ((win = SDL_SetVideoMode(WINSIDE, WINSIDE, 32,
			      SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    throw std::exception();
  SDL_WM_SetCaption(game.c_str(), NULL);
  first_loop = true;
}

void	lib_sdl::Get_key(t_gamedata &gamedata) const
{
  bool		*value;
  SDL_Event	event;
  int		i;
  int		key[] =
    {
      233,
      34,
      39,
      40,
      95,
      231,
      SDLK_UP,
      SDLK_DOWN,
      SDLK_RIGHT,
      SDLK_LEFT,
      SDLK_ESCAPE
    };

  if (SDL_PollEvent(&event) == 0 || event.key.state == SDL_RELEASED)
    return ;
  i = -1;
  value = static_cast<bool*>(&gamedata.prev_graph);
  while (++i < 11)
    {
      if (event.key.keysym.sym == key[i])
	value[i] = true;
    }
}

void	lib_sdl::Release()
{
  for (std::map<std::string, SDL_Surface *>::iterator it = textures.begin() ;
       it != textures.end() ; ++it)
    SDL_FreeSurface(it->second);
  SDL_Quit();
}

extern "C" IGraph	*factory()
{
  return (new lib_sdl);
}
