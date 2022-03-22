# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sameye <sameye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 16:53:51 by sameye            #+#    #+#              #
#    Updated: 2022/03/21 14:59:49 by sameye           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################	COMPILER		#################

CC			=		c++ -Wall -Wextra -Werror -std=c++98

################	DIRECTORIES		#################

SRCS_DIR	=		tests

OBJS_DIR	=		obj

#################	HEADER FILES	#################

INCLUDE		=		-I iterators \
					-I containers \
					-I utils

#################	SOURCE FILES	#################

SRCS		=		main.cpp


SOURCES		=		$(addprefix $(SRCS_DIR)/,$(SRCS))

#################	OBJECT FILES	#################

OBJS		=		$(addsuffix .o, $(basename $(SRCS)))
OBJECTS		=		$(addprefix $(OBJS_DIR)/,$(OBJS))

################	BINARIES		#################

NAME		=		ft_containers

################	TARGETS			#################

all:				$(NAME)

$(NAME):			$(OBJS_DIR) $(OBJECTS)
					@echo Building ...
					@$(CC) $(INCLUDE) $(OBJECTS) -o $(NAME)

$(OBJS_DIR):
					mkdir -p $@

$(OBJECTS):			$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
					@$(CC) $(INCLUDE) -c $< -o $@

clean:
					@echo Cleaning minishell objects...
					@rm -f $(OBJECTS)

fclean:				clean
					@echo Cleaning binary...
					@rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re