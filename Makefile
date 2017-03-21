##
## Makefile for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
##
## Made by Baptiste veyssiere
## Login   <VEYSSI_B@epitech.net>
##
## Started on  Wed May 18 21:26:30 2016 Baptiste veyssiere
##

NAME	= arcade

RM	= rm -f

CXX	= g++

MKDIR	= mkdir -p

SRC	= src/main.cpp

SRCDIR	= src

OBJDIR	= obj

OBJ	= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CXXFLAGS	= -Iinclude

$(NAME): $(OBJ)
	@$(CXX) -o $(NAME) $(OBJ)
	@echo "Linking complete!"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(MKDIR) $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "Cleanup complete!"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
