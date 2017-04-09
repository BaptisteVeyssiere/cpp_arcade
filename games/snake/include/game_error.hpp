//
// game_error.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade/games/snake
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Tue Apr  4 00:50:20 2017 Baptiste Veyssiere
// Last update Tue Apr  4 00:50:47 2017 Baptiste Veyssiere
//

#ifndef __GAME_ERROR_HPP__
# define __GAME_ERROR_HPP__

#include <string>
#include <stdexcept>

class	game_error : public std::exception
{
public:
  ~game_error() throw() {}
  game_error(std::string const &msg):
    _msg(msg) {}
  const char* what() const throw()
  { return _msg.c_str(); }
private:
  std::string	_msg;
};

#endif // !__GAME_ERROR_HPP__
