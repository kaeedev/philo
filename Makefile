# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 13:39:10 by luviso-p          #+#    #+#              #
#    Updated: 2025/09/11 13:39:10 by luviso-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= pipex
CC:= cc
CFLAGS:= -Wextra -Wall -Werror -g

SRCS:= $(shell find ./srcs -iname "*.c")
OBJS:= ${SRCS:.c=.o}

HEADERS:= -I ./includes -I 

GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Enlazando $@...$(NC)"
	@$(CC) $(OBJS)
	@echo "$(GREEN)✅ philosopher compile success!$(NC)"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\r"

clean:
	@rm -rf $(OBJS)
	@echo "Clean objects files."

fclean: clean
	@rm -rf $(NAME)
	@echo "Clean all."

re: fclean all

.PHONY: all clean fclean re