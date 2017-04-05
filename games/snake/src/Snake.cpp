//
// Snake.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:41:59 2017 Baptiste Veyssiere
// Last update Wed Apr  5 10:36:13 2017 Baptiste Veyssiere
//

#include "Snake.hpp"

Snake::Snake() : counter(0) {}

Snake::~Snake() {}

void	Snake::Get_file_content(std::vector<std::string> &coded_map) const
{
  std::ifstream	file("games/snake/map/map.txt");
  std::string	str;

  if (file.is_open())
    while (getline(file, str))
      coded_map.push_back(str);
  else
    throw game_error("map.txt was not found (must be in games/snake/map/)");
}

void	Snake::Add_mapline(const std::string &line, std::vector<std::vector<t_block>> &map) const
{
  std::vector<t_block>	mapline;
  t_block		block;

  for (size_t i = 0; i < line.size(); i++)
    {
      if (line[i] - '0' >= BLOCK_NBR)
	throw game_error(std::string("Error in map.txt: symbol '") +
			 static_cast<char>(line[i]) +
			 std::string("' is unknown"));
      block.type = static_cast<blockType>(line[i] - '0');
      block.sprite = 0;
      block.angle = 0;
      mapline.push_back(block);
    }
  map.push_back(mapline);
}

void	Snake::Add_cell(t_map &map, unsigned int y, unsigned int x)
{
  t_cell	cell;

  cell.x = x;
  cell.y = y;
  this->head.push_back(cell);
  map.map[y][x].type = blockType::SNAKTAIL;
  map.map[y][x].sprite = 0;
}

void	Snake::Add_player(t_map &game_map)
{
  t_cell	head;

  head.x = game_map.width / 2 + 1;
  head.y = game_map.height / 2;
  this->head.push_back(head);
  this->player_xdirection = 1;
  this->player_ydirection = 0;
  game_map.map[head.y][head.x].type = blockType::PLAYER;
  game_map.map[head.y][head.x].angle = 270;
  game_map.map[head.y][head.x].sprite = 0;
  this->Add_cell(game_map, head.y, head.x - 1);
  this->Add_cell(game_map, head.y, head.x - 2);
  this->Add_cell(game_map, head.y, head.x - 3);
}

void	Snake::Get_map(t_map &game_map)
{
  std::vector<std::string>	coded_map;

  srand(time(NULL));
  this->Get_file_content(coded_map);
  for (size_t i = 0; i < coded_map.size(); i++)
    {
      if (i > 0 && coded_map[i].size() != coded_map[i - 1].size())
	throw game_error("Error: map.txt is corrupted");
      this->Add_mapline(coded_map[i], game_map.map);
    }
  game_map.height = game_map.map.size();
  if (game_map.height < 10)
    throw game_error("Error: map height is too small");
  game_map.width = game_map.map[0].size();
  if (game_map.width < 10)
    throw game_error("Error: map width is too small");
  this->Add_player(game_map);
  this->Add_powerup(game_map);
}

int	Snake::check_ahead(t_map &game_map)
{
  blockType	next_block;

  next_block = game_map.map[this->head.begin()->y + this->player_ydirection][this->head.begin()->x + this->player_xdirection].type;
  if (next_block == blockType::BLOCK ||
      next_block == blockType::SNAKTAIL ||
      next_block == blockType::OBSTACLE)
    return (1);
  return (0);
}

void	Snake::change_direction(t_gamedata &data)
{
  if (data.up || data.down || data.right || data.left)
    {
      this->player_ydirection = 0;
      this->player_xdirection = 0;
    }
  if (data.up)
    this->player_ydirection = -1;
  else if (data.right)
    this->player_xdirection = 1;
  else if (data.down)
    this->player_ydirection = 1;
  else if (data.left)
    this->player_xdirection = -1;
}


void	Snake::Remove_last_cell(t_map &map)
{
  map.map[(this->head.back()).y][(this->head.back()).x].type = blockType::EMPTY;
  this->head.pop_back();
}

void	Snake::move(t_map &map)
{
  t_cell	cell;
  unsigned int	angle;

  angle = 0;
  if (this->player_xdirection == 1)
    angle = 270;
  else if (this->player_xdirection = -1)
    angle = 90;
  else if (this->player_ydirection = 1)
    angle = 180;
  cell.x = this->head.begin()->x;
  cell.y = this->head.begin()->y;
  this->head.begin()->x += this->player_xdirection;
  this->head.begin()->y += this->player_ydirection;
  map.map[cell.y][cell.x].type = blockType::SNAKTAIL;
  map.map[cell.y][cell.x].angle = 0;
  map.map[this->head.begin()->y][this->head.begin()->x].type = blockType::PLAYER;
  map.map[this->head.begin()->y][this->head.begin()->x].angle =
    angle;
  this->head.insert(++this->head.begin(), cell);
}

void	Snake::Add_powerup(t_map &map) const
{
  unsigned int	x;
  unsigned int	y;
  bool		done;

  done = false;
  while (!done)
    {
      x = rand() % (map.width - 2) + 1;
      y = rand() % (map.height - 2) + 1;
      if (map.map[y][x].type == blockType::EMPTY)
	{
	  map.map[y][x].type = blockType::POWERUP;
	  done = true;
	}
    }
}

void	Snake::move_snake(t_map &map)
{
  bool	powerup;

  powerup = false;
  if (map.map[this->head.begin()->y + this->player_ydirection][this->head.begin()->x + this->player_xdirection].type == blockType::POWERUP)
    powerup = true;
  this->move(map);
  if (!powerup)
    this->Remove_last_cell(map);
  else
    this->Add_powerup(map);
}

int	Snake::Game_loop(t_gamedata &data)
{
  ++this->counter;
  this->change_direction(data);
  if (this->counter > (FPS / 2))
    {
      if (this->check_ahead(data.map))
	return (1);
      this->move_snake(data.map);
      this->counter = 0;
    }
  return (0);
}

extern "C" IGame	*factory()
{
  return (new Snake);
}
