//
// Ncurses.cpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sun Mar 26 22:02:12 2017 Baptiste Veyssiere
// Last update Thu Mar 30 01:46:54 2017 Baptiste Veyssiere
//

#include "Ncurses.hpp"

Ncurses::Ncurses() {}

Ncurses::~Ncurses() {}

Ncurses::Ncurses(const Ncurses &) {}

void    check_ncurses_ret(int ret, int error, const std::string &msg)
{
  if (ret == error)
    {
      std::cout << msg << std::endl;
      throw std::exception();
    }
}

void	Ncurses::Init(const std::string &game)
{
  (void)game;
  initscr();
  check_ncurses_ret(cbreak(), ERR, CBREAK_ERROR);
  check_ncurses_ret(refresh(), ERR, REFRESH_ERROR);
  check_ncurses_ret((win = newwin(HEIGHT, WIDTH, STARTY, STARTX)) != NULL,
                     0, NEWWIN_ERROR);
  check_ncurses_ret(box(win, BOXY, BOXX), ERR, BOX_ERROR);
  check_ncurses_ret(keypad(win, true), ERR, KEYPAD_ERROR);
  check_ncurses_ret(wrefresh(win), ERR, WREFRESH_ERROR);
  check_ncurses_ret(curs_set(0), ERR, CURS_SET_ERROR);
}

void	Ncurses::Release()
{
  check_ncurses_ret(delwin(win), ERR, DELWIN_ERROR);
  check_ncurses_ret(endwin(), ERR, ENDWIN_ERROR);
}

void	Ncurses::Loop_display(const t_map &map) const
{
  std::vector<char>     sym = {' ','#','o','A','|','.','U','p','<'};

  check_ncurses_ret(wmove(win, 1, 1), ERR, WMOVE_ERROR);
  for (int i = 0; i < map.height; i++)
    {
      for (int j = 0; j < map.width; j++)
        check_ncurses_ret(waddch(win, sym[static_cast<int>(map.map[i][j])]),
			  ERR, WADDCH_ERROR);
      check_ncurses_ret(wmove(win, i + 2, 1), ERR, WMOVE_ERROR);
    }
  check_ncurses_ret(wrefresh(win), ERR, WREFRESH_ERROR);
}

void	Ncurses::Get_key(t_gamedata &gamedata) const
{
  int	ch;

  ch = getch();
  gamedata.ch = ch;
  if (ch == KEY_2)
    gamedata.prev_graph = true;
  else if (ch == KEY_3)
    gamedata.next_graph = true;
  else if (ch == KEY_4)
    gamedata.prev_game = true;
  else if (ch == KEY_5)
    gamedata.next_game = true;
  else if (ch == KEY_8)
    gamedata.restart = true;
  else if (ch == KEY_9)
    gamedata.menu = true;
  else if (ch == KEY_ESC)
    gamedata.exit_game = true;
}
