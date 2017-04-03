//
// Ncurses.cpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sun Mar 26 22:02:12 2017 Baptiste Veyssiere
// Last update Tue Apr  4 01:28:04 2017 Baptiste Veyssiere
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

void	Ncurses::Get_sprites(const std::string &game)
{
  std::vector<std::string>		tab;
  std::vector<std::string>::iterator	it;
  std::vector<std::string>		name =
    {
      "games/"+game+"/sprites/text/empty",
      "games/"+game+"/sprites/text/block",
      "games/"+game+"/sprites/text/obstacle",
      "games/"+game+"/sprites/text/evil_dude",
      "games/"+game+"/sprites/text/evil_shoot",
      "games/"+game+"/sprites/text/my_shoot",
      "games/"+game+"/sprites/text/powerup",
      "games/"+game+"/sprites/text/pacgum",
      "games/"+game+"/sprites/text/snaktail",
      "games/"+game+"/sprites/text/player"
    };
  int	i;

  get_directory_filenames("games/"+game+"/sprites/text/", tab);
  i = -1;
  while (++i < name.size())
    {
      if ((it = find(tab.begin(), tab.end(), name[i])) == tab.end())
	throw library_error(FIND_ERROR(name[i]));
      this->symlist += this->get_sym(name[i]);
    }
}

void	Ncurses::Init(const std::string &game)
{
  initscr();
  check_ncurses_ret(cbreak(), ERR, CBREAK_ERROR);
  check_ncurses_ret(noecho(), ERR, NOECHO_ERROR);
  check_ncurses_ret(refresh(), ERR, REFRESH_ERROR);
  check_ncurses_ret((this->win = newwin(HEIGHT, WIDTH, STARTY, STARTX)) != NULL,
                     0, NEWWIN_ERROR);
  check_ncurses_ret(box(this->win, BOXY, BOXX), ERR, BOX_ERROR);
  check_ncurses_ret(keypad(this->win, true), ERR, KEYPAD_ERROR);
  check_ncurses_ret(wrefresh(this->win), ERR, WREFRESH_ERROR);
  check_ncurses_ret(curs_set(0), ERR, CURS_SET_ERROR);
  this->Get_sprites(game);
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
        check_ncurses_ret(waddch(this->win, this->symlist[static_cast<int>(map.map[i][j].type)]),
			  ERR, WADDCH_ERROR);
      check_ncurses_ret(wmove(this->win, i + 2, 1), ERR, WMOVE_ERROR);
    }
  check_ncurses_ret(wrefresh(this->win), ERR, WREFRESH_ERROR);
}

void	Ncurses::set_prev_graph(t_gamedata &gamedata) const
{
  gamedata.prev_graph = true;
}

void	Ncurses::set_next_graph(t_gamedata &gamedata) const
{
  gamedata.next_graph = true;
}

void	Ncurses::set_prev_game(t_gamedata &gamedata) const
{
  gamedata.prev_game = true;
}

void	Ncurses::set_next_game(t_gamedata &gamedata) const
{
  gamedata.next_game = true;
}

void	Ncurses::set_restart(t_gamedata &gamedata) const
{
  gamedata.restart = true;
}

void	Ncurses::set_menu(t_gamedata &gamedata) const
{
  gamedata.menu = true;
}

void	Ncurses::set_exit_game(t_gamedata &gamedata) const
{
  gamedata.exit_game = true;
}

void	Ncurses::Get_key(t_gamedata &gamedata) const
{
  int	ch;
  std::vector<int>	keys =
    {KEY_2, KEY_3, KEY_4, KEY_5, KEY_8, KEY_9, KEY_ESC};
  std::vector<std::function<void(const Ncurses&, t_gamedata&)>> ptr =
    {
      &Ncurses::set_prev_graph,
      &Ncurses::set_next_graph,
      &Ncurses::set_prev_game,
      &Ncurses::set_next_game,
      &Ncurses::set_restart,
      &Ncurses::set_menu,
      &Ncurses::set_exit_game
    };

  ch = getch();
  for (size_t i = 0; i < keys.size(); i++)
    if (ch == keys[i])
      {
	ptr[i](*this, gamedata);
	break;
      }
}

extern "C" IGraph	*factory()
{
  return (new Ncurses);
}
