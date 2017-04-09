//
// Core_program.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_arcade
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Fri Mar 31 14:15:00 2017 Baptiste Veyssiere
// Last update Sun Apr  9 05:58:24 2017 Baptiste Veyssiere
//

#ifndef __CORE_PROGRAM_HPP__
# define __CORE_PROGRAM_HPP__

# include <string>
# include <dlfcn.h>
# include <unistd.h>
# include <iostream>
# include <sstream>
# include <fstream>
# include <sys/types.h>
# include <dirent.h>
# include <algorithm>
# include "core_program_exception.hpp"
# include "technical_spec.hpp"
# include "gamedata.hpp"

typedef struct	s_score
{
  std::string	username;
  unsigned int	score;
}		t_score;

class	Core_program
{
public:
  void					*graphic_handle;
  void					*game_handle;
  std::vector<std::string>		game_list;
  std::vector<std::string>		graph_list;
  std::vector<std::vector<t_score>>	score_list;
  std::string				game;
  std::string				username;
  int					graph_selector;
  int					game_selector;

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
  void	Display_menu();
  void	Add_Score(unsigned int);
  void	Save_score() const;
  int	Get_selected_game();

private:
  void	Set_Games();
  void	Set_Graph();
  void	Set_Scores(const std::string &);
  void	Aff_Games() const;
  void	Aff_Graph() const;
  void	Aff_Scores() const;
  void	Get_Username();
};

#endif // !__CORE_PROGRAM_HPP__
