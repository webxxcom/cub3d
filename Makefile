NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS		= main.c \
			sources/game/start.c sources/game/exit.c \
			sources/parse/parse_map.c sources/parse/parse_textures.c sources/parse/validate.c
OBJS		= $(SRCS:%.c=%.o)

LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

MLX_DIR		= mlx
MLX_A		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -lXext -lX11 -lm 

INCLUDES	= -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_A) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re