SRC_DIR   = src
TEST_DIR  = tests
OBJ_DIR   = build
LIBFT_DIR = libft
MLX_DIR = MLX42
MLX_BUILD = $(MLX_DIR)/build
PARSING_DIR = parsing
MINIMAP_DIR = minimap

NAME = game

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_BUILD)/libmlx42.a

CFLAGS = -Wall -Wextra -Werror -Iinclude -g
EXTRA_FLAGS = -lglfw -ldl -pthread -lm

VALGRIND = valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--errors-for-leak-kinds=definite \
	--error-exitcode=1

SOURCES  = main.c

PARSING_SOURCES = is_valid_path.c parse_textures.c parse_rgb.c parse_map.c \
		parse_player.c helpers/free_map.c helpers/read_lines.c \
		helpers/expand_tabs.c helpers/parser_cleanup.c helpers/set_gnl.c \
		helpers/trim_map.c helpers/trim_spaces.c helpers/is_contiguous.c \
		helpers/flood_fill.c helpers/is_closed.c parse.c

MINIMAP_SOURCES = move_player.c put_player.c helpers/utils.c

MINIMAP_SRC = $(addprefix $(MINIMAP_DIR)/, $(MINIMAP_SOURCES))
PARSING_SRC = $(addprefix $(PARSING_DIR)/, $(PARSING_SOURCES))

SRC = $(SOURCES) $(PARSING_SRC) $(MINIMAP_SRC)

OBJ  = $(SRC:%.c=$(OBJ_DIR)/%.o)

TEST_SRC  = $(filter-out main.c, $(SRC))
TEST_OBJ  = $(TEST_SRC:%.c=$(OBJ_DIR)/%.o)

TEST_NAMES = test_parse_map test_expand_tabs \
				 test_parse_player test_read_lines \
				 test_rgb test_parse_textures test_trim_spaces \
				 test_trim_map test_is_valid_path test_flood_fill \
				 test_is_closed

TESTS      = $(addprefix $(OBJ_DIR)/,$(TEST_NAMES))

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD)
	@cmake --build $(MLX_BUILD) -j4

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@cc $(CFLAGS) $(EXTRA_FLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test_%: $(TEST_DIR)/test_%.c $(TEST_OBJ) $(LIBFT) | $(OBJ_DIR)
	@cc $(CFLAGS) $< $(TEST_OBJ) $(LIBFT) -o $@

re: fclean $(NAME)

test: $(TESTS)
	@status=0; \
	for t in $(TESTS); do \
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


test-leaks: $(TESTS)
	@status=0; \
	for t in $(TESTS); do \
		tmpfile=$$(mktemp); \
		printf "Running %-25s" "$$t"; \
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

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX_BUILD)
	@make -C $(LIBFT_DIR) clean

.PHONY: test test-leaks clean
