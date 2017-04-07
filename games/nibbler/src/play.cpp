//
// play.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/nibbler
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Apr  6 13:49:35 2017 Baptiste Veyssiere
// Last update Fri Apr  7 23:41:38 2017 ilyas semmaoui
//

# include <iostream>
# include <vector>
# include <functional>
# include "Protocol.hpp"

uint16_t	gen_randnbr()
{
  return (rand() % 18 + 1);
}

void	where_am_i(arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  map = map;
  direction = direction;
  snake->type = arcade::CommandType::WHERE_AM_I;
  std::cout.write(reinterpret_cast<char*>(snake), (sizeof(uint16_t)*2)*(snake->lenght+1));
}

void	get_map(arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  snake = snake;
  direction = direction;
  map->type = arcade::CommandType::GET_MAP;
  std::cout.write(reinterpret_cast<char*>(map),sizeof(uint16_t)*3 + sizeof(uint16_t)*((map->width * map->height)));
}

void	go_up(arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  snake = snake;
  map = map;
  direction = 0;
}

void	go_right(arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  snake = snake;
  map = map;
  direction = 1;
}

void	go_down(arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  snake = snake;
  map = map;
  direction = 2;
}

void	go_left(arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  snake = snake;
  map = map;
  direction = 3;
}

void	play(arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  int	i;

  if (direction >= 0 && direction < 4) {
    i = snake->lenght;
    while (--i > 0) {
      snake->position[i].x = snake->position[i-1].x;
      snake->position[i].y = snake->position[i-1].y;
    }
  }
  if (direction == 0)
    --(snake->position[0].y);
  else if (direction == 3)
    --(snake->position[0].x);
  else if (direction == 1)
    ++(snake->position[0].x);
  else if (direction == 2)
    ++(snake->position[0].y);
  if (map->tile[snake->position[0].y * 20 + snake->position[0].x] == arcade::TileType::POWERUP)
    {
      ++snake->lenght;
      map->tile[snake->position[0].y * 20 + snake->position[0].x] == arcade::TileType::EMPTY;
      map->tile[gen_randnbr() * 20 + gen_randnbr()] == arcade::TileType::POWERUP;
    }
  direction = direction;
}

void	shoot(arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  map = map;
  snake = snake;
  direction = direction;
}

void	go_forward(arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  map = map;
  snake = snake;
  direction = direction;
}

void	illegal(arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  map = map;
  snake = snake;
  direction = direction;
}

void	choose_function(char ch, arcade::GetMap *map, arcade::WhereAmI *snake, char &direction)
{
  std::vector<std::function<void(arcade::GetMap*, arcade::WhereAmI*, char&)>>	ptr =
    {
      where_am_i,
      get_map,
      go_up,
      go_down,
      go_left,
      go_right,
      go_forward,
      shoot,
      illegal,
      play
    };
  std::string	symlist = "0123456789";
  for (int i = 0; i < 10; i++)
    if (ch == symlist[i])
      ptr[i](map, snake, direction);
}

void	InitMap(arcade::GetMap *map)
{
  arcade::Position	powerup;

  powerup.x = gen_randnbr();
  powerup.y = gen_randnbr();
  map->type = arcade::CommandType::GET_MAP;
  map->width = 20;
  map->height = 20;
  for (size_t i = 0; i < 20; i++)
    {
      for (size_t j = 0; j < 20; j++)
	{
	  if (i == 0 || j == 0 || i == 19 || j == 19)
	    map->tile[i * 20 + j] = arcade::TileType::BLOCK;
	  else if (i == powerup.y && j == powerup.x)
	    map->tile[i * 20 + j] = arcade::TileType::POWERUP;
	  else
	    map->tile[i * 20 + j] = arcade::TileType::EMPTY;
	}
    }
}

void	InitPosition(arcade::WhereAmI *snake)
{
  snake->type = arcade::CommandType::WHERE_AM_I;
  snake->lenght = 4;
  snake->position[0].x = 20 / 2;
  snake->position[0].y = 20 / 2;
  snake->position[1].x = snake->position[0].x - 1;
  snake->position[1].y = snake->position[0].y;
  snake->position[2].x = snake->position[1].x - 1;
  snake->position[2].y = snake->position[1].y;
  snake->position[3].x = snake->position[2].x - 1;
  snake->position[3].y = snake->position[2].y;
}

extern "C" void	Play(void)
{
  arcade::GetMap	*map;
  arcade::WhereAmI	*snake;
  char		direction;
  int		ch;
  char		buff[2];

  map = new arcade::GetMap[sizeof(arcade::GetMap) + (20 * 20 * sizeof(arcade::TileType))];
  InitMap(map);
  snake = new arcade::WhereAmI[sizeof(arcade::WhereAmI) + sizeof(arcade::Position)];
  InitPosition(snake);
  while (std::cin.read(buff, 2) && std::cin.good() == true)
    {
      ch = *reinterpret_cast<int*>(buff);
      choose_function(ch + '0', map, snake, direction);
    }
  delete map;
  delete snake;
}
