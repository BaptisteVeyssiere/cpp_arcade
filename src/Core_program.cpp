//
// Core_program.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Fri Mar 31 14:21:00 2017 Baptiste Veyssiere
// Last update Fri Mar 31 14:42:30 2017 Baptiste Veyssiere
//

#include "Core_program.hpp"

Core_program::Core_program(const std::string &graphic_libname)
{
  this->graphic_handle = dlopen(graphic_libname.c_str(), RTLD_NOW);
  if (!this->graphic_handle)
    throw core_program_exception(dlerror());
}

Core_program::~Core_program()
{
  if (this->graphic_handle && dlclose(this->graphic_handle))
    throw core_program_exception(dlerror());
  if (this->game_handle && dlclose(this->game_handle))
    throw core_program_exception(dlerror());
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
