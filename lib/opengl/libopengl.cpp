//
// libopengl.cpp for libopengl in /home/ilyas/rendu/CPP/cpp_arcade/lib/opengl
// 
// Made by ilyas semmaoui
// Login   <ilyas.semmaoui@epitech.eu>
// 
// Started on  Tue Apr  4 00:59:31 2017 ilyas semmaoui
// Last update Tue Apr  4 01:05:23 2017 ilyas semmaoui
//

#include <iostream>
#include <stdexcept>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "libopengl.hpp"

libopengl::libopengl() {
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw std::runtime_error("Failed to initialize libopengl !");
}

libopengl::~libopengl() {
}

std::string	libopengl::getFileName(std::string str)
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

std::string	libopengl::tile_to_file(t_block const &tile)
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

GLuint	libopengl::getTextureId(std::string const &name) {
  SDL_Surface	*surface;
  GLuint	id;

  if ((surface = IMG_Load(name.c_str())) == NULL)
    return (-1);
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0,
	       GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  SDL_FreeSurface(surface);
  return (id);
}

void	libopengl::Init(const std::string &game) {
  std::vector<std::string>	files;
  std::string			fname;
  GLuint			id;

  get_directory_filenames(game, files);
  while (files.size() > 0) {
    fname = getFileName(files.back());
    if ((id = getTextureId(files.back())) != -1)
      textures[fname] = id;
    files.pop_back();
  }
  SDL_WM_SetCaption(game.c_str(), NULL);
  if (SDL_SetVideoMode(1280, 720, 32, SDL_OPENGL) == NULL)
    throw std::runtime_error("Failed to initialize libopengl !");
  glEnable(GL_TEXTURE_2D);
}

void	libopengl::Loop_display(const t_map &map) const {

  glClear(GL_COLOR_BUFFER_BIT);
  //process
  glFlush();
  SDL_GL_SwapBuffers();
}

void	libopengl::Release() {
  SDL_Quit();
}

void	libopengl::Get_key(t_gamedata &gamedata) const {
  //SDL_PollEvent(&event);
}
