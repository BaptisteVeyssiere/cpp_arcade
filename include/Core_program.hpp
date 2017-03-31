//
// Core_program.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Fri Mar 31 14:15:00 2017 Baptiste Veyssiere
// Last update Fri Mar 31 14:45:05 2017 Baptiste Veyssiere
//

#ifndef __CORE_PROGRAM_HPP__
# define __CORE_PROGRAM_HPP__

#include <string>
#include <dlfcn.h>
#include "core_program_exception.hpp"

class	Core_program
{
  void	*graphic_handle;
  void	*game_handle;

private:
  Core_program(const Core_program &);
  Core_program	&operator=(const Core_program &);

public:
  Core_program(const std::string &);
  ~Core_program();

public:
  void	load_graphic_lib(const std::string &);
  void	*get_graphic_function(const std::string &) const;

  void	load_game_lib(const std::string &);
  void	*get_game_function(const std::string &) const;
};

#endif // !__CORE_PROGRAM_HPP__
