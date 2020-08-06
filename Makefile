# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nkuipers <nkuipers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/22 14:25:44 by nkuipers      #+#    #+#                  #
#    Updated: 2020/08/06 15:46:49 by nkuipers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME            =   cub3D
SRCS            =   start.c \
					parse_grid.c \
					parse_details.c \
					mlx_start.c \
					init_rays.c \
					dda.c \
					implement_movement.c \
					calculate_movement.c \
					draw_sprites.c \
					find_sprites.c \
					screenshot.c \
					textures.c \
					utils.c \
					utils_2.c \
					../lib/get_next_line/get_next_line.c
CFILES          =   $(SRCS:%=src/%)
OFILES          =   $(CFILES:.c=.o)
CFLAGS          =   -Wall -Wextra -Werror
INCLUDES        =   -I include\
                    -I lib/mlx\
                    -I lib/libft\
					-I lib/get_next_line
LIBS            =   -L lib/mlx -lmlx\
                    -L lib/libft -lft\
# LIB LOCATIONS
MLX_LOC			= 	lib/mlx
LIBFT_LOC       =   lib/libft
# COLORS
WHITE   = \x1b[37;01m
CYAN    = \x1b[36;01m
PINK    = \x1b[35;01m
BLUE    = \x1b[34;01m
YELLOW  = \x1b[33;01m
GREEN   = \x1b[32;01m
RED     = \x1b[31;01m
BLACK   = \x1b[30;01m
RESET   = \x1b[0m

all: $(NAME)

$(NAME): $(OFILES)
	@echo "$(WHITE)/-----      Compiling mlx -----\\ $(RESET)"
	@make -C $(MLX_LOC)
	@cp lib/mlx/libmlx.dylib .
	@echo "$(WHITE)/-----      Compiling libft     -----\\ $(RESET)"
	make bonus -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Compiling cub3d    -----\\ $(RESET)"
	@gcc $(CFLAGS) $(INCLUDES) $(OFILES) $(LIBS) $(EXT_LIBS) -o $(NAME)
	@echo "$(GREEN) cub3D is ready to go! $(RESET)"

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@ -g

clean:
	@echo "$(WHITE)/-----      Cleaning mlx        -----\\ $(RESET)"
	@make clean -C $(MLX_LOC)
	@echo "$(WHITE)/-----      Cleaning libft      -----\\ $(RESET)"
	@make clean -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Cleaning cub3d     -----\\ $(RESET)"
	@rm -f $(OFILES)

fclean: clean
	@echo "$(WHITE)/-----      Fcleaning libft     -----\\ $(RESET)"
	@make fclean -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Fcleaning cub3d    -----\\ $(RESET)"
	@rm -f $(NAME) libmlx.dylib

re: fclean all

.PHONY: all clean fclean re
