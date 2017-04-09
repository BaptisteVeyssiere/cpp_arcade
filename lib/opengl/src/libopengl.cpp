//
// libopengl.cpp for libopengl in /home/ilyas/rendu/CPP/cpp_arcade/lib/opengl
//
// Made by ilyas semmaoui
// Login   <ilyas.semmaoui@epitech.eu>
//
// Started on  Tue Apr  4 00:59:31 2017 ilyas semmaoui
// Last update Sun Apr  9 22:54:42 2017 ilyas semmaoui
//

#include <iostream>
#include <algorithm>
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
  SDL_Color		color;
  SDL_PixelFormat	format;
  SDL_Surface		*text;
  SDL_Surface		*tmp;
  GLuint		id;
  int			iformat;

  color.r = 255;
  color.g = 255;
  color.b = 255;
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
  Mix_Chunk			*music;
  int				i;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1 || TTF_Init() == -1)
    throw library_error("Failed to initialize libopengl !");
  SDL_WM_SetCaption(game.c_str(), NULL);
  SDL_putenv(center);
  if (SDL_SetVideoMode(WINSIDE, WINSIDE+GUISIDE, 32, SDL_OPENGL) == NULL)
    throw library_error("Failed to initialize libopengl !");
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    throw library_error("Failed to initialize audio !");
  glEnable(GL_TEXTURE_2D);
  if ((font = TTF_OpenFont("lib/opengl/fonts/LemonMilk.otf", 32)) == NULL)
    throw library_error("Failed to load font !");
  get_directory_filenames("games/"+game, files);
  while (files.size() > 0) {
    fname = getFileName(files.back());
    if ((tmp = getTextureId(files.back())) != static_cast<GLuint>(-1))
      textures[fname] = tmp;
    files.pop_back();
  }
  files.clear();
  get_directory_filenames("games/"+game+"/sounds", files);
  while (files.size() > 0) {
    fname = getFileName(files.back());
    if ((music = Mix_LoadWAV(files.back().c_str())) != NULL) {
      soundName.push_back(fname);
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

void	libopengl::playSounds(const t_map &map)
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

  playSounds(map);
  glClear(GL_COLOR_BUFFER_BIT);
  x_size = static_cast<double>(WINSIDE) / static_cast<double>(map.width);
  y_size = static_cast<double>(WINSIDE) / static_cast<double>(map.height);
  if (textures.find("bg") == textures.end())
    throw library_error("Failed to find a texture !");
  putBackground();
  y = -1;
  while (++y < static_cast<int>(map.height))
    {
      x = -1;
      while (++x < static_cast<int>(map.width))
	{
	  i = -1;
	  while (++i < static_cast<int>(map.map[y][x].size())) {
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
  TTF_CloseFont(font);
  TTF_Quit();
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

extern "C" IGraph	*factory()
{
  return (new libopengl);
}
