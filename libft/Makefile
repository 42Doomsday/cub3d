# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 18:43:41 by clouden           #+#    #+#              #
#    Updated: 2026/02/05 14:54:33 by clouden          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE    =	\033[0;34m
RESET   =	\033[0m 
GREEN   =	\033[0;32m

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude
CFLAGS	+= -g3

# Name of the output static library
NAME    = libft.a

# Source and object files

# Define input/output 
IO_DIR	=	io/
IO_SRCS	=	$(IO_DIR)ft_putendl_fd.c\
			$(IO_DIR)ft_putchar_fd.c\
			$(IO_DIR)ft_putstr_fd.c\
			$(IO_DIR)ft_putnbr_fd.c\
			$(IO_DIR)ft_putunbr_fd.c\
			$(IO_DIR)ft_puthex_fd.c\

# Define math	
MATH_DIR	=	math/
MATH_SRCS	=	$(MATH_DIR)ft_power.c\

# Define chars
CHAR_DIR 	=	chars/
CHAR_SRCS	=	$(CHAR_DIR)ft_isalnum.c\
				$(CHAR_DIR)ft_isalpha.c\
				$(CHAR_DIR)ft_isascii.c\
				$(CHAR_DIR)ft_isdigit.c\
				$(CHAR_DIR)ft_isprint.c\
				$(CHAR_DIR)ft_tolower.c\
				$(CHAR_DIR)ft_toupper.c

# Define conversions
CONV_DIR	=	convs/
CONV_SRCS	=	$(CONV_DIR)ft_itoa.c\
				$(CONV_DIR)ft_atol.c\
				$(CONV_DIR)ft_atof.c\
				$(CONV_DIR)ft_atoi.c

# Define memory
MEM_DIR		=	memory/
MEM_SRCS	=	$(MEM_DIR)ft_bzero.c\
				$(MEM_DIR)ft_memchr.c\
				$(MEM_DIR)ft_memcmp.c\
				$(MEM_DIR)ft_memcpy.c\
				$(MEM_DIR)ft_memmove.c\
				$(MEM_DIR)ft_memset.c\
				$(MEM_DIR)ft_calloc.c\
				$(MEM_DIR)ft_strarr_free.c

# Define lists
LIST_DIR	=	lists/
LIST_SRCS	=	$(LIST_DIR)ft_lstnew.c\
				$(LIST_DIR)ft_lstadd_front.c\
				$(LIST_DIR)ft_lstsize.c\
				$(LIST_DIR)ft_lstlast.c\
				$(LIST_DIR)ft_lstadd_back.c\
				$(LIST_DIR)ft_lstdelone.c\
				$(LIST_DIR)ft_lstclear.c\
				$(LIST_DIR)ft_lstiter.c\
				$(LIST_DIR)ft_lstmap.c

# Define strings
STR_DIR		=	strings/
STR_SRCS	=	$(STR_DIR)ft_strlcpy.c\
				$(STR_DIR)ft_strlcat.c\
				$(STR_DIR)ft_substr.c\
				$(STR_DIR)ft_strlen.c\
				$(STR_DIR)ft_strjoin.c\
				$(STR_DIR)ft_strtrim.c\
				$(STR_DIR)ft_strjoin_n.c\
				$(STR_DIR)ft_split.c\
				$(STR_DIR)ft_strmapi.c\
				$(STR_DIR)ft_strchr.c\
				$(STR_DIR)ft_strdup.c\
				$(STR_DIR)ft_strnstr.c\
				$(STR_DIR)ft_strncmp.c\
				$(STR_DIR)ft_striteri.c\
				$(STR_DIR)ft_strrchr.c\
				$(STR_DIR)ft_strarr_len.c\
				$(STR_DIR)ft_strarr_join.c\

# Define get_next_line
GNL_DIR 	= 	get_next_line/
GNL_SRCS	= 	$(GNL_DIR)get_next_line.c\
				$(GNL_DIR)get_next_line_utils.c

ALL_SRCS 	=	$(GNL_SRCS) \
				$(MEM_SRCS) \
				$(LIST_SRCS) \
				$(STR_SRCS) \
				$(CONV_SRCS) \
				$(CHAR_SRCS) \
				$(MATH_SRCS) \
				$(IO_SRCS)

OBJS		= 	$(ALL_SRCS:.c=.o)

# Default rule
all: $(NAME)

# Rule to build the library from object files
$(NAME): $(OBJS)
	@echo "$(GREEN)[LIBFT]$(RESET) Creating static library..."
	@ar rcs $(NAME) $(OBJS)

# Rule to compile .c to .o
%.o: %.c
# 	@printf "$(GREEN)[COMPILING]$(RESET) %-20s → %s\n" $< $@
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile test
test: $(TEST_OBJ) $(NAME)
	@echo "$(GREEN)[LIBFT]$(RESET) Ready For Testing..."
	@$(CC) $(CFLAGS) $^ -o $(TEST_BIN) 

# Clean object files
clean:
	@echo "Cleaning object libft files..."	
	@rm -f $(OBJS) $(TEST_OBJ)

# Clean object files and library
fclean: clean
	@echo "Removing libft..."
	@rm -f $(NAME) $(TEST_BIN)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re test 
