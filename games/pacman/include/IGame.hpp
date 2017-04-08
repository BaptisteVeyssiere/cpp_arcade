//
// IGame.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:36:59 2017 Baptiste Veyssiere
// Last update Tue Apr  4 22:42:53 2017 Baptiste Veyssiere
//

#ifndef __IGAME_HPP__
# define __IGAME_HPP__

# include "gamedata.hpp"

class	IGame
{
public:
  virtual ~IGame() {}
  virtual int	Game_loop(t_gamedata &) = 0;
  virtual void	Get_map(t_map &) = 0;
};

#endif // !__IGAME_HPP__
