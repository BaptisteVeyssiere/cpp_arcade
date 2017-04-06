##
## Makefile for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
##
## Made by Baptiste veyssiere
## Login   <VEYSSI_B@epitech.net>
##
## Started on  Wed May 18 21:26:30 2016 Baptiste veyssiere
##

NAME	= lib_arcade_opengl.so

RM	= rm -f

CXX	= g++

MKDIR	= mkdir -p

SRC	= src/libopengl.cpp 		\
	src/directory_reader.cpp

SRCDIR	= src

OBJDIR	= obj

OBJ	= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CXXFLAGS	= -Iinclude -I../../deps/SDL-1.2.15/install/include

LDFLAGS = -lSDL_image -L../../deps/SDL-1.2.15/install/lib/ -lGL

$(NAME): $(OBJ)
	@$(CXX) $(LDFLAGS) -shared -o $(NAME) $(OBJ)
	@echo "Linking complete!"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(MKDIR) $(OBJDIR)
	@$(CXX) $(LDFLAGS) $(CXXFLAGS) -c $< -o $@ -fPIC
	@echo "Compiled "$<" successfully!"

deps:
	cd ../../deps/SDL-1.2.15/; ./configure --prefix=${PWD}/install --enable-shared=yes ; make; make install;

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "Cleanup complete!"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
