CC = cc
CFLAGS = -Wall -Wextra -Werror -L$(MLX_DIR) -I$(MLX_DIR) -g
SRCS = cub3D.c init.c utils.c render.c hooks.c
NAME = cub3D

ODIR = objs
OBJS = $(patsubst %.c, $(ODIR)/%.o, $(SRCS))
MLX_DIR = minilibx-linux

all: $(NAME) 

$(NAME): $(OBJS) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lmlx -lX11 -lXext -lm

$(ODIR)/%.o: %.c | $(ODIR)
	$(CC) $(CFLAGS) $< -c -o $@ 

$(ODIR):
	mkdir -p $(ODIR)

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
