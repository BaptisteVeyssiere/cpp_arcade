//
// library_error.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Fri Mar 31 14:03:44 2017 Baptiste Veyssiere
// Last update Fri Mar 31 14:04:49 2017 Baptiste Veyssiere
//

#ifndef __LIBRARY_ERROR_HPP__
# define __LIBRARY_ERROR_HPP__

#include <string>
#include <stdexcept>

class	library_error : public std::exception
{
public:
  ~library_error() throw() {}
  library_error(std::string const &msg):
    _msg(msg) {}
  const char* what() const throw()
  { return _msg.c_str(); }
private:
  std::string	_msg;
};

#endif // !__LIBRARY_ERROR_HPP__
