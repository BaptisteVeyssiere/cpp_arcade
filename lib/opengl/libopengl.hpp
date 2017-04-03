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
  
private:

  GLuint	getTextureId(std::string const& name);
  std::string	getFileName(std::string str);
  std::string	tile_to_file(t_block const &tile);
    
public:

  libopengl();
  virtual ~libopengl();

  virtual void	Init(const std::string &game);
  virtual void	Loop_display(const t_map &map) const;
  virtual void	Release();
  virtual void	Get_key(t_gamedata &gamedata) const;
  
};

#endif
