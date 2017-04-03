//
// Snake.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:39:26 2017 Baptiste Veyssiere
// Last update Tue Apr  4 00:59:57 2017 Baptiste Veyssiere
//

#ifndef __SNAKE_HPP__
# define __SNAKE_HPP__

# include <fstream>
# include "IGame.hpp"
# include "game_error.hpp"

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
  virtual void	Get_map(t_map &) const;

private:
  void	Get_file_content(std::vector<std::string> &) const;
  void	Add_mapline(const std::string &, std::vector<std::vector<t_block>> &) const;
};

extern "C" IGame	*factory();

#endif // !__SNAKE_HPP__
