# Directories
SRC_DIR   = src
TEST_DIR  = tests
OBJ_DIR   = build
LIBFT_DIR = libft

# Library
LIBFT = $(LIBFT_DIR)/libft.a

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -Iinclude -g

# Valgrind for leak checking
VALGRIND = valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--errors-for-leak-kinds=definite \
	--error-exitcode=1

# Source files
SRC  = parse_textures.c
OBJ  = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Test executables (stored in build)
TESTS = $(OBJ_DIR)/test_parse_textures

# Build libft if needed
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Ensure build directory exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile source files to build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@cc $(CFLAGS) -c $< -o $@

# Compile tests to build/
$(OBJ_DIR)/test_%: $(TEST_DIR)/test_%.c $(OBJ) $(LIBFT) | $(OBJ_DIR)
	@cc $(CFLAGS) $< $(OBJ) $(LIBFT) -o $@

# Run all tests
test: $(TESTS)
	@for t in $(TESTS); do \
		echo "Running $$t"; \
		./$$t || exit 1; \
	done

# Run all tests under Valgrind to check leaks
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

# Clean build files and test executables
clean:
	rm -rf $(OBJ_DIR)

.PHONY: test test-leaks clean
