//
// IGame.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:36:59 2017 Baptiste Veyssiere
// Last update Tue Apr  4 00:59:42 2017 Baptiste Veyssiere
//

#ifndef __IGAME_HPP__
# define __IGAME_HPP__

# include "gamedata.hpp"

class	IGame
{
public:
  virtual ~IGame() {}
  virtual void	Game_loop(t_map &) const = 0;
  virtual void	Get_map(t_map &) const = 0;
};

#endif // !__IGAME_HPP__
