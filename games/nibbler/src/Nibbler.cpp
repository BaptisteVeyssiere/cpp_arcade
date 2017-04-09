//
// Nibbler.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/nibbler
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:41:59 2017 Baptiste Veyssiere
// Last update Sun Apr  9 23:25:05 2017 Baptiste Veyssiere
//

#include <iostream>
#include "Nibbler.hpp"

Nibbler::Nibbler() : counter(0) {}

Nibbler::~Nibbler() {}

void	Nibbler::Get_file_content(std::vector<std::string> &coded_map) const
{
  std::ifstream	file("games/nibbler/map/map.txt");
  std::string	str;

  if (file.is_open())
    while (getline(file, str))
      coded_map.push_back(str);
  else
    throw game_error("map.txt was not found (must be in games/nibbler/map/)");
}

void	Nibbler::Add_block(t_block &block, std::vector<std::vector<t_block>> &mapline) const
{
  std::vector<t_block>	block_list;

  block_list.push_back(block);
  mapline.push_back(block_list);
}

void	Nibbler::Add_mapline(const std::string &line, std::vector<std::vector<std::vector<t_block>>> &map) const
{
  std::vector<std::vector<t_block>>	mapline;
  t_block				block;
  std::vector<t_block>			block_list;

  for (size_t i = 0; i < line.size(); i++)
    {
      if (line[i] - '0' >= BLOCK_NBR)
	throw game_error(std::string("Error in map.txt: symbol '") +
			 static_cast<char>(line[i]) +
			 std::string("' is unknown"));
      block.type = static_cast<blockType>(line[i] - '0');
      block.sprite = 0;
      block.angle = 0;
      block.shiftx = 0.0;
      block.shifty = 0.0;
      this->Add_block(block, mapline);
    }
  map.push_back(mapline);
}

void	Nibbler::Add_cell(t_map &map, unsigned int y, unsigned int x, float shiftx, float shifty)
{
  t_cell	cell;
  t_block	block;

  cell.x = x;
  cell.y = y;
  this->head.push_back(cell);
  block.angle = 0;
  block.type = blockType::SNAKTAIL;
  block.sprite = 0;
  block.shiftx = shiftx;
  block.shifty = shifty;
  map.map[y][x].push_back(block);
}

void	Nibbler::Add_player(t_map &game_map)
{
  t_cell	head;
  t_block	block;

  head.x = (game_map.width / 2 + 1);
  head.y = (game_map.height / 2);
  this->head.push_back(head);
  this->player_xdirection = 1;
  this->player_ydirection = 0;
  block.type = blockType::PLAYER;
  block.angle = 270;
  block.sprite = 0;
  block.shiftx = 0;
  block.shifty = 0;
  if (game_map.map[head.y][head.x][0].type == blockType::BLOCK ||
      game_map.map[head.y][head.x][0].type == blockType::SNAKTAIL ||
      game_map.map[head.y][head.x][0].type == blockType::PLAYER ||
      game_map.map[head.y][head.x][0].type == blockType::OBSTACLE ||
      game_map.map[head.y][head.x - 1][0].type == blockType::BLOCK ||
      game_map.map[head.y][head.x - 1][0].type == blockType::SNAKTAIL ||
      game_map.map[head.y][head.x - 1][0].type == blockType::PLAYER ||
      game_map.map[head.y][head.x - 1][0].type == blockType::OBSTACLE ||
      game_map.map[head.y][head.x - 2][0].type == blockType::BLOCK ||
      game_map.map[head.y][head.x - 2][0].type == blockType::SNAKTAIL ||
      game_map.map[head.y][head.x - 2][0].type == blockType::PLAYER ||
      game_map.map[head.y][head.x - 2][0].type == blockType::OBSTACLE ||
      game_map.map[head.y][head.x - 3][0].type == blockType::BLOCK ||
      game_map.map[head.y][head.x - 3][0].type == blockType::SNAKTAIL ||
      game_map.map[head.y][head.x - 3][0].type == blockType::PLAYER ||
      game_map.map[head.y][head.x - 3][0].type == blockType::OBSTACLE)
    throw game_error("Unauthorized block at the snake start position");
  game_map.map[head.y][head.x].push_back(block);
  this->Add_cell(game_map, head.y, head.x - 1, 0.0, 0.0);
  this->Add_cell(game_map, head.y, head.x - 2, 0.0, 0.0);
  this->Add_cell(game_map, head.y, head.x - 3, 0.0, 0.0);
}

void	Nibbler::Get_map(t_map &game_map)
{
  std::vector<std::string>	coded_map;

  srand(time(NULL));
  game_map.map.clear();
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
  if (game_map.width != game_map.height)
    throw game_error("The map must be squared");
  this->score = 0;
  this->Add_player(game_map);
  this->Add_powerup(game_map);
  for (size_t i = 0; i < game_map.map.size(); i++)
    for (size_t j = 0; j < game_map.map[0].size(); j++)
      if ((i == 0 || j == 0 || i == (game_map.map.size() - 1) || j == (game_map.map[0].size() - 1)) && game_map.map[i][j][0].type != blockType::BLOCK)
	throw game_error("The map must be surrounded by blocks");
  this->last_key = -1;
  this->start_time = time(NULL);
  this->end = 0;
}

int	Nibbler::check_ahead(t_map &game_map)
{
  blockType	next_block;

  for (int i = 0; i < 2; i++)
    {
      if (i == 1 && game_map.map[this->head.begin()->y + this->player_ydirection][this->head.begin()->x + this->player_xdirection].size() < 2)
	return (0);
      next_block = game_map.map[this->head.begin()->y + this->player_ydirection][this->head.begin()->x + this->player_xdirection][i].type;
      if (next_block == blockType::BLOCK ||
	  next_block == blockType::SNAKTAIL ||
	  next_block == blockType::OBSTACLE)
	return (1);
    }
  return (0);
}

void	Nibbler::change_direction(t_gamedata &data)
{
  if (data.up)
    this->last_key = 0;
  else if (data.right)
    this->last_key = 1;
  else if (data.down)
    this->last_key = 2;
  else if (data.left)
    this->last_key = 3;
  if (this->counter > (FPS / 12))
    {
      if (this->last_key == 0 || this->last_key == 2)
	this->player_xdirection = 0;
      else if (this->last_key == 1 || this->last_key == 3)
	this->player_ydirection = 0;
      if (this->last_key == 0 && this->player_ydirection != 1)
	this->player_ydirection = -1;
      else if (this->last_key == 1 && this->player_xdirection != -1)
	this->player_xdirection = 1;
      else if (this->last_key == 2 && this->player_ydirection != -1)
	this->player_ydirection = 1;
      else if (this->last_key == 3 && this->player_xdirection != 1)
	this->player_xdirection = -1;
      this->last_key = -1;
    }
}

void	Nibbler::move(t_map &map)
{
  unsigned int	angle;
  t_block	block;
  t_cell	cell;

  angle = 0;
  if (this->player_xdirection == 1)
    angle = 270;
  else if (this->player_xdirection == -1)
    angle = 90;
  else if (this->player_ydirection == 1)
    angle = 180;
  map.map[this->head.begin()->y][this->head.begin()->x][1].type = blockType::SNAKTAIL;
  map.map[this->head.begin()->y][this->head.begin()->x][1].angle = 0;
  cell.x = this->head.begin()->x;
  cell.y = this->head.begin()->y;
  this->head.insert(++this->head.begin(), cell);
  this->head.begin()->x += (this->player_xdirection);
  this->head.begin()->y += (this->player_ydirection);
  if (map.map[this->head.begin()->y][this->head.begin()->x].size() < 2)
    {
      block.shiftx = 0;
      block.shifty = 0;
      block.sprite = 0;
      map.map[this->head.begin()->y][this->head.begin()->x].push_back(block);
    }
  map.map[this->head.begin()->y][this->head.begin()->x][1].type = blockType::PLAYER;
  map.map[this->head.begin()->y][this->head.begin()->x][1].angle = angle;
}

void	Nibbler::Add_powerup(t_map &map) const
{
  unsigned int	x;
  unsigned int	y;
  bool		done;

  done = false;
  while (!done)
    {
      x = rand() % (map.width - 2) + 1;
      y = rand() % (map.height - 2) + 1;
      if (map.map[y][x][0].type == blockType::EMPTY &&
	  map.map[y][x].size() == 1)
	{
	  map.map[y][x][0].type = blockType::POWERUP;
	  done = true;
	}
    }
}

void	Nibbler::move_nibbler(t_map &map)
{
  bool	powerup;
  int	x;
  int	y;

  powerup = false;
  x = this->head.begin()->x + this->player_xdirection;
  y = this->head.begin()->y + this->player_ydirection;
  if (map.map[y][x][0].type == blockType::POWERUP)
    {
      powerup = true;
      map.sName.push_back("eat");
      map.map[y][x][0].type = blockType::EMPTY;
    }
  this->move(map);
  if (powerup)
    {
      this->Add_powerup(map);
      this->score += POWERUP_SCORE;
    }
  else if (!powerup)
    {
      map.map[std::prev(this->head.end())->y][std::prev(this->head.end())->x][1].type = blockType::EMPTY;
      this->head.pop_back();
    }
}

int	Nibbler::Game_loop(t_gamedata &data)
{
  data.map.sName.clear();
  if (this->end > 0)
    {
      ++this->end;
      if (this->end >= 20)
	return (this->score);
      return (1);
    }
  ++this->counter;
  this->change_direction(data);
  if (this->counter > (FPS / 12))
    {
      if (this->check_ahead(data.map))
	{
	  this->end = 1;
	  data.map.sName.push_back("wall");
	  return (1);
	}
      this->move_nibbler(data.map);
      this->counter = 0;
    }
  data.map.gui.score = this->score;
  data.map.gui.sec = time(NULL) - this->start_time;
  return (1);
}

extern "C" IGame	*factory()
{
  return (new Nibbler);
}
