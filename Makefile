NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -Wnull-dereference -Wuninitialized #-Wunused -pedantic #-Wconversion

SRCS		= main.c \
			  sources/game/start.c sources/game/exit.c sources/game/loop.c sources/game/hooks.c \
			  	sources/game/keyboard_handle.c sources/game/key_hooks.c	\
			  sources/parse/parse.c sources/parse/validate.c \
			  sources/render/render.c	\
			  sources/utils/vec_utils.c sources/utils/image.c sources/utils/image2.c sources/utils/vec_ops.c \
			  	sources/utils/time.c

OBJ_DIR		= obj
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

MLX_DIR		= mlx
MLX_A		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -lXext -lX11 -lm 

INCLUDES	= -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)

RM			= rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_A) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
