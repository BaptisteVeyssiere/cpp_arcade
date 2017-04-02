//
// directory_reader.cpp for Project-Master in /home/veyssi_b/test/ncurses
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sun Mar 26 23:06:22 2017 Baptiste Veyssiere
// Last update Sun Apr  2 22:49:10 2017 Baptiste Veyssiere
//

#include <string>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "library_error.hpp"

void	get_directory_filenames(const std::string &name,
				std::vector<std::string> &tab)
{
  DIR				*dir;
  struct dirent			*file;
  std::string			full_path;
  std::string			path;
  struct stat			path_stat;
  std::vector<std::string>	buffer;

  if ((dir = opendir(name.c_str())) == NULL)
    throw library_error("Error while calling opendir()");
  path = name;
  if (name[name.length() - 1] != '/')
    path += "/";
  while ((file = readdir(dir)))
    {
      full_path = path + std::string(file->d_name);
      if (file->d_name[0] == '.')
	continue;
      if (stat(full_path.c_str(), &path_stat) == -1)
	throw library_error("Error while calling stat()");
      if (S_ISDIR(path_stat.st_mode))
	{
	  get_directory_filenames(full_path, buffer);
	  for (size_t i = 0; i < buffer.size(); i++)
	    tab.push_back(buffer[i]);
	}
      else
	tab.push_back(full_path);
    }
  if (closedir(dir) == -1)
    throw library_error("Error while calling closedir()");
}
