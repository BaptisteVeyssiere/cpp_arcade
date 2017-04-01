//
// Ncurses.cpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sun Mar 26 22:02:12 2017 Baptiste Veyssiere
// Last update Sun Apr  2 01:17:55 2017 Baptiste Veyssiere
//

#include "Ncurses.hpp"

Ncurses::Ncurses() {}

Ncurses::~Ncurses() {}

Ncurses::Ncurses(const Ncurses &) {}

void    check_ncurses_ret(int ret, int error, const std::string &msg)
{
  if (ret == error)
    throw library_error(msg);
}

char	Ncurses::get_sym(const std::string &name) const
{
  std::ifstream	filestream;
  std::string	line;

  filestream.open(name);
  if (!(filestream.is_open()))
    throw library_error(OPEN_ERROR);
  getline(filestream, line);
  if (line.size() < 1)
    throw library_error(GETLINE_ERROR);
  return (line[0]);
}

void	Ncurses::Get_sprites()
{
  std::vector<std::string>		tab;
  std::vector<std::string>::iterator	it;
  std::vector<std::string>		name =
    {
      "empty",
      "block",
      "obstacle",
      "evil_dude",
      "evil_shoot",
      "my_shoot",
      "power_up",
      "pacgum",
      "snaktail",
      "player"
    };
  int	i;

  get_directory_filenames("ncurses/sprites", tab);
  i = -1;
  while (++i < 10)
    {
      if ((it = find(tab.begin(), tab.end(), name[i])) == tab.end())
	throw library_error(FIND_ERROR);
      this->symlist += this->get_sym(name[i]);
    }
}

void	Ncurses::Init(const std::string &game)
{
  (void)game;
  initscr();
  check_ncurses_ret(cbreak(), ERR, CBREAK_ERROR);
  check_ncurses_ret(refresh(), ERR, REFRESH_ERROR);
  check_ncurses_ret((this->win = newwin(HEIGHT, WIDTH, STARTY, STARTX)) != NULL,
                     0, NEWWIN_ERROR);
  check_ncurses_ret(box(this->win, BOXY, BOXX), ERR, BOX_ERROR);
  check_ncurses_ret(keypad(this->win, true), ERR, KEYPAD_ERROR);
  check_ncurses_ret(wrefresh(this->win), ERR, WREFRESH_ERROR);
  check_ncurses_ret(curs_set(0), ERR, CURS_SET_ERROR);
  timeout(1000);
}

void	Ncurses::Release()
{
  check_ncurses_ret(delwin(this->win), ERR, DELWIN_ERROR);
  check_ncurses_ret(endwin(), ERR, ENDWIN_ERROR);
}

void	Ncurses::Loop_display(const t_map &map) const
{
  check_ncurses_ret(wmove(this->win, 1, 1), ERR, WMOVE_ERROR);
  for (size_t i = 0; i < map.height; i++)
    {
      for (size_t j = 0; j < map.width; j++)
        check_ncurses_ret(waddch(this->win, this->symlist[static_cast<int>(map.map[i][j])]),
			  ERR, WADDCH_ERROR);
      check_ncurses_ret(wmove(this->win, i + 2, 1), ERR, WMOVE_ERROR);
    }
  check_ncurses_ret(wrefresh(this->win), ERR, WREFRESH_ERROR);
}

void	Ncurses::Get_key(t_gamedata &gamedata) const
{
  int	ch;

  ch = getch();
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

extern "C" IGraph	*factory()
{
  return (new Ncurses);
}
