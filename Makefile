# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 16:14:59 by isahmed           #+#    #+#              #
#    Updated: 2025/10/09 20:30:06 by isahmed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra  -L$(MLX_DIR) -I$(LIBFT_DIR) -I$(IDIR) -I$(MLX_DIR) -g 
SRCS = cub3D.c init.c utils.c render.c hooks.c parser.c utils2.c validate_input.c \
		validate_map_utils.c validate_map.c dda.c game.c control.c textures.c texture_utils.c \
		minimap.c sprites.c
		
NAME = cub3D

ODIR = objs/
SDIR = srcs/
IDIR = inc/
FULL_SRCS = $(addprefix $(SDIR), $(SRCS))
OBJS = $(patsubst $(SDIR)%.c, $(ODIR)%.o, $(FULL_SRCS))
MLX_DIR = minilibx-linux/
LIBFT_DIR = Libft/

all: $(NAME)

$(NAME): $(OBJS) $(MLX_DIR)libmlx.a $(LIBFT_DIR)libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lmlx -lX11 -lXext -lm $(LIBFT_DIR)libft.a

$(ODIR)%.o: $(SDIR)%.c  | $(ODIR)
	$(CC) $(CFLAGS) $< -c -o $@ 

$(ODIR): submodule
	@mkdir -p $(ODIR)

submodule:
	@git submodule update --init --recursive

$(MLX_DIR)libmlx.a:
	make -C $(MLX_DIR)

$(LIBFT_DIR)libft.a:
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

