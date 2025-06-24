OS := $(shell uname)

ifeq ($(OS), Darwin)
	MLX_DIR		=	./src/libs/minilibx-linux
	MLX_FLAGS	=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -g -O3
	MLX			=	$(MLX_DIR)/libmlx.a
else
	MLX_DIR		=	./src/libs/minilibx-linux
	MLX_FLAGS	=	-L$(MLX_DIR) -lmlx -lXext -lX11 -lm -g
	MLX			=	$(MLX_DIR)/libmlx.a
endif


NAME		=	cub3D

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

LIBFT_DIR	=	./src/libs/libft
LIBFT		=	$(LIBFT_DIR)/libft.a

INCLUDES	=	-I$(MLX_DIR) -I$(LIBFT_DIR)/inc

SRC_DIR		=	./src
OBJ_DIR		=	./obj

SRC			=	$(SRC_DIR)/code/main.c \
				$(SRC_DIR)/code/graphics/graph_main.c \
				$(SRC_DIR)/code/graphics/graph_init.c \
				$(SRC_DIR)/code/graphics/graph_gameplay.c \
				$(SRC_DIR)/code/graphics/graph_move.c \
				$(SRC_DIR)/code/graphics/graph_move_rotate.c \
				$(SRC_DIR)/code/graphics/graph_key.c \
				$(SRC_DIR)/code/graphics/graph_raycast.c \
				$(SRC_DIR)/code/graphics/graph_ray_utils.c \
				$(SRC_DIR)/code/parsing/pars_algo.c \
				$(SRC_DIR)/code/parsing/pars_color.c \
				$(SRC_DIR)/code/parsing/pars_main.c \
				$(SRC_DIR)/code/parsing/pars_storage.c \
				$(SRC_DIR)/code/parsing/pars_verif.c \
				$(SRC_DIR)/code/parsing/pars_utils.c \
				$(SRC_DIR)/code/utils/utils.c \

OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(MLX):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@echo "\033[0;32mMlx compiled ✅"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "\033[0;32mMinilib compiled ✅"

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(MLX_FLAGS) $(INCLUDES)
	@echo "\033[0;32mCube3D a finis sa compilation ✅ -> ⚙️ \033[1;34m./cube3D [path_to_map]"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -g3 -c $< $(INCLUDES)

clean:
	@$(RM) -r $(OBJ_DIR)  > /dev/null 2>&1
	@$(MAKE) -C $(LIBFT_DIR) clean  > /dev/null 2>&1
	@echo "\033[0;31mMiniLib & cube3D object delete"

fclean: clean
	@$(RM) $(NAME)  > /dev/null 2>&1 
	@$(MAKE) -C $(LIBFT_DIR) fclean  > /dev/null 2>&1 
	@$(MAKE) -C $(MLX_DIR) clean  > /dev/null 2>&1
	@echo "\033[0;31mProject has been clean !"

re: fclean all

.PHONY: all clean fclean re