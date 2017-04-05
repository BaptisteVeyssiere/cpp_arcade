//
// Core_program.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Fri Mar 31 14:21:00 2017 Baptiste Veyssiere
// Last update Wed Apr  5 13:17:42 2017 Baptiste Veyssiere
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
	this->game_list.push_back(std::string(file->d_name));
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
  std::cout << "Please enter a username:" << std::endl;
  getline(std::cin, this->username);
  std::cout << "Hi " << this->username << std::endl;
}

void	Core_program::Display_menu()
{
  this->Aff_Games();
  this->Aff_Graph();
  //this->Aff_Scores();
  this->Get_Username();
  while (this->Get_selected_game());
}
