//
// Pacman.cpp for Pac in /home/scutar_n/rendu/CPP/cpp_arcade/games/pacman/src
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Fri Apr  7 17:27:31 2017 Nathan Scutari
// Last update Mon Apr 10 01:07:46 2017 Nathan Scutari
//

#include "Pacman.hpp"

Pacman::Pacman()
{
}

Pacman::~Pacman() {}

void	Pacman::Init_map(std::vector<std::string> &map)
{
  map.push_back("11111111111111111111111111111");
  map.push_back("10000000000000100000000000001");
  map.push_back("10111110111110101111101111101");
  map.push_back("10001000011000000011000010001");
  map.push_back("10101011011011011011011010101");
  map.push_back("10100000000000000000000000101");
  map.push_back("10101111011111011111011110101");
  map.push_back("10000000010000000001000000001");
  map.push_back("10111111010111111101011111101");
  map.push_back("10000001000100000100010000001");
  map.push_back("11111101010001010001010111111");
  map.push_back("22222100010111111101000122222");
  map.push_back("22222101010122222101010122222");
  map.push_back("11111101010122222101010111111");
  map.push_back("00000000000122222100000000000");
  map.push_back("11111101010122222101010111111");
  map.push_back("22222101010111111101010122222");
  map.push_back("22222100010000200001000122222");
  map.push_back("11111101010111011101010111111");
  map.push_back("10000001000000000000010000001");
  map.push_back("10111111010111111101011111101");
  map.push_back("10000000010000000001000000001");
  map.push_back("10101111011111011111011110101");
  map.push_back("10100000000000000000000000101");
  map.push_back("10101011011011011011011010101");
  map.push_back("10001000011000000011000010001");
  map.push_back("10111110111110101111101111101");
  map.push_back("10000000000000100000000000001");
  map.push_back("11111111111111111111111111111");
}

void	Pacman::Get_map(t_map &game_map)
{
  std::vector<t_block>		block_line;
  t_block		data;
  std::vector<std::string>	map;
  std::vector<std::vector<t_block>>		map_line;

  srand(time(NULL));
  game_map.map.clear();
  game_map.width = 29;
  game_map.height = 29;
  Init_map(map);
  basic_map = map;
  basic_map[11][14] = '0';
  data.sprite = 0;
  data.angle = 0;
  data.shiftx = 0;
  data.shifty = 0;
  for (int y = 0 ; y < 29 ; ++y)
    {
      map_line.clear();
      for (int x = 0 ; x < 29 ; ++x)
	{
	  if (map[y][x] == '0' || map[y][x] == '2')
	    data.type = blockType::EMPTY;
	  else
	    data.type = blockType::BLOCK;
	  block_line.clear();
	  block_line.push_back(data);
	  map_line.push_back(block_line);
	}
      game_map.map.push_back(map_line);
    }
  data.type = blockType::PACGUM;
  data.sprite = 0;
  for (int y = 0 ; y < 29 ; ++y)
    {
      for (int x = 0 ; x < 29 ; ++x)
	{
	  if ((x == 3 && y == 3) || (x == 25 && y == 3) ||
	      (x == 3 && y == 25) || (x == 25 && y == 25))
	    {
	      data.type = blockType::POWERUP;
	      game_map.map[y][x].push_back(data);
	    }
	  else if (map[y][x] == '0')
	    {
	      data.type = blockType::PACGUM;
	      game_map.map[y][x].push_back(data);
	    }
	}
    }
  pac_pos.y = 17.0;
  pac_pos.x = 14.0;
  pacgum = 0;
  g_pos[0].x = 12;
  g_pos[0].y = 15;
  g_pos[1].x = 16;
  g_pos[1].y = 15;
  g_pos[3].x = 16;
  g_pos[3].y = 12;
  g_pos[2].x = 12;
  g_pos[2].y = 12;
  time_sec = time(NULL);
  ghost[0].alive = 1;
  ghost[1].alive = 1;
  ghost[2].alive = 1;
  ghost[3].alive = 1;
  ghost[0].speed = 0.125;
  ghost[1].speed = 0.125;
  ghost[2].speed = 0.125;
  ghost[3].speed = 0.125;
  begin = 0;
  alive = 1;
  killer_state = 0;
  death_sprite = 3;
  frame_counter = 0;
  current_direction = -1;
  next_direction = -1;
  facing = 0;
  score = 0;
}

void	Pacman::check_next_direction(t_gamedata &data)
{
  bool	*ptr;
  int	i;

  ptr = &data.up;
  i = -1;
  while (++i < 4)
    {
      if (*(ptr))
	next_direction = i;
      ++ptr;
    }
}

int	Pacman::is_cross_direction(t_gamedata &data)
{
  int	direction_counter;

  direction_counter = 0;
  if (data.map.map[pac_pos.y + 1][pac_pos.x][0].type == blockType::EMPTY)
    ++direction_counter;
  if (data.map.map[pac_pos.y - 1][pac_pos.x][0].type == blockType::EMPTY)
    ++direction_counter;
  if (data.map.map[pac_pos.y][pac_pos.x + 1][0].type == blockType::EMPTY)
    ++direction_counter;
  if (data.map.map[pac_pos.y][pac_pos.x - 1][0].type == blockType::EMPTY)
    ++direction_counter;
  if (direction_counter > 2)
    return (1);
  return (0);
}

int	Pacman::is_direction_valid(t_gamedata &data)
{
  int	dir[4][2] =
    {
      {-1, 0},
      {1, 0},
      {0, 1},
      {0, -1}
    };

  if (next_direction == -1)
    return (0);
  if (data.map.map[pac_pos.y + dir[next_direction][0]][pac_pos.x + dir[next_direction][1]][0].type == blockType::EMPTY)
    return (1);
  return (0);
}

void	Pacman::check_collision(t_gamedata &data)
{
  int	dir[4][2] =
    {
      {-1, 0},
      {1, 0},
      {0, 1},
      {0, -1}
    };

  if (current_direction == -1)
    return ;
  if (data.map.map[pac_pos.y + dir[current_direction][0]][pac_pos.x + dir[current_direction][1]][0].type == blockType::BLOCK)
    current_direction = -1;
}

void	Pacman::check_direction_change(t_gamedata &data)
{
  if (is_cross_direction(data))
    {
      if (is_direction_valid(data))
	{
	  current_direction = next_direction;
	  next_direction = -1;
	}
    }
  else
    check_basic_direction();
  check_collision(data);
}

void	Pacman::check_basic_direction()
{
  if (current_direction == -1)
    {
      current_direction = next_direction;
      next_direction = -1;
    }
  else
    check_backward_direction();
}

void	Pacman::go_towards_direction()
{
  double	dir[4][2] =
    {
      {-0.125, 0},
      {0.125, 0},
      {0, 0.125},
      {0, -0.125}
    };

  if (current_direction == -1)
    return ;
  pac_pos.y += dir[current_direction][0];
  pac_pos.x += dir[current_direction][1];
}

void	Pacman::check_backward_direction()
{
  int	back[4] = {1, 0, 3, 2};

  if (back[current_direction] == next_direction)
    {
      current_direction = next_direction;
      next_direction = -1;
    }
}

int	Pacman::get_angle()
{
  int	angle[4] = {90, 270, 0, 180};

  return (angle[current_direction]);
}

void	Pacman::update_map(t_gamedata &data)
{
  t_block	new_block;

  new_block.type = blockType::PLAYER;
  if (current_direction != -1)
    {
      new_block.angle = get_angle();
      facing = new_block.angle;
    }
  else
    new_block.angle = facing;
  if (current_direction == -1)
    new_block.sprite = 0;
  else
    new_block.sprite = (frame_counter % 15 < 7) ? 0 : 1;
  new_block.shiftx = pac_pos.x - static_cast<int>(pac_pos.x);
  new_block.shifty = pac_pos.y - static_cast<int>(pac_pos.y);
  data.map.map[pac_pos.y][pac_pos.x].push_back(new_block);
}

void	Pacman::remove_block(t_gamedata &data, int y, int x, blockType type)
{
  int	i;

  i = -1;
  while (++i < static_cast<int>(data.map.map[y][x].size()))
    {
      if (data.map.map[y][x][i].type == type)
	data.map.map[y][x].erase(data.map.map[y][x].begin() + i);
    }
}

void	Pacman::find_opposite_pos(t_pos &pos)
{
  double	distancex;
  double	distancey;
  t_pos		max;
  double	m_distance;
  double	distance;

  pos.x = 0;
  pos.y = 0;
  m_distance = 0;

  while (++pos.y < 28)
    {
      pos.x = 0;
      while (++pos.x < 28)
	{
	  distancex = pos.x - pac_pos.x;
	  distancey = pos.y - pac_pos.y;
	  distancex = (distancex < 0.0) ? -distancex : distancex;
	  distancey = (distancey < 0.0) ? -distancey : distancey;
	  distance = distancex + distancey;
	  if (distance > m_distance && basic_map[pos.y][pos.x] == '0')
	    {
	      max.x = pos.x;
	      max.y = pos.y;
	      m_distance = distance;
	    }
	}
    }
  pos.x = max.x;
  pos.y = max.y;
}

void	Pacman::eat_pacgum(t_gamedata &data)
{
  t_pos	pos;
  int	i;

  i = -1;
  while (++i < static_cast<int>(data.map.map[pac_pos.y][pac_pos.x].size()))
    {
      if (data.map.map[pac_pos.y][pac_pos.x][i].type == blockType::PACGUM)
	{
	  pacgum = 1;
	  remove_block(data, pac_pos.y, pac_pos.x, blockType::PACGUM);
	  score += 42;
	}
      else if (data.map.map[pac_pos.y][pac_pos.x][i].type == blockType::POWERUP)
	{
	  remove_block(data, pac_pos.y, pac_pos.x, blockType::POWERUP);
	  score += 5 * 42;
	  killer_state = 1;
	  find_opposite_pos(pos);
	  for (int y = 0 ; y < 4 ; ++y)
	    {
	      ghost[y].speed = 0.0625;
	      go_to(pos.y, pos.x, y);
	    }
	}
    }
}

int	Pacman::check_tp(t_gamedata &data)
{
  if (pac_pos.y >= 14 && pac_pos.y <= 14.1 &&
      pac_pos.x >= 27.9 && pac_pos.x <= 28.1)
    {
      pac_pos.x = 0;
      eat_pacgum(data);
      pac_pos.x = 0.125;
      return (0);
    }
  else if (pac_pos.y >= 14 && pac_pos.y <= 14.1 &&
	   pac_pos.x >= -0.1 && pac_pos.x <= 0.1)
    {
      pac_pos.x = 28;
      eat_pacgum(data);
      pac_pos.x = 27.875;
      return (0);
    }
  return (1);
}

void	Pacman::pacman_move(t_gamedata &data)
{
  check_next_direction(data);
  remove_block(data, pac_pos.y, pac_pos.x, blockType::PLAYER);
  data.map.map[pac_pos.y][pac_pos.x][0].type = blockType::EMPTY;
  ++frame_counter;
  if (pac_pos.x - static_cast<int>(pac_pos.x) < 0.1 &&
      pac_pos.y - static_cast<int>(pac_pos.y) < 0.1)
    {
      eat_pacgum(data);
      if (check_tp(data))
	check_direction_change(data);
    }
  else
    check_backward_direction();
  go_towards_direction();
  update_map(data);
}

void	Pacman::update_clyde(t_gamedata &data)
{
  t_block	new_block;

  new_block.type = blockType::EVIL_DUDE;
  new_block.sprite = 12;
  if (killer_state)
    new_block.sprite = 1;
  if (ghost[3].alive == 0)
    new_block.sprite = 2;
  new_block.angle = 0;
  new_block.shiftx = g_pos[3].x - static_cast<int>(g_pos[3].x);
  new_block.shifty = g_pos[3].y - static_cast<int>(g_pos[3].y);
  data.map.map[g_pos[3].y][g_pos[3].x].push_back(new_block);
}

void	Pacman::update_inky(t_gamedata &data)
{
  t_block	new_block;

  new_block.type = blockType::EVIL_DUDE;
  new_block.sprite = 8;
  if (killer_state)
    new_block.sprite = 1;
  if (ghost[2].alive == 0)
    new_block.sprite = 2;
  new_block.angle = 0;
  new_block.shiftx = g_pos[2].x - static_cast<int>(g_pos[2].x);
  new_block.shifty = g_pos[2].y - static_cast<int>(g_pos[2].y);
  data.map.map[g_pos[2].y][g_pos[2].x].push_back(new_block);
}

void	Pacman::update_blinky(t_gamedata &data)
{
  t_block	new_block;

  new_block.type = blockType::EVIL_DUDE;
  new_block.sprite = 0;
  if (killer_state)
    new_block.sprite = 1;
  if (ghost[0].alive == 0)
    new_block.sprite = 2;
  new_block.angle = 0;
  new_block.shiftx = g_pos[0].x - static_cast<int>(g_pos[0].x);
  new_block.shifty = g_pos[0].y - static_cast<int>(g_pos[0].y);
  data.map.map[g_pos[0].y][g_pos[0].x].push_back(new_block);
}

void	Pacman::update_pinky(t_gamedata &data)
{
  t_block	new_block;

  new_block.type = blockType::EVIL_DUDE;
  new_block.sprite = 4;
  if (killer_state)
    new_block.sprite = 1;
  if (ghost[1].alive == 0)
    new_block.sprite = 2;
  new_block.angle = 0;
  new_block.shiftx = g_pos[1].x - static_cast<int>(g_pos[1].x);
  new_block.shifty = g_pos[1].y - static_cast<int>(g_pos[1].y);
  data.map.map[g_pos[1].y][g_pos[1].x].push_back(new_block);
}

void	Pacman::pinky_move(t_gamedata &data)
{
  if (frame_counter >= 300)
    {
      if ((ghost_cross_direction(1) || start[1] == 0 || ghost[1].path.size() == 0)
	  && killer_state == 0 && ghost[1].alive)
	{
	  start[1] = 1;
	  move_front_pacman(1);
	}
      if (ghost[1].alive == 0 && ghost[1].path.size() == 0)
	{
	  tp_ghost(1);
	  ghost[1].speed = 0.125;
	  ghost[1].alive = 1;
	}
    }
  move_ghost(1);
  update_pinky(data);
}

int	Pacman::ghost_cross_direction(int g)
{
  int	dir[4][2] =
    {
      {-1, 0},
      {1, 0},
      {0, 1},
      {0, -1}
    };
  int	i;
  int	cross;

  cross = 0;
  if (g_pos[g].x - static_cast<int>(g_pos[g].x) < 0.1 &&
      g_pos[g].y - static_cast<int>(g_pos[g].y) < 0.1)
    {
      g_pos[g].x = static_cast<int>(g_pos[g].x);
      g_pos[g].y = static_cast<int>(g_pos[g].y);
      i = -1;
      while (++i < 4)
	{
	  if (basic_map[g_pos[g].y + dir[i][0]][g_pos[g].x + dir[i][1]] == '0')
	    ++cross;
	}
      return ((cross > 2) ? 1 : 0);
    }
  return (0);
}

void	Pacman::move_behind_pacman(int g)
{
  int	wall[4][2] =
    {
      {-1, 0},
      {1, 0},
      {0, 1},
      {0, -1}
    };

  if (current_direction != -1 && basic_map[pac_pos.y + wall[current_direction][0]][pac_pos.x + wall[current_direction][1]] == '0')
    basic_map[pac_pos.y + wall[current_direction][0]][pac_pos.x + wall[current_direction][1]] = '3';
  go_to(pac_pos.y, pac_pos.x, g);
}

void	Pacman::move_front_pacman(int g)
{
  int	wall[4][2] =
    {
      {1, 0},
      {-1, 0},
      {0, -1},
      {0, -1}
    };

  if (current_direction != -1 && basic_map[pac_pos.y + wall[current_direction][0]][pac_pos.x + wall[current_direction][1]] == '0')
    basic_map[pac_pos.y + wall[current_direction][0]][pac_pos.x + wall[current_direction][1]] = '3';
  go_to(pac_pos.y, pac_pos.x, g);
}

void	Pacman::blinky_move(t_gamedata &data)
{
  if (frame_counter >= 300)
    {
      if ((ghost_cross_direction(0) || start[0] == 0 || ghost[0].path.size() == 0)
	  && killer_state == 0 && ghost[0].alive)
	{
	  start[0] = 1;
	  move_behind_pacman(0);
	}
      if (ghost[0].alive == 0 && ghost[0].path.size() == 0)
	{
	  tp_ghost(0);
	  ghost[0].alive = 1;
	  ghost[0].speed = 0.125;
	}
    }
  move_ghost(0);
  update_blinky(data);
}

t_node	*Pacman::pick_shortest()
{
  t_node			*ret;
  std::list<t_node *>::iterator	shortest = open.begin();
  int	value = (*shortest)->value;

  for (std::list<t_node *>::iterator it = open.begin() ; it != open.end() ; ++it)
    {
      if ((*it)->value < value)
	{
	  shortest = it;
	  value = (*it)->value;
	}
    }
  ret = (*shortest);
  basic_map[ret->pos.y][ret->pos.x] = '3';
  closed.push_back(ret);
  open.erase(shortest);
  return (ret);
}

t_node	*Pacman::already_in_list(int x, int y)
{
  for (std::list<t_node *>::iterator it = open.begin() ; it != open.end() ; ++it)
    {
      if (static_cast<int>((*it)->pos.x) == x && static_cast<int>((*it)->pos.y) == y)
	return (*it);
    }
  return (0);
}

void	Pacman::compare_value(t_node *current, t_node *compare)
{
  int	new_value;

  new_value = compare->dist_to_end + (current->dist_to_start + 1);
  if (new_value < compare->value)
    {
      compare->previous = current;
      compare->value = new_value;
      compare->dist_to_start = current->dist_to_start + 1;
    }
}

void	Pacman::path_finder(int y, int x, int g)
{
  t_pos				pos;
  int				i;
  t_node			*compare;
  t_node			*current;
  int	n_pos[4][2] =
    {
      {-1, 0},
      {1, 0},
      {0, -1},
      {0, 1}
    };

  if (static_cast<int>(g_pos[g].x) == x && static_cast<int>(g_pos[g].y) == y)
    return ;
  loop_count = 0;
  while (open.size() && ++loop_count <= 1500)
    {
      i = -1;
      current = pick_shortest();
      while (++i < 4)
	if (current->pos.x + n_pos[i][1] >= 0 && current->pos.y + n_pos[i][0] >= 0 &&
	    current->pos.x + n_pos[i][1] < 29 && current->pos.y + n_pos[i][1] < 29 &&
	    (basic_map[current->pos.y + n_pos[i][0]][current->pos.x + n_pos[i][1]] == '0' ||
	     basic_map[current->pos.y + n_pos[i][0]][current->pos.x + n_pos[i][1]] == '2'))
	  {
	    pos.x = current->pos.x + n_pos[i][1];
	    pos.y = current->pos.y + n_pos[i][0];
	    if ((compare = already_in_list(pos.x, pos.y)))
	      compare_value(current, compare);
	    else
	      add_to_list(current, pos, y, x);
	    if (current->pos.x + n_pos[i][1] == x && current->pos.y + n_pos[i][0] == y)
	      {
		trace_back(g);
		return ;
	      }
	  }
    }
  for (int i = 0 ; i < 29 ; ++i)
    {
      for (int x = 0 ; x < 29 ; ++x)
	if (basic_map[i][x] == '3')
	  basic_map[i][x] = '0';
    }
  while (open.size())
    {
      delete open.back();
      open.pop_back();
    }
  while (closed.size())
    {
      delete closed.back();
      closed.pop_back();
    }
}

void	Pacman::trace_back(int g)
{
  t_pos		pos;
  t_node	*tmp;

  tmp = open.back();
  ghost[g].path.clear();
  while (tmp->previous)
    {
      pos.x = tmp->pos.x;
      pos.y = tmp->pos.y;
      ghost[g].path.push_back(pos);
      tmp = tmp->previous;
    }
  while (open.size())
    {
      delete open.back();
      open.pop_back();
    }
  while (closed.size())
    {
      delete closed.back();
      closed.pop_back();
    }
  for (int i = 0 ; i < 29 ; ++i)
    {
      for (int x = 0 ; x < 29 ; ++x)
	if (basic_map[i][x] == '3')
	  basic_map[i][x] = '0';
    }
}

int	get_dist(int y, int x, int y2, int x2)
{
  int	dist;

  dist = y - y2 + x - x2;
  return ((dist < 0) ? -dist : dist);
}

void	Pacman::add_to_list(t_node *current, t_pos pos, int y, int x)
{
  t_node	*new_node;

  new_node = new t_node;
  new_node->previous = current;
  new_node->pos.x = pos.x;
  new_node->pos.y = pos.y;
  new_node->dist_to_start = current->dist_to_start + 1;
  new_node->dist_to_end = get_dist(pos.y, y, pos.x, x);
  new_node->value = new_node->dist_to_start + new_node->dist_to_end;
  open.push_back(new_node);
}

void	Pacman::go_to(int y, int x, int g)
{
  t_node	*node = new t_node;

  open.clear();
  closed.clear();
  node->dist_to_start = 0;
  node->dist_to_end = get_dist(y, x, g_pos[g].y, g_pos[g].x);
  node->value = node->dist_to_start + node->dist_to_end;
  node->previous = NULL;
  g_pos[g].x = static_cast<int>(g_pos[g].x);
  g_pos[g].y = static_cast<int>(g_pos[g].y);
  node->pos.x = g_pos[g].x;
  node->pos.y = g_pos[g].y;
  open.push_back(node);
  path_finder(y, x, g);
}

void	Pacman::move_ghost(int g)
{
  if (ghost[g].path.size() == 0)
    return ;
  if (g_pos[g].x != ghost[g].path.back().x)
    {
      if (g_pos[g].x < ghost[g].path.back().x)
	g_pos[g].x += ghost[g].speed;
      else
	g_pos[g].x -= ghost[g].speed;
    }
  else if (g_pos[g].y != ghost[g].path.back().y)
    {
      if (g_pos[g].y < ghost[g].path.back().y)
	g_pos[g].y += ghost[g].speed;
      else
	g_pos[g].y -= ghost[g].speed;
    }
  if (g_pos[g].y == ghost[g].path.back().y &&
      g_pos[g].x == ghost[g].path.back().x)
    ghost[g].path.pop_back();
}

void	Pacman::move_to_random_pos(int g)
{
  t_pos	pos;
  bool	ok;

  ok = false;
  while (ok == false)
    {
      pos.x = rand() % 29;
      pos.y = rand() % 29;
      if (basic_map[pos.y][pos.x] == '0')
	ok = true;
    }
  go_to(pos.y, pos.x, g);
}

void	Pacman::clyde_move(t_gamedata &data)
{
  if (frame_counter >= 300)
    {
      if (ghost[3].path.size() == 0 && killer_state == 0 && ghost[3].alive)
	move_to_random_pos(3);
      if (ghost[3].alive == 0 && ghost[2].path.size() == 0)
	{
	  tp_ghost(3);
	  ghost[3].speed = 0.125;
	  ghost[3].alive = 1;
	}
    }
  move_ghost(3);
  update_clyde(data);
}

void	Pacman::inky_move(t_gamedata &data)
{
  if (frame_counter >= 300)
    {
      if (ghost[2].path.size() == 0 && killer_state == 0 && ghost[2].alive)
	move_to_random_pos(2);
      if (ghost[2].alive == 0 && ghost[2].path.size() == 0)
	{
	  tp_ghost(2);
	  ghost[2].speed = 0.125;
	  ghost[2].alive = 1;
	}
    }
  move_ghost(2);
  update_inky(data);
}

int	Pacman::kill_ghost(int g)
{
  if (ghost[g].alive)
    {
      score += 294;
      ghost[g].alive = 0;
      go_to(14, 14, g);
      ghost[g].speed = 0.250;
    }
  return (0);
}

int	Pacman::is_dead(t_gamedata &data)
{
  double	distancex;
  double	distancey;
  double	distance;
  int		i;

  i = -1;
  while (++i < 4)
    {
      distancex = g_pos[i].x - pac_pos.x;
      distancey = g_pos[i].y - pac_pos.y;
      distancex = (distancex < 0.0) ? -distancex : distancex;
      distancey = (distancey < 0.0) ? -distancey : distancey;
      distance = distancex + distancey;
      if (distance <= 0.4 && distance >= -0.4)
	{
	  if (killer_state == 0)
	    {
	      data.map.sName.push_back("5");
	      return (1);
	    }
	  else
	    {
	      data.map.sName.push_back("4");
	      return (kill_ghost(i));
	    }
	}
    }
  return (0);
}

int	Pacman::pac_death(t_gamedata &data)
{
  t_block	new_block;

  if (frame_counter % 10 == 0)
    {
      ++death_sprite;
      frame_counter = 0;
    }
  if (death_sprite == 8)
    return (1);
  remove_block(data, pac_pos.y, pac_pos.x, blockType::PLAYER);
  new_block.type = blockType::PLAYER;
  new_block.sprite = death_sprite;
  new_block.shiftx = pac_pos.x - static_cast<int>(pac_pos.x);
  new_block.shifty = pac_pos.y - static_cast<int>(pac_pos.y);
  new_block.angle = 0;
  data.map.map[pac_pos.y][pac_pos.x].push_back(new_block);
  return (0);
}

void	Pacman::tp_ghost(int y)
{
  g_pos[y].x = static_cast<int>(g_pos[y].x);
  g_pos[y].y = static_cast<int>(g_pos[y].y);
}

int	Pacman::Game_loop(t_gamedata &data)
{
  data.map.sName.clear();
  data.map.sNameLoop.clear();
  if (pacgum)
    {
      if (++pacgum == 20)
	pacgum = 0;
      data.map.sNameLoop.push_back("1");
    }
  if (++begin <= 150)
    {
      if (begin == 1)
	data.map.sName.push_back("0");
    }
  else if (alive)
    {
      if (killer_state == 0)
	data.map.sNameLoop.push_back("2");
      else
	data.map.sNameLoop.push_back("3");
      if (killer_state && ++killer_state == 300)
	{
	  for (int y = 0 ; y < 4 ; ++y)
	    if (ghost[y].alive)
	      {
		tp_ghost(y);
		ghost[y].speed = 0.125;
	      }
	  killer_state = 0;
	}
      remove_block(data, g_pos[0].y, g_pos[0].x, blockType::EVIL_DUDE);
      remove_block(data, g_pos[3].y, g_pos[3].x, blockType::EVIL_DUDE);
      remove_block(data, g_pos[1].y, g_pos[1].x, blockType::EVIL_DUDE);
      remove_block(data, g_pos[2].y, g_pos[2].x, blockType::EVIL_DUDE);
      pacman_move(data);
      clyde_move(data);
      inky_move(data);
      blinky_move(data);
      pinky_move(data);
      if (is_dead(data))
	{
	  alive = 0;
	  frame_counter = 0;
	}
    }
  else
    {
      ++frame_counter;
      if (pac_death(data))
	return (score);
    }
  data.map.gui.score = score;
  data.map.gui.sec = time(NULL) - time_sec;
  return (1);
}

extern "C" IGame	*factory()
{
  return (new Pacman);
}
