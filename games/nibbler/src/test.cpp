#include <iostream>
#include "../include/Protocol.hpp"

int	main()
{
  std::cout << sizeof(arcade::WhereAmI) + sizeof(arcade::Position) << std::endl;
  return (0);
}
