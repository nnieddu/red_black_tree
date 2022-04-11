# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ninieddu <ninieddu@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 06:10:57 by ninieddu          #+#    #+#              #
#    Updated: 2022/04/04 17:56:41 by ninieddu         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	=	rbt

COMP 	=	c++

# FLAG	=	-Wall -Wextra -Werror -std=c++98
FLAG	=	-Wall -Wextra -std=c++98

SRC		=	mymain.cpp 

INCS	=

OBJ		=	$(SRC:.cpp=.o)

%.o : %.cpp $(INCS)
	$(COMP) $(FLAG) -c $< -o $@

all : $(NAME) runv
# all : $(NAME)

$(NAME) : $(OBJ)
	$(COMP) $(FLAG) $(OBJ) -o $(NAME)

run : $(NAME)
	./$(NAME)
	
runv : $(NAME)
	valgrind ./$(NAME)

clean :
	rm -f $(OBJ)

fclean :
	rm -f $(NAME) $(OBJ)

re : fclean all

.PHONY : all clean fclean re run