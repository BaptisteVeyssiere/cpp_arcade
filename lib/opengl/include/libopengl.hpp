#ifndef LIBOPENGL_HPP_
#define LIBOPENGL_HPP_

#include <string>
#include <unordered_map>
#include <GL/gl.h>
#include "IGraph.hpp"

class libopengl : public IGraph {

private:

  std::unordered_map<std::string,GLuint>	textures;
  SDL_Event					event;
  TTF_Font					*font;

private:

  GLuint	getFontId(std::string const& str, uint32_t &w, uint32_t &h);
  GLuint	getTextureId(std::string const& name) const;
  std::string	getFileName(std::string str) const;
  std::string	tile_to_file(t_block const &tile) const;
  void		putBackground() const;
  void		displayGui(const t_map &map);
    
public:

  libopengl();
  virtual ~libopengl();

  virtual void	Init(const std::string &game);
  virtual void	Loop_display(const t_map &map);
  virtual void	Release();
  virtual void	Get_key(t_gamedata &gamedata) const;
  
};

#endif
