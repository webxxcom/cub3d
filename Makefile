NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -O3 -Wnull-dereference -Wuninitialized #-Wunused -pedantic -Wconversion

SRC_FLDR	= sources

SRCS		= main.c \
			  $(SRC_FLDR)/game/exit.c $(SRC_FLDR)/game/hooks.c $(SRC_FLDR)/game/key_press_hook.c \
			  	$(SRC_FLDR)/game/key_release_hook.c $(SRC_FLDR)/game/process_keypress.c $(SRC_FLDR)/game/main_loop.c \
				$(SRC_FLDR)/game/mvement_handle.c $(SRC_FLDR)/game/start.c $(SRC_FLDR)/game/minimap.c \
				$(SRC_FLDR)/game/inits.c $(SRC_FLDR)/game/inits2.c $(SRC_FLDR)/game/frame.c $(SRC_FLDR)/game/camera.c \
				$(SRC_FLDR)/game/animation.c $(SRC_FLDR)/game/animation_move.c $(SRC_FLDR)/game/entity.c \
			  $(SRC_FLDR)/parse/parse.c $(SRC_FLDR)/parse/validate.c \
			  $(SRC_FLDR)/render/render.c $(SRC_FLDR)/render/put_minimap.c $(SRC_FLDR)/render/perform_dda.c \
			  	$(SRC_FLDR)/render/draw_vert_line.c $(SRC_FLDR)/render/sprite.c \
				$(SRC_FLDR)/render/draw_floor_and_ceiling.c \
			  $(SRC_FLDR)/utils/vec_utils.c $(SRC_FLDR)/utils/image.c $(SRC_FLDR)/utils/image2.c $(SRC_FLDR)/utils/vec_ops.c \
			  	$(SRC_FLDR)/utils/time.c $(SRC_FLDR)/utils/utils.c $(SRC_FLDR)/utils/array.c $(SRC_FLDR)/utils/draw_utils.c

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
