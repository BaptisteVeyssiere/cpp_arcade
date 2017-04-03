//
// Ncurses.hpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sun Mar 26 22:12:35 2017 Baptiste Veyssiere
// Last update Mon Apr  3 15:06:21 2017 Baptiste Veyssiere
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

# define HEIGHT		25
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
# define FIND_ERROR(s)	"Error: sprite not found: " + s
# define GETLINE_ERROR	"Error: sprite file is empty"
# define KEY_ESC	27
# define KEY_2		505
# define KEY_3		515
# define KEY_4	        525
# define KEY_5		535
# define KEY_8		565
# define KEY_9		575

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
};

extern "C" IGraph	*factory();

#endif // !__NCURSES_HPP__
