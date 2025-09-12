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

NAME:= philo
CC:= cc
CFLAGS:= -Wextra -Wall -Werror -g -pthread

SRCS:= $(shell find ./src -iname "*.c")
OBJS:= ${SRCS:.c=.o}

HEADERS:= -I .

GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Creating executable $@...$(NC)"
	@$(CC) $(OBJS) -o $(NAME) -pthread
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(NC)"

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