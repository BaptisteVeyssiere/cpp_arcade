//
// Ncurses.cpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sun Mar 26 22:02:12 2017 Baptiste Veyssiere
// Last update Sun Apr  9 18:20:12 2017 Baptiste Veyssiere
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

  this->symlist.clear();
  get_directory_filenames("games/"+game+"/sprites/text/", tab);
  i = -1;
  while (++i < name.size())
    {
      if ((it = find(tab.begin(), tab.end(), name[i])) == tab.end())
	this->symlist += static_cast<char>(0);
      else
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
  check_ncurses_ret(keypad(stdscr, true), ERR, KEYPAD_ERROR);
  check_ncurses_ret(wrefresh(this->win), ERR, WREFRESH_ERROR);
  check_ncurses_ret(curs_set(0), ERR, CURS_SET_ERROR);
  this->Get_sprites(game);
  check_ncurses_ret(nodelay(stdscr, true), ERR, NODELAY_ERROR);
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLUE);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_BLUE, COLOR_BLACK);
}

void	Ncurses::Release()
{
  check_ncurses_ret(delwin(this->win), ERR, DELWIN_ERROR);
  check_ncurses_ret(endwin(), ERR, ENDWIN_ERROR);
}

void	Ncurses::Gui_display(const t_gui &gui) const
{
  int	x;
  int	y;

  getyx(this->win, y, x);
  check_ncurses_ret(wprintw(this->win, "Score: %u", gui.score), ERR, WPRINTW_ERROR);
  check_ncurses_ret(wmove(this->win, y + 1, 1), ERR, WMOVE_ERROR);
  check_ncurses_ret(wprintw(this->win, "Time: %02u:%02u", gui.sec / 60, gui.sec % 60), ERR, WPRINTW_ERROR);
}

void	Ncurses::color_on(const t_map &map, int i, int j, int k) const
{
  if (map.map[i][j][k].type == blockType::EVIL_DUDE && map.map[i][j][k].sprite == 2)
    wattron(this->win, COLOR_PAIR(6));
  if (map.map[i][j][k].type == blockType::EVIL_DUDE && map.map[i][j][k].sprite == 0)
    wattron(this->win, COLOR_PAIR(2));
  if (map.map[i][j][k].type == blockType::EVIL_DUDE && map.map[i][j][k].sprite == 4)
    wattron(this->win, COLOR_PAIR(3));
  if (map.map[i][j][k].type == blockType::EVIL_DUDE && map.map[i][j][k].sprite == 8)
    wattron(this->win, COLOR_PAIR(4));
  if (map.map[i][j][k].type == blockType::EVIL_DUDE && map.map[i][j][k].sprite == 12)
    wattron(this->win, COLOR_PAIR(5));
  if (map.map[i][j][k].type == blockType::EMPTY)
    wattron(this->win, COLOR_PAIR(6));
}

void	Ncurses::color_off(const t_map &map, int i, int j, int k) const
{
  if (map.map[i][j][k].type == blockType::EVIL_DUDE && map.map[i][j][k].sprite == 2)
    wattroff(this->win, COLOR_PAIR(6));
  if (map.map[i][j][k].type == blockType::EVIL_DUDE && map.map[i][j][k].sprite == 0)
    wattroff(this->win, COLOR_PAIR(2));
  if (map.map[i][j][k].type == blockType::EVIL_DUDE && map.map[i][j][k].sprite == 4)
    wattroff(this->win, COLOR_PAIR(3));
  if (map.map[i][j][k].type == blockType::EVIL_DUDE && map.map[i][j][k].sprite == 8)
    wattroff(this->win, COLOR_PAIR(4));
  if (map.map[i][j][k].type == blockType::EVIL_DUDE && map.map[i][j][k].sprite == 12)
    wattroff(this->win, COLOR_PAIR(5));
  if (map.map[i][j][k].type == blockType::EMPTY)
    wattroff(this->win, COLOR_PAIR(6));
}

void	Ncurses::Loop_display(const t_map &map) const
{
  int	x;
  int	y;

  check_ncurses_ret(wmove(this->win, 1, 1), ERR, WMOVE_ERROR);
  for (size_t i = 0; i < map.height; i++)
    {
      for (size_t j = 0; j < map.width; j++)
	{
	  if (map.map[i][j][0].type == blockType::BLOCK)
	    {
	      wattron(this->win, COLOR_PAIR(1));
	      check_ncurses_ret(waddch(this->win, this->symlist[static_cast<int>(map.map[i][j][0].type)]),
				ERR, WADDCH_ERROR);
	      check_ncurses_ret(waddch(this->win, this->symlist[static_cast<int>(map.map[i][j][0].type)]),
				ERR, WADDCH_ERROR);
	      wattroff(this->win, COLOR_PAIR(1));
	    }
	  else
	    {
	      for (size_t k = 0; k < map.map[i][j].size(); k++)
		{
		  this->color_on(map, i, j, k);
		  getyx(this->win, y, x);
		  check_ncurses_ret(waddch(this->win, this->symlist[static_cast<int>(map.map[i][j][k].type)]),
				    ERR, WADDCH_ERROR);
		  check_ncurses_ret(waddch(this->win, ' '), ERR, WADDCH_ERROR);
		  if ((k + 1) < map.map[i][j].size())
		    check_ncurses_ret(wmove(this->win, y, x), ERR, WMOVE_ERROR);
		  this->color_off(map, i, j, k);
		}

	    }
	}
      check_ncurses_ret(wmove(this->win, i + 2, 1), ERR, WMOVE_ERROR);
    }
  this->Gui_display(map.gui);
  check_ncurses_ret(wrefresh(this->win), ERR, WREFRESH_ERROR);
}

void	Ncurses::Get_key(t_gamedata &gamedata) const
{
  int	ch;
  bool	*value;
  std::vector<int>	keys =
    {
      KEY_2,
      KEY_3,
      KEY_4,
      KEY_5,
      KEY_8,
      KEY_9,
      KEY_UP,
      KEY_DOWN,
      KEY_RIGHT,
      KEY_LEFT,
      KEY_ESC
    };

  ch = getch();
  value = static_cast<bool*>(&gamedata.prev_graph);
  for (size_t i = 0; i < keys.size(); i++)
    if (ch == keys[i])
      {
	value[i] = true;
	i = keys.size();
      }
}

extern "C" IGraph	*factory()
{
  return (new Ncurses);
}
