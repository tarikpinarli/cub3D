# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 13:16:45 by tpinarli          #+#    #+#              #
#    Updated: 2025/07/09 14:32:58 by tpinarli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -rf

SRC_DIR     = ./src
OBJ_DIR     = ./obj
INC_DIR     = ./include
LIB_DIR     = ./lib

LIBFT_DIR   = $(LIB_DIR)/libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX42_DIR   = $(LIB_DIR)/MLX42

SRCS        =	main.c arena.c error_exit.c \
				game/load_textures.c \
				cleanup/close_window.c \
				handle_keypress/handle_keypress.c \
				handle_keypress/update_player.c \
				init_dummy_data/init_dummy_data.c \
				render/raycast.c \
				render/draw_map.c

OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX42_DIR)/include -I/opt/homebrew/include

# MLX42 link flags for Linux
MLX42_LINUX_FLAGS = -L$(MLX42_DIR)/build -lmlx42 -ldl -lglfw -pthread -lm

# MLX42 link flags for macOS (includes glfw manually if needed)
MLX42_MAC_FLAGS = -L$(MLX42_DIR)/build -lmlx42 \
				  -L/opt/homebrew/lib -lglfw \
				  -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

# Default target (builds for Linux)
all: linux

# Build target for Linux
linux: $(LIBFT) $(MLX42_DIR)/build/libmlx42.a $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX42_LINUX_FLAGS) -o $(NAME)
	@echo "\033[0;32mLinux build complete!\033[0m"

# Build target for macOS
mac: $(LIBFT) $(MLX42_DIR)/build/libmlx42.a $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX42_MAC_FLAGS) -o $(NAME)
	@echo "\033[0;32mmacOS build complete!\033[0m"

# Compile .c files to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Clone and build MLX42
$(MLX42_DIR)/build/libmlx42.a:
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
	fi
	@cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR) -DMLX42_BUILD_EXAMPLES=OFF
	@cmake --build $(MLX42_DIR)/build --config Release

# Clean object files and MLX42 build
clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) -rf $(MLX42_DIR)/build

# Full clean (also deletes binary and MLX42 clone)
fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) -rf $(MLX42_DIR)
	@echo "\033[0;31mFull clean complete.\033[0m"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re linux mac
