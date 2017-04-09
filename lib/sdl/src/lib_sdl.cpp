//
// lib_sdl.cpp for arcade in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Mar 25 23:29:39 2017 Nathan Scutari
// Last update Mon Apr 10 00:55:53 2017 Nathan Scutari
//

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "lib_sdl.hpp"
#include "technical_spec.hpp"
#include "library_error.hpp"

lib_sdl::lib_sdl()
{
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
  file += std::to_string(tile.sprite);
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
  while (++i < static_cast<int>(pos_s))
    if (file_name[i] < '0' || file_name[i] > '9')
      return (false);
  while (++i < static_cast<int>(file_name.size()))
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

void	lib_sdl::displayGui(const std::string &str1, const std::string &str2)
{
  SDL_Surface	*surf;
  SDL_Surface	*tmp;
  SDL_Color	color;
  SDL_Rect	pos;
  double	x_size;
  double	y_size;

  color.r = 255;
  color.g = 255;
  color.b = 255;
  if ((tmp = TTF_RenderText_Solid(font, str1.c_str(), color)) == NULL)
    throw library_error("TTF_RenderText_Solid failed\n");
  x_size = static_cast<double>(tmp->w) / (static_cast<double>(tmp->h) / ((static_cast<double>(GUISIDE) / 2.0) - 10.0));
  y_size = (static_cast<double>(GUISIDE) / 2.0) - 10.0;
  pos.x = 5;
  pos.y = WINSIDE + 5;
  surf = zoomSurface(tmp, x_size/tmp->w, y_size/tmp->h, 1);
  SDL_BlitSurface(surf, NULL, win, &pos);
  SDL_FreeSurface(tmp);
  SDL_FreeSurface(surf);
  if ((tmp = TTF_RenderText_Solid(font, str2.c_str(), color)) == NULL)
    throw library_error("TTF_RenderText_Solid failed\n");
  x_size = static_cast<double>(tmp->w) / (static_cast<double>(tmp->h) / ((static_cast<double>(GUISIDE) / 2.0) - 10.0));
  y_size = (static_cast<double>(GUISIDE) / 2.0) - 10.0;
  pos.x = 5;
  pos.y = WINSIDE + 10 + y_size;
  surf = zoomSurface(tmp, x_size/tmp->w, y_size/tmp->h, 1);
  SDL_BlitSurface(surf, NULL, win, &pos);
  SDL_FreeSurface(tmp);
  SDL_FreeSurface(surf);
}

void	lib_sdl::playSounds(const t_map &map)
{
  std::vector<std::string>::const_iterator	it;
  std::vector<std::string>::const_iterator	itl;
  int	i;

  if (map.sNameLoop.size() > 0 || map.sName.size() > 0) {
    i = -1;
    while (++i < static_cast<int>(soundName.size())) {
      itl = map.sNameLoop.end();
      it = map.sName.end();
      if ((itl = find(map.sNameLoop.begin(), map.sNameLoop.end(), soundName[i]))
	  != map.sNameLoop.end()) {
	if (Mix_Playing(i) == 0) {
	  Mix_PlayChannel(i, soundChunk[i], 0);
	}
      }
      if ((it = find(map.sName.begin(), map.sName.end(), soundName[i])) != map.sName.end()) {
	if (find(notLoop.begin(), notLoop.end(), i) == notLoop.end())
	  notLoop.push_back(i);
	Mix_PlayChannel(i, soundChunk[i], 0);
      }

      if (itl == map.sNameLoop.end() && find(notLoop.begin(), notLoop.end(), i) == notLoop.end()) {
	Mix_HaltChannel(i);
      }
    }
  }
}


void	lib_sdl::Loop_display(const t_map &map)
{
  int		y;
  int		x;
  int		i;
  double	x_size;
  double	y_size;
  std::string	file;
  SDL_Rect	pos;
  SDL_Surface	*tmp;

  playSounds(map);
  x_size = static_cast<double>(WINSIDE) / static_cast<double>(map.width);
  y_size = static_cast<double>(WINSIDE) / static_cast<double>(map.height);
  y = -1;
  if (first_loop)
    resize_textures(textures, first_loop, x_size, y_size);
  SDL_FillRect(win, NULL, 0x000000);
  SDL_BlitSurface(textures["bg"], NULL, win, 0);
  while (++y < static_cast<int>(map.height))
    {
      x = -1;
      while (++x < static_cast<int>(map.width))
	{
	  i = -1;
	  while (++i < static_cast<int>(map.map[y][x].size()))
		 {
		   pos.x = static_cast<double>(x) * x_size + map.map[y][x][i].shiftx * x_size;
		   pos.y = static_cast<double>(y) * y_size + map.map[y][x][i].shifty * y_size;
		   file = tile_to_file(map.map[y][x][i]);
		   if (file.size() > 0 && textures.find(file) == textures.end())
		     {
		       std::cout << file << std::endl;
		       throw std::exception();
		     }
		   if (file.size() > 0 && map.map[y][x][i].angle != 0)
		     {
		       tmp = rotozoomSurface(textures.at(file), map.map[y][x][i].angle, 1, 1);
		       SDL_BlitSurface(tmp, NULL, win, &pos);
		       SDL_FreeSurface(tmp);
		     }
		   else if (file.size() > 0)
		     SDL_BlitSurface(textures.at(file), NULL, win, &pos);
		 }
	}
    }
  displayGui("Score: " + std::to_string(map.gui.score), "Time: " + std::to_string(map.gui.sec));
  SDL_Flip(win);
}

void	lib_sdl::Init(const std::string &game)
{
  char		center[] = "SDL_VIDEO_WINDOW_POS=center";
  std::string	file_name;
  std::vector<std::string>	files;
  SDL_Surface	*tmp;
  Mix_Chunk	*music;
  int		i;


  if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) == -1)
    throw library_error("SDL_Init failed\n");
  if (TTF_Init() == -1)
    throw library_error("TTF_Init failed\n");
  if ((font = TTF_OpenFont("lib/sdl/fonts/LemonMilk.otf", 32)) == NULL)
    throw library_error("TTF_OpenFont failed\n");
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    throw library_error("Failed to initialize audio !");
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
  if ((win = SDL_SetVideoMode(WINSIDE, WINSIDE+GUISIDE, 32,
			      SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    throw std::exception();
  SDL_WM_SetCaption(game.c_str(), NULL);
  first_loop = true;
  files.clear();
  get_directory_filenames("games/"+game+"/sounds", files);
  while (files.size() > 0) {
    file_name = get_name(files.back());
    if ((music = Mix_LoadWAV(files.back().c_str())) != NULL) {
      soundName.push_back(file_name);
      soundChunk.push_back(music);
    }
    files.pop_back();
  }
  if (soundName.size() != soundChunk.size())
    throw library_error("Something went wrong !");
  if (soundName.size() > 0) {
    Mix_AllocateChannels(soundName.size());
    i = -1;
    while (++i < static_cast<int>(soundName.size()))
      Mix_Volume(i, MIX_MAX_VOLUME / 2);
  }
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
  if (event.type == SDL_QUIT) {
    value[10] = true;
    return ;
  }
  while (++i < 11)
    {
      if (event.key.keysym.sym == key[i])
	value[i] = true;
    }
}

void	lib_sdl::Release()
{
  int	i;

  i = soundChunk.size();
  while (--i >= 0) {
    if (Mix_Playing(i) == 1)
      Mix_HaltChannel(i);
    Mix_FreeChunk(soundChunk[i]);
    soundChunk.pop_back();
  }
  soundChunk.clear();
  soundName.clear();
  notLoop.clear();
  Mix_CloseAudio();
  for (std::map<std::string, SDL_Surface *>::iterator it = textures.begin() ;
       it != textures.end() ; ++it)
    SDL_FreeSurface(it->second);
  textures.clear();
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

extern "C" IGraph	*factory()
{
  return (new lib_sdl);
}
