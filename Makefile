# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 17:47:01 by ojacobs           #+#    #+#              #
#    Updated: 2024/08/02 23:38:50 by ojacobs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 						= pipex

 SRCS =  $(SRC_DIR)pipex_innit.c\
    	$(SRC_DIR)pipex_utils.c\
		$(SRC_DIR)pipex_aid.c\
		$(SRC_DIR)pipex_split.c\
    	$(SRC_DIR)pipex.c

RM = rm -rf

CC = gcc -g #-fsanitize=address

CFLAGS = -Werror -Wall -Wextra

SRC_DIR = src/

OBJ_DIR = obj

INC_DIR = inc

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFTDIR = ./$(INC_DIR)/libft

LIBFTA = $(LIBFTDIR)/libft.a

NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
WARNING='\033[33m'
DANGER='\033[31m'

all: $(NAME)

$(NAME): $(LIBFTA) $(SRC) $(OBJS)
	@$(CC) $(OBJS) $(LIBFTA) -o $@
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJ_DIR)/%.o: %.c $(LIBFTA)
	@echo $(CURSIVE) "     - Building $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFTA):
	@echo $(CURSIVE)$(WARNING) "     - (Wait a sec...) Building $@" $(NONE)
	@make all -C $(LIBFTDIR) > /dev/null || true

clean:
	@$(RM) $(OBJS) $(OBJ_DIR)
	@make -C $(LIBFTDIR) clean > /dev/null || true
	@echo $(CURSIVE)$(GRAY) "     - Object files removed" $(NONE)

fclean: clean
	@rm -f $(NAME) > /dev/null || true
	@make -C $(LIBFTDIR) fclean > /dev/null || true
	@echo $(CURSIVE)$(GRAY) "     - $(NAME) removed" $(NONE)

re: fclean all

.PHONY: all clean fclean re