# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samoore <samoore@student.42london.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 14:38:19 by samoore           #+#    #+#              #
#    Updated: 2024/01/22 12:10:49 by samoore          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Werror -Wextra
FILE = pipex

SRC_FILES = ft_split.c ft_strings.c init.c paths.c heredoc.c pipex.c
OBJ_FILES = $(patsubst %c, %o, $(SRC_FILES))

all: $(FILE)

$(FILE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
