//
// Core_program.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Fri Mar 31 14:21:00 2017 Baptiste Veyssiere
// Last update Sun Apr  9 05:52:46 2017 Baptiste Veyssiere
//

#include "Core_program.hpp"

Core_program::Core_program(const std::string &graphic_libname)
{
  this->game_handle = NULL;
  this->graphic_handle = NULL;
  this->graphic_handle = dlopen(graphic_libname.c_str(), RTLD_NOW);
  if (!this->graphic_handle)
    throw core_program_exception(dlerror());
  this->Set_Games();
  this->Set_Graph();
  this->game_selector = 0;
  this->graph_selector = 0;
}

Core_program::~Core_program()
{
  if (this->graphic_handle)
    dlclose(this->graphic_handle);
  if (this->game_handle)
    dlclose(this->game_handle);
}

void	Core_program::load_graphic_lib(const std::string &graphic_libname)
{
  std::cout << graphic_libname << std::endl;
  if (this->graphic_handle && dlclose(this->graphic_handle))
    throw core_program_exception(dlerror());
  this->graphic_handle = dlopen(graphic_libname.c_str(), RTLD_NOW);
  if (!this->graphic_handle)
    throw core_program_exception(dlerror());
}

void	Core_program::load_game_lib(const std::string &game_libname)
{
  if (this->game_handle && dlclose(this->game_handle))
    throw core_program_exception(dlerror());
  this->game_handle = dlopen(game_libname.c_str(), RTLD_NOW);
  if (!this->game_handle)
    throw core_program_exception(dlerror());
}

void	*Core_program::get_graphic_function(const std::string &fname) const
{
  void	*ptr;

  ptr = dlsym(this->graphic_handle, fname.c_str());
  if (!ptr)
    throw core_program_exception(dlerror());
  return (ptr);
}

void	*Core_program::get_game_function(const std::string &fname) const
{
  void	*ptr;

  ptr = dlsym(this->game_handle, fname.c_str());
  if (!ptr)
    throw core_program_exception(dlerror());
  return (ptr);
}

void		Core_program::Set_Scores(const std::string &game_name)
{
  std::vector<t_score>	tab;
  int			fd;
  std::ifstream		file("games/"+game_name+"/highscore");
  std::string		str;
  t_score		result;
  std::stringstream	stream;
  std::string		word;
  int			i;

  i = -1;
  while (getline(file, str) && ++i < 10)
    {
      stream << str;
      stream >> word;
      result.username = word;
      stream >> word;
      result.score = std::stoi(word);
      tab.push_back(result);
      stream.str(std::string());
      stream.clear();
    }
  while (++i < 10)
    {
      result.username = "USERNAME";
      result.score = 0;
      tab.push_back(result);
    }
  this->score_list.push_back(tab);
}

void		Core_program::Add_Score(unsigned int score)
{
  t_score	score_struct;

  score_struct.score = score;
  score_struct.username = this->username;
  for (unsigned int i = 0; i < this->score_list[this->game_selector].size(); i++)
    if (this->score_list[this->game_selector][i].score < score)
      {
	this->score_list[this->game_selector].insert(this->score_list[this->game_selector].begin() + i, score_struct);
	if (this->score_list[this->game_selector].size() > 10)
	  this->score_list[this->game_selector].pop_back();
	break;
      }
}

void	Core_program::Save_score() const
{
  std::ofstream	file;
  std::string	username;
  unsigned int	score;

  for (unsigned int id = 0; id < this->game_list.size(); id++)
    {
      file.open("games/"+this->game_list[id]+"/highscore", std::ios::trunc);
      std::cout << "games/"+this->game_list[id]+"/highscore" << std::endl;
      if (file.is_open())
	for (unsigned int i = 0; i < this->score_list[id].size(); i++)
	  {
	    username = this->score_list[id][i].username;
	    score = this->score_list[id][i].score;
	    std::cout << username << " " << score << std::endl;
	    file << username << " " << score << std::endl;
	  }
      else
	throw core_program_exception("Impossible to open or create highscore file");
      file.close();
    }
}

void		Core_program::Set_Games()
{
  DIR		*dir;
  struct dirent	*file;

  if ((dir = opendir("./games")) == NULL)
    throw core_program_exception("Error while using opendir()");
  file = readdir(dir);
  while (file)
    {
      if (file->d_type == DT_DIR && file->d_name[0] != '.')
	{
	  this->game_list.push_back(std::string(file->d_name));
	  this->Set_Scores(file->d_name);
	}
      file = readdir(dir);
    }
  if (closedir(dir) == -1)
    throw core_program_exception("Error while using closedir()");
}

void		Core_program::Set_Graph()
{
  DIR		*dir;
  struct dirent	*file;

  if ((dir = opendir("./lib")) == NULL)
    throw core_program_exception("Error while using opendir()");
  file = readdir(dir);
  while (file)
    {
      if (file->d_type == DT_DIR && file->d_name[0] != '.')
	this->graph_list.push_back(std::string(file->d_name));
      file = readdir(dir);
    }
  if (closedir(dir) == -1)
    throw core_program_exception("Error while using closedir()");
}

void	Core_program::Aff_Games() const
{
  unsigned int	max_length;

  max_length = 16;
  for (unsigned int i = 0; i < this->game_list.size(); i++)
    if (this->game_list[i].size() > max_length)
      max_length = this->game_list[i].size();
  std::cout << std::string(max_length + 4, '*') << std::endl << "*" << std::string(max_length + 2, ' ') << "*" << std::endl;
  std::cout << "* " << "Games available:" << std::string(max_length - 16, ' ') << " *" << std::endl;
  for (unsigned int i = 0; i < this->game_list.size(); i++)
    std::cout << "* " << this->game_list[i] << std::string(max_length - this->game_list[i].size(), ' ') << " *" << std::endl;
  std::cout << "*" << std::string(max_length + 2, ' ') << "*" << std::endl << std::string(max_length + 4, '*') << std::endl;
}

void	Core_program::Aff_Graph() const
{
  unsigned int	max_length;

  max_length = 20;
  for (unsigned int i = 0; i < this->graph_list.size(); i++)
    if (this->graph_list[i].size() > max_length)
      max_length = this->graph_list[i].size();
  std::cout << std::string(max_length + 4, '*') << std::endl << "*" << std::string(max_length + 2, ' ') << "*" << std::endl;
  std::cout << "* " << "Libraries available:" << std::string(max_length - 20, ' ') << " *" << std::endl;
  for (unsigned int i = 0; i < this->graph_list.size(); i++)
    std::cout << "* " << this->graph_list[i] << std::string(max_length - this->graph_list[i].size(), ' ') << " *" << std::endl;
  std::cout << "*" << std::string(max_length + 2, ' ') << "*" << std::endl << std::string(max_length + 4, '*') << std::endl;
}

void	Core_program::Aff_Scores() const
{
  unsigned int	max_length;
  unsigned int	length;

  for (unsigned int i = 0; i < this->score_list.size(); i++)
    {
      max_length = 15 < this->game_list[i].size() ? this->game_list[i].size() : 15;
      for (unsigned int j = 0; j < this->score_list[i].size(); j++)
	{
	  length = std::to_string(this->score_list[i][j].score).length() + 5 + this->score_list[i][j].username.size();
	  max_length = length > max_length ? length : max_length;
	}
      std::cout << std::string(max_length + 4, '*') << std::endl << "*" <<
	std::string(max_length + 2, ' ') << "*" << std::endl;
      std::cout << "* " << this->game_list[i] << ":" << std::string(max_length - this->game_list[i].size() - 1, ' ') << " *" << std::endl;
      std::cout << "* " << "Highscores:" << std::string(max_length - 11, ' ') << " *" << std::endl;
      for (unsigned int j = 0; j < this->score_list[i].size(); j++)
	{
	  length = this->score_list[i][j].username.size() + std::to_string(this->score_list[i][j].score).length() + std::to_string((j + 1)).length() + 3;
	  std::cout << "* " << j + 1 << ". " << this->score_list[i][j].username << " " << this->score_list[i][j].score << std::string(max_length - length, ' ') << " *" << std::endl;
	}
  std::cout << "*" << std::string(max_length + 2, ' ') << "*" << std::endl << std::string(max_length + 4, '*') << std::endl;
    }
}

int	Core_program::Get_selected_game()
{
  std::cout << "Please choose your game in the list above:" << std::endl;
  getline(std::cin, this->game);
  if (find(this->game_list.begin(), this->game_list.end(), this->game) == this->game_list.end())
    {
      std::cout << "This game doesn't exist at this time" << std::endl;
      return (1);
    }
  return (0);
}

void	Core_program::Get_Username()
{
  this->username = "";
  while (this->username.size() < 1)
    {
      std::cout << "Please enter a username:" << std::endl;
      getline(std::cin, this->username);
      if (this->username.size() > 0)
	std::cout << "Hi " << this->username << std::endl;
      else
	{
	  std::cout << "So you don't have name ? Poor child..." << std::endl;
	  std::cout << "Ok, so I let you choose a nickname :)" << std::endl;
	}
    }
}

void	Core_program::Display_menu()
{
  this->Aff_Games();
  this->Aff_Graph();
  this->Aff_Scores();
  this->Get_Username();
  while (this->Get_selected_game());
}
