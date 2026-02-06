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

SRC  = is_valid_path.c parse_textures.c
OBJ  = $(SRC:%.c=$(OBJ_DIR)/%.o)

TESTS = $(OBJ_DIR)/test_parse_textures $(OBJ_DIR)/test_is_valid_path

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
		./$$t || exit 1; \
	done


test-leaks: $(TESTS)
	@for t in $(TESTS); do \
		printf "Running %-25s" "$$t"; \
		$(VALGRIND) ./$$t > /dev/null 2>&1; \
		if [ $$? -eq 0 ]; then \
			echo " OK"; \
		else \
			echo " LEAK"; \
		fi; \
	done

clean:
	rm -rf $(OBJ_DIR)

.PHONY: test test-leaks clean
