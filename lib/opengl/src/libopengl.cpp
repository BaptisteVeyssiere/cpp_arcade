//
// libopengl.cpp for libopengl in /home/ilyas/rendu/CPP/cpp_arcade/lib/opengl
//
// Made by ilyas semmaoui
// Login   <ilyas.semmaoui@epitech.eu>
//
// Started on  Tue Apr  4 00:59:31 2017 ilyas semmaoui
// Last update Sun Apr  9 02:58:04 2017 ilyas semmaoui
//

#include <iostream>
#include <SDL/SDL_image.h>
#include "library_error.hpp"
#include "technical_spec.hpp"
#include "libopengl.hpp"

libopengl::libopengl() {
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
  file += std::to_string(tile.sprite);
  return (file);
}

GLuint	libopengl::getFontId(std::string const &str, uint32_t &w, uint32_t &h) {
  SDL_Color		color = {255, 255, 255};
  SDL_PixelFormat	format;
  SDL_Surface		*text;
  SDL_Surface		*tmp;
  GLuint		id;
  int			iformat;

  if ((tmp = TTF_RenderText_Solid(font, str.c_str(), color)) == NULL)
    throw library_error("Failed to make text !");
  format = *(tmp->format);
  format.BitsPerPixel = 32;
  format.BytesPerPixel = 4;
  if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
    format.Rmask = 0x000000ff;
    format.Gmask = 0x0000ff00;
    format.Bmask = 0x00ff0000;
    format.Amask = 0xff000000;
  } else {
    format.Rmask = 0xff000000;
    format.Gmask = 0x00ff0000;
    format.Bmask = 0x0000ff00;
    format.Amask = 0x000000ff;
  }
  if ((text = SDL_ConvertSurface(tmp, &format, SDL_SWSURFACE)) == NULL)
    throw library_error("Failed to convert font !");
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  iformat = GL_RGB;
  if (text->format->BytesPerPixel == 4)
    iformat = GL_RGBA;
  w = text->w;
  h = text->h;
  glTexImage2D(GL_TEXTURE_2D, 0, iformat, text->w, text->h, 0,
	       iformat, GL_UNSIGNED_BYTE, text->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  SDL_FreeSurface(tmp);
  SDL_FreeSurface(text);
  return (id);
}

GLuint	libopengl::getTextureId(std::string const &name) const {
  SDL_PixelFormat	format;
  SDL_Surface		*surface;
  SDL_Surface		*tmp;
  GLuint		id;
  int			iformat;

  if ((tmp = IMG_Load(name.c_str())) == NULL)
    return (-1);
  format = *(tmp->format);
  format.BitsPerPixel = 32;
  format.BytesPerPixel = 4;
  if (SDL_BYTEORDER == SDL_LIL_ENDIAN) {
    format.Rmask = 0x000000ff;
    format.Gmask = 0x0000ff00;
    format.Bmask = 0x00ff0000;
    format.Amask = 0xff000000;
  } else {
    format.Rmask = 0xff000000;
    format.Gmask = 0x00ff0000;
    format.Bmask = 0x0000ff00;
    format.Amask = 0x000000ff;
  }
  if ((surface = SDL_ConvertSurface(tmp, &format, SDL_SWSURFACE)) == NULL)
    throw library_error("Failed to convert font !");
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  iformat = GL_RGB;
  if (surface->format->BytesPerPixel == 4)
    iformat = GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D, 0, iformat, surface->w, surface->h, 0,
	       iformat, GL_UNSIGNED_BYTE, surface->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  SDL_FreeSurface(tmp);
  SDL_FreeSurface(surface);
  return (id);
}

void	libopengl::Init(const std::string &game) {
  char		center[] = "SDL_VIDEO_WINDOW_POS=center";
  std::vector<std::string>	files;
  std::string			fname;
  GLuint			tmp;

  if (SDL_Init(SDL_INIT_VIDEO) == -1 || TTF_Init() == -1)
    throw library_error("Failed to initialize libopengl !");
  SDL_WM_SetCaption(game.c_str(), NULL);
  SDL_putenv(center);
  if (SDL_SetVideoMode(WINSIDE, WINSIDE+GUISIDE, 32, SDL_OPENGL) == NULL)
    throw library_error("Failed to initialize libopengl !");
  glEnable(GL_TEXTURE_2D);
  if ((font = TTF_OpenFont("lib/opengl/fonts/LemonMilk.otf", 32)) == NULL)
    throw library_error("Failed to load font !");
  get_directory_filenames("games/"+game, files);
  while (files.size() > 0) {
    fname = getFileName(files.back());
    if ((tmp = getTextureId(files.back())) != -1)
      textures[fname] = tmp;
    files.pop_back();
  }
}

void	libopengl::putBackground() const
{
  glBindTexture(GL_TEXTURE_2D, textures.at("bg"));
  glBegin(GL_QUADS);

  glTexCoord2d(1, 0);
  glVertex2d(1.0, 1.0);

  glTexCoord2d(0, 0);
  glVertex2d(-1.0, 1.0);

  glTexCoord2d(0, 1);
  glVertex2d(-1.0, (static_cast<double>(WINSIDE)*2.0/(static_cast<double>(WINSIDE)+static_cast<double>(GUISIDE))-1.0)*-1.0);

  glTexCoord2d(1, 1);
  glVertex2d(1.0, (static_cast<double>(WINSIDE)*2.0/(static_cast<double>(WINSIDE)+static_cast<double>(GUISIDE))-1.0)*-1.0);

  glEnd();
}

void	libopengl::displayGui(const t_map &map)
{
  GLuint	tmp;
  uint32_t	w;
  uint32_t	h;
  double	nh;
  double	nw;
  double	x;
  double	y;

  tmp = getFontId("Score: "+std::to_string(map.gui.score), w, h);
  nw = static_cast<double>(w) / (static_cast<double>(h) / ((static_cast<double>(GUISIDE) / 2.0) - 10.0));
  nh = (static_cast<double>(GUISIDE) / 2.0) - 10.0;
  nw = nw * 2.0 / static_cast<double>(WINSIDE);
  nh = nh * 2.0 / (static_cast<double>(WINSIDE) + static_cast<double>(GUISIDE));
  x = 5.0 * 2.0 / static_cast<double>(WINSIDE) - 1;
  y = (static_cast<double>(WINSIDE) + 5.0) * 2.0 / (static_cast<double>(WINSIDE) + static_cast<double>(GUISIDE)) - 1;
  glBindTexture(GL_TEXTURE_2D, tmp);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glBegin(GL_QUADS);
  glTexCoord2d(1, 0);
  glVertex2d(x+nw, y*-1);
  glTexCoord2d(0, 0);
  glVertex2d(x, y*-1);
  glTexCoord2d(0, 1);
  glVertex2d(x, (y+nh)*-1);
  glTexCoord2d(1, 1);
  glVertex2d(x+nw, (y+nh)*-1);
  glEnd();
  glDeleteTextures(1, &tmp);
  tmp = getFontId("Time: "+std::to_string(map.gui.sec), w, h);
  nw = static_cast<double>(w) / (static_cast<double>(h) / ((static_cast<double>(GUISIDE) / 2.0) - 10.0));
  nh = (static_cast<double>(GUISIDE) / 2.0) - 10.0;
  y = (static_cast<double>(WINSIDE) + 10.0 + nh) * 2.0 / (static_cast<double>(WINSIDE) + static_cast<double>(GUISIDE)) - 1;
  x = 5.0 * 2.0 / static_cast<double>(WINSIDE) - 1;
  nw = nw * 2.0 / static_cast<double>(WINSIDE);
  nh = nh * 2.0 / (static_cast<double>(WINSIDE) + static_cast<double>(GUISIDE));
  glBindTexture(GL_TEXTURE_2D, tmp);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glBegin(GL_QUADS);
  glTexCoord2d(1, 0);
  glVertex2d(x+nw, y*-1);
  glTexCoord2d(0, 0);
  glVertex2d(x, y*-1);
  glTexCoord2d(0, 1);
  glVertex2d(x, (y+nh)*-1);
  glTexCoord2d(1, 1);
  glVertex2d(x+nw, (y+nh)*-1);
  glEnd();
  glDeleteTextures(1, &tmp);
}

void	libopengl::Loop_display(const t_map &map) {
  std::string	file;
  double	posx;
  double	posy;
  double	x_size;
  double	y_size;
  int		y;
  int		x;
  int		i;
  GLuint	tmp;
  GLdouble	angle;

  glClear(GL_COLOR_BUFFER_BIT);
  x_size = static_cast<double>(WINSIDE) / static_cast<double>(map.width);
  y_size = static_cast<double>(WINSIDE) / static_cast<double>(map.height);
  if (textures.find("bg") == textures.end())
    throw library_error("Failed to find a texture !");
  putBackground();
  y = -1;
  while (++y < map.height)
    {
      x = -1;
      while (++x < map.width)
	{
	  i = -1;
	  while (++i < map.map[y][x].size()) {
	    posx = ((static_cast<double>(x) + map.map[y][x][i].shiftx) * x_size) * 2.0 / static_cast<double>(WINSIDE);
	    posy = ((static_cast<double>(y) + map.map[y][x][i].shifty) * y_size) * 2.0 / static_cast<double>(WINSIDE+GUISIDE);
	    if ((file = this->tile_to_file(map.map[y][x][i])) != "")
	      {
		if (textures.find(file) == textures.end())
		  throw library_error("Failed to find a texture !");
		tmp = textures.at(file);
		glBindTexture(GL_TEXTURE_2D, tmp);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		angle = map.map[y][x][i].angle;
		glPushMatrix();
		glRotatef(angle, 0.0, 0.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glBegin(GL_QUADS);
		glTexCoord2d(1, 0);
		glVertex2d(posx-1+(x_size*2/WINSIDE), (posy-1)*-1);
		glTexCoord2d(0, 0);
		glVertex2d(posx-1, (posy-1)*-1);
		glTexCoord2d(0, 1);
		glVertex2d(posx-1, (posy-1+(y_size*2/(WINSIDE+GUISIDE)))*-1);
		glTexCoord2d(1, 1);
		glVertex2d(posx-1+(x_size*2/WINSIDE), (posy-1+(y_size*2/(WINSIDE+GUISIDE)))*-1);
		glEnd();
		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
	      }
	  }
	}
    }
  displayGui(map);
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

extern "C" IGraph	*factory()
{
  return (new libopengl);
}
