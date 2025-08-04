# Main Makefile for the entire project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Include directories
INCLUDES = -I./game -I./map_parse -I./libft -I./getnextline -I./minilibx-linux

# Libraries to link against
LIBFT = ./libft/libft.a
GNL = ./getnextline/getnextline.a
MLX = ./minilibx-linux

LIBMLX = -L$(MLX) -lmlx -L/usr/lib -lXext -lX11 -lm

# The executable name
NAME = cub3d

# List of all directories to be built
DIRS = libft getnextline ftprint

# Main source files
SRC = src/main.c \
		src/free_game.c \
		src/parse/utils.c \
		src/render/init_graphics.c \
		src/render/init_player.c \
		src/render/movement.c \
		src/render/rot.c \
		src/render/render_frame.c \


# Object files corresponding to the source files
OBJ = $(SRC:.c=.o)

# Default target to build everything
all: $(LIBFT) $(GNL) $(NAME)

# Rule to build the final executable
$(NAME): $(OBJ)
	@echo "Building executable..."
	$(CC) $(OBJ) $(LIBFT) $(GNL) $(LIBMLX) -o $(NAME)

# Compile object files from source files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to build the libft library
$(LIBFT):
	$(MAKE) -C libft

# Rule to build the getnextline library
$(GNL):
	$(MAKE) -C getnextline

# Build the game and parsing directories
$(DIRS): 
	$(MAKE) -C $@

# Clean all object files and binaries
clean:
	@echo "Cleaning..."
	rm -f $(OBJ)
	$(MAKE) -C libft clean
	$(MAKE) -C getnextline clean

# Remove object files, executable and libraries
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	$(MAKE) -C getnextline fclean

# Rebuild everything from scratch
re: fclean all
