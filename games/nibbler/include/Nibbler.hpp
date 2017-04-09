//
// Snake.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:39:26 2017 Baptiste Veyssiere
// Last update Sun Apr  9 23:08:40 2017 Baptiste Veyssiere
//

#ifndef __NIBBLER_HPP__
# define __NIBBLER_HPP__

# include <fstream>
# include <list>
# include "IGame.hpp"
# include "game_error.hpp"
# include "technical_spec.hpp"

# define POWERUP_SCORE	42;

typedef struct	s_cell
{
  int		x;
  int		y;
}		t_cell;

class	Nibbler : public IGame
{
private:
  std::list<t_cell>	head;
  char			player_xdirection;
  char			player_ydirection;
  int			counter;
  unsigned int		score;
  int			last_key;
  time_t		start_time;
  int			end;

private:
  Nibbler(const Nibbler &);
  Nibbler &operator=(const Nibbler &);

public:
  Nibbler();
  virtual ~Nibbler();

public:
  virtual int	Game_loop(t_gamedata &);
  virtual void	Get_map(t_map &);

private:
  void	Get_file_content(std::vector<std::string> &) const;
  void	Add_mapline(const std::string &, std::vector<std::vector<std::vector<t_block>>> &) const;
  void	Add_player(t_map &);
  void	Add_cell(t_map &, unsigned int, unsigned int, float, float);
  int	check_ahead(t_map &);
  void	change_direction(t_gamedata &);
  void	move_nibbler(t_map &);
  void	move(t_map &);
  void	Add_powerup(t_map &) const;
  void	Add_block(t_block&, std::vector<std::vector<t_block>>&) const;
};

extern "C" IGame	*factory();

#endif // !__NIBBLER_HPP__
