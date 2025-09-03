CC = cc
CFLAGS = -Wall -Wextra -Werror -L$(MLX_DIR) -I$(MLX_DIR) -g
SRCS = cub3D.c init.c utils.c render.c hooks.c
NAME = cub3D
OBJS = $(patsubst %.c, %.o, $(SRCS))
MLX_DIR = minilibx-linux

all: $(NAME) 

$(NAME): $(OBJS) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lmlx -lX11 -lXext -lm

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@ 

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
