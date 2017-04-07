//
// Nibbler.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/nibbler
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:41:59 2017 Baptiste Veyssiere
// Last update Sat Apr  8 00:33:48 2017 Baptiste Veyssiere
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

void	Nibbler::Add_mapline(const std::string &line, std::vector<std::vector<t_block>> &map) const
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
      block.shiftx = 0.0;
      block.shifty = 0.0;
      mapline.push_back(block);
    }
  map.push_back(mapline);
}

void	Nibbler::Add_cell(t_map &map, unsigned int y, unsigned int x, float shiftx, float shifty)
{
  t_cell	cell;

  cell.x = x;
  cell.y = y;
  this->head.push_back(cell);
  map.map[y][x].type = blockType::SNAKTAIL;
  map.map[y][x].sprite = 0;
  map.map[y][x].shiftx = shiftx;
  map.map[y][x].shifty = shifty;
}

void	Nibbler::Add_player(t_map &game_map)
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
      if ((i == 0 || j == 0) && game_map.map[i][j].type != blockType::BLOCK)
	throw game_error("The map must be surrounded by blocks");
  this->last_key = -1;
}

int	Nibbler::check_ahead(t_map &game_map)
{
  blockType	next_block;

  next_block = game_map.map[this->head.begin()->y + this->player_ydirection][this->head.begin()->x + this->player_xdirection].type;
  if (next_block == blockType::BLOCK ||
      next_block == blockType::SNAKTAIL ||
      next_block == blockType::OBSTACLE)
    return (1);
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
  if (this->counter > (FPS / 120))
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


void	Nibbler::Remove_last_cell(t_map &map)
{
  map.map[(this->head.back()).y][(this->head.back()).x].type = blockType::EMPTY;
  map.map[(this->head.back()).y][(this->head.back()).x].shiftx = 0.0;
  map.map[(this->head.back()).y][(this->head.back()).x].shifty = 0.0;
  this->head.pop_back();
}

int	Nibbler::move(t_map &map)
{
  t_cell	cell;
  unsigned int	angle;
  int		ret;

  ret = 0;
  angle = 0;
  if (this->player_xdirection == 1)
    angle = 270;
  else if (this->player_xdirection == -1)
    angle = 90;
  else if (this->player_ydirection == 1)
    angle = 180;
  cell.x = this->head.begin()->x;
  cell.y = this->head.begin()->y;
  if ((angle == 270 && map.map[cell.y][cell.x].shiftx >= 0.9) ||
      (angle == 90 && map.map[cell.y][cell.x].shiftx <= -0.9) ||
      (angle == 180 && map.map[cell.y][cell.x].shifty >= 0.9) ||
      (angle == 0 && map.map[cell.y][cell.x].shifty <= -0.9))
    {
      this->head.begin()->x += this->player_xdirection;
      this->head.begin()->y += this->player_ydirection;
      map.map[cell.y][cell.x].type = blockType::SNAKTAIL;
      map.map[cell.y][cell.x].angle = 0;
      this->head.insert(++this->head.begin(), cell);
      map.map[this->head.begin()->y][this->head.begin()->x].type = blockType::PLAYER;
      ret = 1;
    }
  for (std::list<t_cell>::iterator it = this->head.begin();
       it != this->head.end(); it++)
    {
      if (it == this->head.begin())
	{
	  map.map[it->y][it->x].shiftx += static_cast<float>(this->player_xdirection) / 10.0;
	  map.map[it->y][it->x].shifty += static_cast<float>(this->player_ydirection) / 10.0;
	}
      else
	{
	  map.map[it->y][it->x].shiftx += static_cast<float>((--it)->x - it->x) / 10.0;
	  ++it;
	  map.map[it->y][it->x].shifty += static_cast<float>((--it)->y - it->y) / 10.0;
	  ++it;
	}
      if (map.map[it->y][it->x].shiftx >= 1 || map.map[it->y][it->x].shiftx <= -1)
  	map.map[it->y][it->x].shiftx = 0.0;
      if (map.map[it->y][it->x].shifty >= 1 || map.map[it->y][it->x].shifty <= -1)
  	map.map[it->y][it->x].shifty = 0.0;
    }
  map.map[this->head.begin()->y][this->head.begin()->x].angle =
    angle;
  return (ret);
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
      if (map.map[y][x].type == blockType::EMPTY)
	{
	  map.map[y][x].type = blockType::POWERUP;
	  done = true;
	}
    }
}

void	Nibbler::move_nibbler(t_map &map)
{
  bool	powerup;
  int	ret;
  int	x;
  int	y;

  powerup = false;
  x = this->head.begin()->x + this->player_xdirection;
  y = this->head.begin()->y + this->player_ydirection;
  if (map.map[y][x].type == blockType::POWERUP//  &&
      // ((this->head.begin()->x == x &&
      // 	this->head.begin()->y - map.map[this->head.begin()->y][this->head.begin()->x].shifty - y >= -0.5 &&
      // 	this->head.begin()->y - map.map[this->head.begin()->y][this->head.begin()->x].shifty - y <= 0.5) ||
      //  (this->head.begin()->y == y &&
      // 	this->head.begin()->x - map.map[this->head.begin()->y][this->head.begin()->x].shiftx - x >= -0.5 &&
      // 	this->head.begin()->x - map.map[this->head.begin()->y][this->head.begin()->x].shiftx - x <= 0.5))
      )
    powerup = true;
  if ((ret = this->move(map)) && !powerup)
    this->Remove_last_cell(map);
  else if (ret && powerup)
    {
      this->Add_powerup(map);
      this->score += POWERUP_SCORE;
    }
}

int	Nibbler::Game_loop(t_gamedata &data)
{
  ++this->counter;
  this->change_direction(data);
  if (this->counter > (FPS / 120))
    {
      if (this->check_ahead(data.map))
	return (this->score);
      this->move_nibbler(data.map);
      this->counter = 0;
    }
  return (1);
}

extern "C" IGame	*factory()
{
  return (new Nibbler);
}
