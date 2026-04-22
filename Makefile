SRC_DIR   = src
OBJ_DIR   = build
LIBFT_DIR = libft
MLX_DIR = MLX42
MLX_BUILD = $(MLX_DIR)/build
PARSING_DIR = parsing
MINIMAP_DIR = minimap
GAME_DIR = game
UTILS_DIR = utils
RAYS_DIR = rays
HOOKS_DIR = hooks

NAME = cub3d

CC = cc

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_BUILD)/libmlx42.a

CFLAGS = -Wall -Wextra -Werror -Iinclude -g -O3
GUI_FLAGS = -lglfw -pthread -ldl
MATH_FLAG = -lm

VALGRIND = valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--errors-for-leak-kinds=definite \
	--error-exitcode=1

SOURCES  = main.c init_mlx.c initialize.c cleanup.c updaters.c

PARSING_SOURCES = is_valid_path.c parse_textures.c parse_rgb.c parse_map.c \
		parse_player.c helpers/free_map.c helpers/read_lines.c \
		helpers/expand_tabs.c helpers/parser_cleanup.c helpers/set_gnl.c \
		helpers/trim_map.c helpers/trim_spaces.c helpers/is_contiguous.c \
		helpers/flood_fill.c helpers/is_closed.c parse.c

MINIMAP_SOURCES =  put_player.c put_minimap.c put_line.c \
		put_circle.c put_square.c put_grid.c

GAME_SOURCES = put_game_screen.c put_textures.c move_player.c

RAYS_SOURCES = cast_ray.c is_wall.c ray_utils.c

UTILS_SOURCES = mlx_scale_image_into.c common.c degree_helpers.c

HOOKS_SOURCES = lifecycle.c input.c

GAME_SRC = $(addprefix $(GAME_DIR)/, $(GAME_SOURCES))
MINIMAP_SRC = $(addprefix $(MINIMAP_DIR)/, $(MINIMAP_SOURCES))
PARSING_SRC = $(addprefix $(PARSING_DIR)/, $(PARSING_SOURCES))
UTILS_SRC = $(addprefix $(UTILS_DIR)/, $(UTILS_SOURCES))
RAYS_SRC = $(addprefix $(RAYS_DIR)/, $(RAYS_SOURCES))
HOOKS_SRC = $(addprefix $(HOOKS_DIR)/, $(HOOKS_SOURCES))

SRC = $(SOURCES) $(PARSING_SRC) $(MINIMAP_SRC) $(GAME_SRC) \
		$(RAYS_SRC) $(UTILS_SRC) $(HOOKS_SRC)

OBJ  = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD)
	@cmake --build $(MLX_BUILD) -j4

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(GUI_FLAGS) $(MATH_FLAG) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean $(NAME)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
	@rm -rf $(MLX42)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX_BUILD)
	@make -C $(LIBFT_DIR) clean

.PHONY: all re fclean clean
