# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 13:16:45 by tpinarli          #+#    #+#              #
#    Updated: 2025/07/08 15:27:21 by tpinarli         ###   ########.fr        #
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

SRCS        = main.c arena.c error_exit.c game/init_game.c
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)

#Linux
MLX_LINUX_DIR   = $(LIB_DIR)/minilibx-linux
MLX_LINUX_INC   = -I$(MLX_LINUX_DIR)
MLX_LINUX_FLAGS = -L$(MLX_LINUX_DIR) -lmlx -lXext -lX11 -lm

#macOS
MLX_MAC_DIR     = $(LIB_DIR)/minilibx
MLX_MAC_INC     = -I$(MLX_MAC_DIR)
MLX_MAC_FLAGS   = -L$(MLX_MAC_DIR) -lmlx -framework OpenGL -framework AppKit

#Default target
all: linux

linux: $(LIBFT) $(MLX_LINUX_DIR)/libmlx.a $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(MLX_LINUX_INC) $(OBJS) $(LIBFT) $(MLX_LINUX_FLAGS) -o $(NAME)
	@echo "\033[0;32mLinux build complete!\033[0m"

mac: $(LIBFT) $(OBJS)
	@$(MAKE) -C $(MLX_MAC_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) $(MLX_MAC_INC) $(OBJS) $(LIBFT) $(MLX_MAC_FLAGS) -o $(NAME)
	@echo "\033[0;32mmacOS build complete!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LINUX_DIR)/libmlx.a:
	@if [ ! -f "$(MLX_LINUX_DIR)/mlx.h" ]; then \
		echo "Cloning MiniLibX for Linux..."; \
		$(RM) $(MLX_LINUX_DIR); \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_LINUX_DIR); \
	fi
	@$(MAKE) -C $(MLX_LINUX_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_MAC_DIR)" ]; then $(MAKE) -C $(MLX_MAC_DIR) clean; fi
	@$(RM) -rf $(MLX_LINUX_DIR)


fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) -rf $(MLX_LINUX_DIR)
	@echo "\033[0;31mFull clean complete.\033[0m"

re: fclean all

.PHONY: all clean fclean re mac linux
