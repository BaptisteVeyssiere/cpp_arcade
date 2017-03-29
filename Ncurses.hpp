//
// Ncurses.hpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sun Mar 26 22:12:35 2017 Baptiste Veyssiere
// Last update Thu Mar 30 01:44:08 2017 Baptiste Veyssiere
//

#ifndef __NCURSES_HPP__
# define __NCURSES_HPP__

# include <string>
# include <iostream>
# include <vector>
# include <ncurses.h>
# include <unistd.h>
# include "IGraph.hpp"

# define HEIGHT		25
# define WIDTH		80
# define STARTX		0
# define STARTY		0
# define BOXX		0
# define BOXY		0
# define ENDWIN_ERROR	"Error occured while calling endwin()"
# define DELWIN_ERROR	"Error occured while calling delwin()"
# define CBREAK_ERROR	"Error occured while calling cbreak()"
# define REFRESH_ERROR	"Error occured while calling refresh()"
# define NEWWIN_ERROR	"Error occured while calling newwin()"
# define BOX_ERROR	"Error occured while calling box()"
# define KEYPAD_ERROR	"Error occured while calling keypad()"
# define WREFRESH_ERROR	"Error occured while calling wrefresh()"
# define WADDCH_ERROR	"Error occured while calling waddch()"
# define WMOVE_ERROR	"Error occured while calling wmove()"
# define CURS_SET_ERROR	"Error occured while calling curs_set()"
# define KEY_ESC	27
# define KEY_2		195
# define KEY_3		34
# define KEY_4		39
# define KEY_5		40
# define KEY_8		95
# define KEY_9		195

class	Ncurses : public IGraph
{
private:
  WINDOW	*win;

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
};

#endif // !__NCURSES_HPP__
