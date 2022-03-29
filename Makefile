# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sameye <sameye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 16:53:51 by sameye            #+#    #+#              #
#    Updated: 2022/03/29 12:03:25 by sameye           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################	COMPILER		#################

FT_NAMESPACE	=		-D NAMESPACE=ft
STD_NAMESPACE	=		-D NAMESPACE=std
CC			=		c++ -Wall -Wextra -Werror -std=c++98

################	DIRECTORIES		#################

SRCS_DIR	=		tests

OBJS_DIR	=		obj

#################	HEADER FILES	#################

INCLUDE		=		-I iterators \
					-I containers \
					-I utils \
					-I tests/test_utils/test_utils.hpp

#################	SOURCE FILES	#################

SRCS		=		main.cpp \
					vector_tests.cpp


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
					@$(CC) $(NAMESPACE) $(INCLUDE) $(OBJECTS) -o $(NAME)

$(OBJS_DIR):
					mkdir -p $@

$(OBJECTS):			$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
					@$(CC) $(FT_NAMESPACE) $(INCLUDE) -c $< -o $@

clean:
					@echo Cleaning minishell objects...
					@rm -f $(OBJECTS)

fclean:				clean
					@echo Cleaning binary...
					@rm -f $(NAME) $(NAME)_ft $(NAME)_std res/res_ft res/res_std res/res_diff

re:					fclean all

.PHONY:				all clean fclean re

################	TESTS			#################

ft_version:			$(OBJS_DIR) $(OBJECTS)
					@echo Building ...
					@$(CC) $(FT_NAMESPACE) $(INCLUDE) $(OBJECTS) -o $(NAME)_ft

std_version:			$(OBJS_DIR) $(OBJECTS)
					@echo Building ...
					@$(CC) $(STD_NAMESPACE) $(INCLUDE) $(OBJECTS) -o $(NAME)_std

test:
					@make fclean
					make ft_version
					@make clean
					make std_version
					@mkdir -p res
					@./ft_containers_ft > res/res_ft
					@./ft_containers_std > res/res_std
					@diff res/res_ft res/res_std > res/res_diff
					@make clean
					@[ -s res/res_diff ] && echo "\033[0;31m=>ERROR! Please check logs" || echo "\033[0;32m=>PERFECT!! No error"
					
