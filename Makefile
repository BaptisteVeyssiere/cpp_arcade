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

NIBBLERDIR	= games/nibbler/

NCURSESDIR	= lib/ncurses/

SDLDIR		= lib/sdl/

GLDIR		= lib/opengl

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
	@$(MAKE) -C $(NIBBLERDIR)
	@echo "Nibbler library linked"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(MKDIR) $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

lib: 
	@$(MAKE) -C $(NCURSESDIR)
	@echo "Ncurses library linked"
	@$(MAKE) -C $(SDLDIR)
	@echo "SDL library linked"
	@$(MAKE) -C $(GLDIR)
	@echo "openGL library linked"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(NCURSESDIR) clean
	@$(MAKE) -C $(SDLDIR) clean
	@$(MAKE) -C $(GLDIR) clean
	@$(MAKE) -C $(NIBBLERDIR) clean
	@echo "Cleanup complete!"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBNAME)
	@$(MAKE) -C $(NCURSESDIR) fclean
	@$(MAKE) -C $(GLDIR) fclean
	@$(MAKE) -C $(SDLDIR) fclean
	@$(MAKE) -C $(NIBBLERDIR) fclean

re: fclean all

.PHONY: all clean fclean re lib
