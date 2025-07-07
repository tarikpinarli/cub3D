# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 13:16:45 by tpinarli          #+#    #+#              #
#    Updated: 2025/07/07 16:01:33 by michoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3D
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
RM			= rm -rf

SRC_DIR 	= ./src
OBJ_DIR 	= ./obj
INC_DIR 	= ./include
LIB_DIR 	= ./lib
MAP_DIR     = ./maps

LIBFT_DIR 	= $(LIB_DIR)/libft
LIBFT 		= $(LIBFT_DIR)/libft.a

MLX_DIR 	= $(LIB_DIR)/minilibx-linux
MLX_LIB 	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_INC 	= -I$(MLX_DIR)
MLX			= $(MLX_DIR)/libmlx.a

INCLUDES 	= -I$(INC_DIR) -I$(LIBFT_DIR) $(MLX_INC)

SRCS = main.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)
	@echo "\033[0;32m✔ Build complete!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Clone and build MiniLibX if not already
$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MiniLibX..."; \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; fi
	@echo "\033[0;31mCleaned object files.\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(MLX_DIR)
	@echo "\033[0;31mCleaned everything.\033[0m"

re: fclean all

.PHONY: all clean fclean re
