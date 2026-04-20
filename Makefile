SRC_DIR   = src
TEST_DIR  = tests
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
TEST_FLAGS = -Wall -Wextra -Werror -Iinclude -g
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

TEST_SRC  = $(PARSING_SRC) $(UTILS_SRC) $(RAYS_SRC)
TEST_OBJ  = $(TEST_SRC:%.c=$(OBJ_DIR)/%.o)

PARSING_TEST_NAMES = test_parse_map test_expand_tabs \
				 test_parse_player test_read_lines \
				 test_rgb test_parse_textures test_trim_spaces \
				 test_trim_map test_is_valid_path test_flood_fill \
				 test_is_closed

RAYS_TEST_NAMES = test_is_wall test_get_side_of_wall \
				 test_get_dist_to_wall test_cast_ray

MINIMAP_TEST_NAMES = test_put_square test_put_circle test_put_line \
				 test_make_draw_params

GAME_TEST_NAMES = test_move_player test_put_game_screen test_put_textures

TEST_NAMES = $(PARSING_TEST_NAMES) $(RAYS_TEST_NAMES) $(MINIMAP_TEST_NAMES) \
			 $(GAME_TEST_NAMES)

PARSING_TESTS = $(addprefix $(OBJ_DIR)/,$(PARSING_TEST_NAMES))
RAYS_TESTS    = $(addprefix $(OBJ_DIR)/,$(RAYS_TEST_NAMES))
MINIMAP_TESTS = $(addprefix $(OBJ_DIR)/,$(MINIMAP_TEST_NAMES))
GAME_TESTS    = $(addprefix $(OBJ_DIR)/,$(GAME_TEST_NAMES))
TESTS         = $(addprefix $(OBJ_DIR)/,$(TEST_NAMES))

MINIMAP_TEST_OBJ = $(MINIMAP_SRC:%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/utils/common.o
MINIMAP_MOCK_OBJ = $(OBJ_DIR)/mock_mlx.o

GAME_TEST_OBJ = $(GAME_SRC:%.c=$(OBJ_DIR)/%.o) \
				$(OBJ_DIR)/rays/is_wall.o \
				$(OBJ_DIR)/utils/common.o

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD) -DDEBUG=1
	@cmake --build $(MLX_BUILD) -j4

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(GUI_FLAGS) $(MATH_FLAG) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/mock_mlx.o: $(TEST_DIR)/mock_mlx.c
	@mkdir -p $(dir $@)
	@$(CC) $(TEST_FLAGS) -c $< -o $@

$(MINIMAP_TESTS): $(OBJ_DIR)/test_%: $(TEST_DIR)/test_%.c \
		$(MINIMAP_TEST_OBJ) $(MINIMAP_MOCK_OBJ) $(LIBFT)
	@$(CC) $(TEST_FLAGS) $< $(MINIMAP_TEST_OBJ) $(MINIMAP_MOCK_OBJ) \
		$(LIBFT) $(MATH_FLAG) -o $@

$(GAME_TESTS): $(OBJ_DIR)/test_%: $(TEST_DIR)/test_%.c \
		$(GAME_TEST_OBJ) $(MINIMAP_MOCK_OBJ) $(LIBFT)
	@$(CC) $(TEST_FLAGS) $< $(GAME_TEST_OBJ) $(MINIMAP_MOCK_OBJ) \
		$(LIBFT) $(MATH_FLAG) -o $@

$(OBJ_DIR)/test_%: $(TEST_DIR)/test_%.c $(TEST_OBJ) $(LIBFT)
	@$(CC) $(TEST_FLAGS) $< $(TEST_OBJ) $(LIBFT) $(MATH_FLAG) -o $@

re: fclean $(NAME)

define run_tests
	@status=0; \
	for t in $(1); do \
		echo "\nRunning $$t"; \
		if ./$$t; then \
			echo "\033[0;32mTest $$t PASSED\033[0m"; \
		else \
			echo "\033[0;31mTest $$t FAILED\033[0m"; \
			status=1; \
		fi; \
	done; \
	echo ; \
	exit $$status
endef

test: $(TESTS)
	$(call run_tests,$(TESTS))

test-parsing: $(PARSING_TESTS)
	$(call run_tests,$(PARSING_TESTS))

test-rays: $(RAYS_TESTS)
	$(call run_tests,$(RAYS_TESTS))

test-minimap: $(MINIMAP_TESTS)
	$(call run_tests,$(MINIMAP_TESTS))

test-game: $(GAME_TESTS)
	$(call run_tests,$(GAME_TESTS))

test-leaks: $(TESTS)
	@status=0; \
	for t in $(TESTS); do \
		tmpfile=$$(mktemp); \
		printf "Running %-30s" "$$t"; \
		$(VALGRIND) ./$$t > $$tmpfile 2>&1; \
		if [ $$? -eq 0 ]; then \
			echo "\033[0;32m OK\033[0m"; \
		else \
			echo "\033[0;31m LEAK\033[0m"; \
			cat $$tmpfile; \
			status=1; \
		fi; \
		rm -f $$tmpfile; \
	done; \
	echo; \
	exit $$status

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
	@rm -rf $(MLX42)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX_BUILD)
	@make -C $(LIBFT_DIR) clean

.PHONY: test test-parsing test-rays test-minimap test-game test-leaks clean
