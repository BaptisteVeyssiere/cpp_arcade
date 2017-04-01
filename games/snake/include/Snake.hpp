//
// Snake.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:39:26 2017 Baptiste Veyssiere
// Last update Sat Apr  1 14:41:24 2017 Baptiste Veyssiere
//

#ifndef __SNAKE_HPP__
# define __SNAKE_HPP__

class	Snake
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

#endif // !__SNAKE_HPP__
