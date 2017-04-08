//
// Pacman.hpp for pac in /home/scutar_n/rendu/CPP/cpp_arcade/games/pacman/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Fri Apr  7 17:21:05 2017 Nathan Scutari
// Last update Fri Apr  7 22:48:13 2017 Nathan Scutari
//

#ifndef __PACMAN_HPP__
# define __PACMAN_HPP__

# include <iostream>
# include "IGame.hpp"
# include "game_error.hpp"
# include "technical_spec.hpp"

class	Pacman : public IGame
{
private:


private:
  Pacman(const Pacman &);
  Pacman &operator=(const Pacman &);

public:
  Pacman();
  virtual ~Pacman();

public:
  void	Init_map(std::vector<std::string> &);
  virtual int	Game_loop(t_gamedata &);
  virtual void	Get_map(t_map &);

private:
};

extern "C" IGame	*factory();

#endif // __PACMAN_HPP__
