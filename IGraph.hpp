//
// IGraph.hpp for arcade in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Tue Mar 21 11:33:44 2017 Nathan Scutari
// Last update Tue Mar 21 12:07:45 2017 Nathan Scutari
//

#ifndef __IGRAPH_HPP__
# define __IGRAPH_HPP__

#include <string>
#include "map.hpp"

class IGraph
{
public:
  virtual ~IGraph();

  virtual void	Init(const std::string &game) = 0;
  virtual void	Loop_display(const t_map &map) const = 0;
  virtual void	Release() = 0;
};

#endif // __IGRAPH_HPP__
