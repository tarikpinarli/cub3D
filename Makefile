# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 13:16:45 by tpinarli          #+#    #+#              #
#    Updated: 2025/07/08 19:42:32 by tpinarli         ###   ########.fr        #
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
MLX42_INC   = -I$(MLX42_DIR)/include
MLX42_FLAGS = -L$(MLX42_DIR)/build -lmlx42 -ldl -lglfw -pthread -lm

SRCS        =	main.c arena.c error_exit.c \
				game/init_game.c \
				cleanup/close_window.c \
				handle_keypress/handle_keypress.c

OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)

# Default target
all: $(NAME)

$(NAME): $(LIBFT) $(MLX42_DIR)/build/libmlx42.a $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(MLX42_INC) $(OBJS) $(LIBFT) $(MLX42_FLAGS) -o $(NAME)
	@echo "\033[0;32mBuild complete using MLX42!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX42_DIR)/build/libmlx42.a:
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
	fi
	@cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR) -DMLX42_BUILD_EXAMPLES=OFF
	@cmake --build $(MLX42_DIR)/build --config Release

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) -rf $(MLX42_DIR)/build

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) -rf $(MLX42_DIR)
	@echo "\033[0;31mFull clean complete.\033[0m"

re: fclean all

.PHONY: all clean fclean re
