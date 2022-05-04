# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sameye <sameye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 16:53:51 by sameye            #+#    #+#              #
#    Updated: 2022/05/04 11:46:05 by sameye           ###   ########.fr        #
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
					-I utils \
					-I tests/test_utils/test_utils.hpp

#################	SOURCE FILES	#################

SRCS		=		main.cpp \
					vector_tests.cpp \
					map_tests.cpp


SOURCES		=		$(addprefix $(SRCS_DIR)/,$(SRCS))

#################	OBJECT FILES	#################

OBJS		=		$(addsuffix .o, $(basename $(SRCS)))
OBJECTS		=		$(addprefix $(OBJS_DIR)/,$(OBJS))

################	BINARIES		#################

NAME		=		ft

################	TARGETS			#################

all:				$(NAME)

$(NAME):			$(OBJS_DIR) $(OBJECTS)
					@echo Building ...
					@$(CC) -DNAMESPACE=$(NAME) $(INCLUDE) $(OBJECTS) -o $(NAME)

$(OBJS_DIR):
					mkdir -p $@

$(OBJECTS):			$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
					@$(CC) -DNAMESPACE=$(NAME) $(INCLUDE) -c $< -o $@

clean:
					@echo Cleaning minishell objects...
					@rm -f $(OBJECTS)

fclean:				clean
					@echo Cleaning binary...
					@rm -f $(NAME) ft std res/res_ft res/res_std res/res_diff dotgraph.txt

re:					fclean all

.PHONY:				all clean fclean re

################	TESTS			#################

test:
					@make fclean
					make all NAME=ft
					@make clean
					make all NAME=std
					@make clean
					@mkdir -p res
					@-./ft > res/res_ft
					@-./std > res/res_std
					@-diff res/res_ft res/res_std > res/res_diff
					@[ -s res/res_diff ] && echo "\033[0;31m=>ERROR! Please check logs" || echo "\033[0;32m=>PERFECT!! No error"
