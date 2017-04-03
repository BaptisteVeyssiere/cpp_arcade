//
// Snake.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sat Apr  1 14:41:59 2017 Baptiste Veyssiere
// Last update Tue Apr  4 01:27:34 2017 Baptiste Veyssiere
//

#include "Snake.hpp"

Snake::Snake() {}

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
      mapline.push_back(block);
    }
  map.push_back(mapline);
}

void	Snake::Get_map(t_map &game_map) const
{
  std::vector<std::string>	coded_map;

  this->Get_file_content(coded_map);
  for (size_t i = 0; i < coded_map.size(); i++)
    {
      if (i > 0 && coded_map[i].size() != coded_map[i - 1].size())
	throw game_error("Error: map.txt is corrupted");
      this->Add_mapline(coded_map[i], game_map.map);
    }
  game_map.height = game_map.map.size();
  if (game_map.height < 3)
    throw game_error("Error: map height is too small");
  game_map.width = game_map.map[0].size();
  if (game_map.width < 3)
    throw game_error("Error: map width is too small");
}

void	Snake::Game_loop(t_map &game_map) const
{
  (void)game_map;
}

extern "C" IGame	*factory()
{
  return (new Snake);
}
