//
// Pacman.hpp for pac in /home/scutar_n/rendu/CPP/cpp_arcade/games/pacman/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Fri Apr  7 17:21:05 2017 Nathan Scutari
// Last update Sun Apr  9 21:53:35 2017 Nathan Scutari
//

#ifndef __PACMAN_HPP__
# define __PACMAN_HPP__

# include <list>
# include <iostream>
# include "IGame.hpp"
# include "game_error.hpp"
# include "technical_spec.hpp"

typedef struct	s_pos
{
  double	x;
  double	y;
}		t_pos;

typedef struct	s_node
{
  t_pos					pos;
  int					value;
  int					dist_to_end;
  int					dist_to_start;
  struct s_node				*previous;
}		t_node;

typedef struct	s_ghost
{
  double			speed;
  int			alive;
  t_pos			direction;
  std::vector<t_pos>	path;
}		t_ghost;

class	Pacman : public IGame
{
private:
  std::vector<std::string>	basic_map;
  int		frame_counter;
  t_pos		pac_pos;
  time_t	time_sec;
  int		current_direction;
  int		facing;
  int		next_direction;
  int		loop_count;
  int		killer_state;
  int		score;
  int		pacgum;
  int		begin;
  int		alive;
  int		start[4] = {0};
  int		death_sprite;
  t_pos		g_pos[4];
  t_ghost	ghost[4];
  std::list<t_node *>	open;
  std::list<t_node *>	closed;

private:
  Pacman(const Pacman &);
  Pacman &operator=(const Pacman &);

public:
  Pacman();
  virtual ~Pacman();

public:
  virtual int	Game_loop(t_gamedata &);
  virtual void	Get_map(t_map &);

private:
  void	Init_map(std::vector<std::string> &);
  void	check_next_direction(t_gamedata &);
  void	check_direction_change(t_gamedata &);
  void	update_map(t_gamedata &);
  void	check_basic_direction(t_gamedata &);
  void	check_collision(t_gamedata &);
  void	remove_block(t_gamedata &, int, int, blockType);
  void	pacman_move(t_gamedata &);
  int	get_angle();
  void	eat_pacgum(t_gamedata &);
  int	is_direction_valid(t_gamedata &);
  int	is_cross_direction(t_gamedata &);
  void	check_backward_direction(t_gamedata &);
  void	go_towards_direction(t_gamedata &);
  t_node	*pick_shortest();
  void	update_clyde(t_gamedata &);
  void	clyde_move(t_gamedata &);
  void	update_pinky(t_gamedata &);
  void	pinky_move(t_gamedata &);
  void	update_blinky(t_gamedata &);
  void	blinky_move(t_gamedata &);
  void	update_inky(t_gamedata &);
  void	inky_move(t_gamedata &);
  void	path_finder(int, int, int);
  void	go_to(int, int, int);
  t_node	*already_in_list(int, int);
  void	compare_value(t_node *, t_node *);
  void	add_to_list(t_node *, t_pos, int, int);
  void	trace_back(int);
  void	move_ghost(int);
  void	move_to_random_pos(int);
  void	move_behind_pacman(int);
  int	ghost_cross_direction(int);
  void	move_front_pacman(int);
  int	is_dead(t_gamedata &);
  int	pac_death(t_gamedata &);
  int	check_tp(t_gamedata &);
  void	find_opposite_pos(t_pos &);
  int	kill_ghost(int);
  void	tp_ghost(int);

private:
};

extern "C" IGame	*factory();

#endif // __PACMAN_HPP__
