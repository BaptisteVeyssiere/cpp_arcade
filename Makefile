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

SNAKEDIR	= games/snake/

NCURSESDIR	= lib/ncurses/

SRC	= src/main.cpp \
	src/Core_program.cpp \
	src/directory_reader.cpp

SRCDIR	= src

OBJDIR	= obj

OBJ	= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CXXFLAGS	= -Iinclude -g

LDFLAGS		= -ldl

$(NAME): $(OBJ)
	@$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ)
	@echo "Linking complete!"
	@$(MAKE) -C $(NCURSESDIR)
	@echo "Ncurses library linked"
	@$(MAKE) -C $(SNAKEDIR)
	@echo "Snake library linked"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(MKDIR) $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(NCURSESDIR) clean
	@$(MAKE) -C $(SNAKEDIR) clean
	@echo "Cleanup complete!"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBNAME)
	@$(MAKE) -C $(NCURSESDIR) fclean
	@$(MAKE) -C $(SNAKEDIR) fclean

re: fclean all

.PHONY: all clean fclean re
