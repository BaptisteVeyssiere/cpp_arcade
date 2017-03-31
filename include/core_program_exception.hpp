//
// core_program_exception.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Fri Mar 31 14:45:16 2017 Baptiste Veyssiere
// Last update Fri Mar 31 14:46:59 2017 Baptiste Veyssiere
//

#ifndef __CORE_PROGRAM_EXCEPTION_HPP__
# define __CORE_PROGRAM_EXCEPTION_HPP__

#include <string>
#include <stdexcept>

class	core_program_exception : public std::exception
{
public:
  ~core_program_exception() throw() {}
  core_program_exception(std::string const &msg):
    _msg(msg) {}
  const char* what() const throw()
  { return _msg.c_str(); }
private:
  std::string	_msg;
};

#endif // !__CORE_PROGRAM_EXCEPTION_HPP__
