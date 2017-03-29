//
// IGraph.hpp for arcade in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Tue Mar 21 11:33:44 2017 Nathan Scutari
// Last update Thu Mar 30 01:53:55 2017 Baptiste Veyssiere
//

#ifndef __IGRAPH_HPP__
# define __IGRAPH_HPP__

# include <string>
# include "gamedata.hpp"

class IGraph
{
public:
  virtual ~IGraph() {}

  virtual int	Init(const std::string &game) = 0;
  virtual void	Loop_Display(const t_map &map) const = 0;
  virtual void	Release() = 0;
  virtual void	Get_key(t_gamedata &gamedata) const = 0;
};

#endif // __IGRAPH_HPP__
