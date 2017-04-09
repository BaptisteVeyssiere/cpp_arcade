//
// Ncurses.hpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sun Mar 26 22:12:35 2017 Baptiste Veyssiere
// Last update Sun Apr  9 16:35:49 2017 Baptiste Veyssiere
//

#ifndef __NCURSES_HPP__
# define __NCURSES_HPP__

# include <iostream>
# include <algorithm>
# include <unistd.h>
# include <fstream>
# include <ncurses.h>
# include "IGraph.hpp"
# include "library_error.hpp"
# include "technical_spec.hpp"

# define HEIGHT		40
# define WIDTH		80
# define STARTX		0
# define STARTY		0
# define BOXX		0
# define BOXY		0
# define ENDWIN_ERROR	"Error occured while calling endwin()"
# define DELWIN_ERROR	"Error occured while calling delwin()"
# define CBREAK_ERROR	"Error occured while calling cbreak()"
# define NOECHO_ERROR	"Error occured while calling noecho()"
# define REFRESH_ERROR	"Error occured while calling refresh()"
# define NEWWIN_ERROR	"Error occured while calling newwin()"
# define BOX_ERROR	"Error occured while calling box()"
# define KEYPAD_ERROR	"Error occured while calling keypad()"
# define WREFRESH_ERROR	"Error occured while calling wrefresh()"
# define WADDCH_ERROR	"Error occured while calling waddch()"
# define WMOVE_ERROR	"Error occured while calling wmove()"
# define CURS_SET_ERROR	"Error occured while calling curs_set()"
# define OPEN_ERROR	"Error occured while calling open()"
# define NODELAY_ERROR	"Error occured while calling nodelay()"
# define WPRINTW_ERROR	"Error occured while calling wprintw()"
# define GETLINE_ERROR	"Error: sprite file is empty"
# define KEY_ESC	27
# define KEY_2		169
# define KEY_3		34
# define KEY_4	        39
# define KEY_5		40
# define KEY_8		95
# define KEY_9		167

class	Ncurses : public IGraph
{
private:
  WINDOW	*win;
  std::string	symlist;

public:
  Ncurses();
  ~Ncurses();

private:
  Ncurses(const Ncurses &);
  Ncurses	&operator=(const Ncurses &);

public:
  virtual void	Init(const std::string &game);
  virtual void	Loop_display(const t_map &map) const;
  virtual void	Release();
  virtual void	Get_key(t_gamedata &gamedata) const;

private:
  void	Get_sprites(const std::string &);
  char	get_sym(const std::string &) const;
  void	Gui_display(const t_gui &) const;
  void	color_on(const t_map &, int, int, int) const;
  void	color_off(const t_map &, int, int, int) const;
};

extern "C" IGraph	*factory();

#endif // !__NCURSES_HPP__
