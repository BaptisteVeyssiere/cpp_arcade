//
// Pacman.hpp for pac in /home/scutar_n/rendu/CPP/cpp_arcade/games/pacman/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Fri Apr  7 17:21:05 2017 Nathan Scutari
// Last update Sat Apr  8 12:31:05 2017 Nathan Scutari
//

#ifndef __PACMAN_HPP__
# define __PACMAN_HPP__

# include <iostream>
# include "IGame.hpp"
# include "game_error.hpp"
# include "technical_spec.hpp"

typedef struct	s_pos
{
  double	x;
  double	y;
}		t_pos;

class	Pacman : public IGame
{
private:
  int		frame_counter;
  t_pos		pac_pos;
  int		current_direction;
  int		next_direction;

private:
  Pacman(const Pacman &);
  Pacman &operator=(const Pacman &);

public:
  Pacman();
  virtual ~Pacman();

public:
  void	Init_map(std::vector<std::string> &);
  void	check_next_direction(t_gamedata &);
  void	check_direction_change(t_gamedata &);
  void	update_map(t_gamedata &);
  void	check_basic_direction(t_gamedata &);
  void	check_collision(t_gamedata &);
  int	is_direction_valid(t_gamedata &);
  int	is_cross_direction(t_gamedata &);
  void	check_backward_direction(t_gamedata &);
  void	go_towards_direction(t_gamedata &);
  virtual int	Game_loop(t_gamedata &);
  virtual void	Get_map(t_map &);

private:
};

extern "C" IGame	*factory();

#endif // __PACMAN_HPP__
