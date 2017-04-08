//
// IGraph.hpp for arcade in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Tue Mar 21 11:33:44 2017 Nathan Scutari
// Last update Sat Apr  8 19:20:14 2017 ilyas semmaoui
//

#ifndef __IGRAPH_HPP__
# define __IGRAPH_HPP__

# include <string>
# include "gamedata.hpp"

class IGraph
{
public:
  virtual ~IGraph() {}

  virtual void	Init(const std::string &game) = 0;
  virtual void	Loop_display(const t_map &map) = 0;
  virtual void	Release() = 0;
  virtual void	Get_key(t_gamedata &gamedata) const = 0;
};

void	get_directory_filenames(const std::string &, std::vector<std::string> &);

#endif // __IGRAPH_HPP__
