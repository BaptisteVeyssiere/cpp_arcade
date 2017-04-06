//
// libopengl.cpp for libopengl in /home/ilyas/rendu/CPP/cpp_arcade/lib/opengl
// 
// Made by ilyas semmaoui
// Login   <ilyas.semmaoui@epitech.eu>
// 
// Started on  Tue Apr  4 00:59:31 2017 ilyas semmaoui
// Last update Thu Apr  6 15:55:02 2017 ilyas semmaoui
//

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "library_error.hpp"
#include "technical_spec.hpp"
#include "libopengl.hpp"

libopengl::libopengl() {
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw library_error("Failed to initialize libopengl !");
}

libopengl::~libopengl() {
}

std::string	libopengl::getFileName(std::string str) const {
  size_t	pos_s;
  size_t	pos_e;
  std::string	name;

  if ((pos_s = str.find_last_of("/")) == std::string::npos)
    return (name);
  if ((pos_e = str.find_last_of(".")) == std::string::npos)
    return (name);
  return (str.substr(pos_s + 1, (pos_e - pos_s - 1)));
}

std::string	libopengl::tile_to_file(t_block const &tile) const {
  std::string	file;
  int		value;

  if ((value = static_cast<int>(tile.type)) == 0)
    return ("");
  file = std::to_string(value);
  file += "-";
  file += tile.sprite + 48;
  return (file);
}

GLuint	libopengl::getTextureId(std::string const &name) const {
  SDL_Surface	*surface;
  GLuint	id;
  int		iformat;

  if ((surface = IMG_Load(name.c_str())) == NULL)
    return (-1);
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  iformat = GL_RGB;
  if (surface->format->BytesPerPixel == 4)
    iformat = GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D, 0, iformat, surface->w, surface->h, 0,
	       iformat, GL_UNSIGNED_BYTE, surface->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  SDL_FreeSurface(surface);
  return (id);
}

void	libopengl::Init(const std::string &game) {
  std::vector<std::string>	files;
  std::string			fname;
  GLuint			tmp;

  SDL_WM_SetCaption(game.c_str(), NULL);
  if (SDL_SetVideoMode(WINSIDE, WINSIDE, 32, SDL_OPENGL) == NULL)
    throw library_error("Failed to initialize libopengl !");
  glEnable(GL_TEXTURE_2D);
  get_directory_filenames("games/"+fname, files);
  while (files.size() > 0) {
    fname = getFileName(files.back());
    if ((tmp = getTextureId(files.back())) != -1)
      textures[fname] = tmp;
    files.pop_back();
  }
}

void	libopengl::Loop_display(const t_map &map) const {
  std::string	file;
  double	posx;
  double	posy;
  double	x_size;
  double	y_size;
  int		y;
  int		x;
  GLuint	tmp;
  GLdouble	angle;

  glClear(GL_COLOR_BUFFER_BIT);
  x_size = WINSIDE / map.width;
  y_size = WINSIDE / map.height;
  y = -1;
  while (++y < map.height)
    {
      x = -1;
      while (++x < map.width)
	{
	  posx = (x * x_size) * 2 / WINSIDE;
	  posy = (y * y_size) * 2 / WINSIDE;
	  if ((file = this->tile_to_file(map.map[y][x])) != "")
	    {
	      if (textures.find(file) == textures.end())
		throw library_error("Failed to find a texture !");
	      tmp = textures.at(file);
	      glBindTexture(GL_TEXTURE_2D, tmp);
	      angle = map.map[y][x].angle;
	      glPushMatrix();
	      glRotatef(angle, 0.0, 0.0, 1.0);
	      glMatrixMode(GL_MODELVIEW);
	      glBegin(GL_QUADS);
	      
	      
	      
	      
	      glTexCoord2d(0, 0);
	      glVertex2d(posx-1, (posy-1+(y_size*2/WINSIDE))*-1);
	      
	      glTexCoord2d(1, 0);
	      glVertex2d(posx-1+(x_size*2/WINSIDE), (posy-1+(y_size*2/WINSIDE))*-1);
	      
	      glTexCoord2d(1, 1);
	      glVertex2d(posx-1+(x_size*2/WINSIDE), (posy-1)*-1);

	      glTexCoord2d(0, 1);
	      glVertex2d(posx-1, (posy-1)*-1);
	      
	      glEnd();
	      glMatrixMode(GL_TEXTURE);
	      glPopMatrix();
	    }
	}
    }
  glFlush();
  SDL_GL_SwapBuffers();
}

void	libopengl::Release() {
  SDL_Quit();
}

void	libopengl::Get_key(t_gamedata &gamedata) const {
  bool		*value;
  SDL_Event	event;
  int		i;
  int		key[] =
    {
      SDLK_2,
      SDLK_3,
      SDLK_4,
      SDLK_5,
      SDLK_8,
      SDLK_9,
      SDLK_UP,
      SDLK_DOWN,
      SDLK_RIGHT,
      SDLK_LEFT,
      SDLK_ESCAPE
    };
  SDL_PollEvent(&event);
  i = -1;
  value = static_cast<bool*>(&gamedata.prev_graph);
  while (++i < 11)
    {
      if (event.key.keysym.sym == key[i])
	value[i] = true;
    }
}

extern "C" IGraph	*factory()
{
  return (new libopengl);
}
