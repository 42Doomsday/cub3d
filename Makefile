SRC_DIR   = src
TEST_DIR  = tests
OBJ_DIR   = build
LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -Iinclude -g

VALGRIND = valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--errors-for-leak-kinds=definite \
	--error-exitcode=1

SRC  = is_valid_path.c parse_textures.c parse_map.c free_map.c \
		read_lines.c parse_player.c expand_tabs.c

OBJ  = $(SRC:%.c=$(OBJ_DIR)/%.o)

TEST_NAMES = test_parse_textures test_is_valid_path test_parse_map \
				test_expand_tabs test_parse_player test_read_lines

TESTS      = $(addprefix $(OBJ_DIR)/,$(TEST_NAMES))

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@cc $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test_%: $(TEST_DIR)/test_%.c $(OBJ) $(LIBFT) | $(OBJ_DIR)
	@cc $(CFLAGS) $< $(OBJ) $(LIBFT) -o $@

test: $(TESTS)
	@for t in $(TESTS); do \
		echo "\nRunning $$t"; \
		if ./$$t; then \
			echo "\033[0;32mTest $$t PASSED\033[0m"; \
		else \
			echo "\033[0;31mTest $$t FAILED\033[0m"; \
			exit 1; \
		fi; \
	done


test-leaks: $(TESTS)
	@for t in $(TESTS); do \
		printf "Running %-25s" "$$t"; \
		$(VALGRIND) ./$$t; \
		if [ $$? -eq 0 ]; then \
			echo "\033[0;32m OK\033[0m"; \
		else \
			echo "\033[0;31m LEAK\033[0m"; \
		fi; \
	done

clean:
	@rm -rf $(OBJ_DIR)

.PHONY: test test-leaks clean
