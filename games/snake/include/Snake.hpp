//
// Snake.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:39:26 2017 Baptiste Veyssiere
// Last update Sun Apr  2 01:07:32 2017 Baptiste Veyssiere
//

#ifndef __SNAKE_HPP__
# define __SNAKE_HPP__

# include "IGame.hpp"

class	Snake : public IGame
{
private:
  Snake(const Snake &);
  Snake &operator=(const Snake &);

public:
  Snake();
  virtual ~Snake();

public:
  virtual void	Game_loop(t_map &) const;
};

extern "C" IGame	*factory();

#endif // !__SNAKE_HPP__
