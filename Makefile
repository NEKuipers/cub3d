# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nkuipers <nkuipers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/22 14:25:44 by nkuipers       #+#    #+#                 #
#    Updated: 2020/03/04 15:09:16 by nkuipers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME            =   cub3d
SRCS            =   start.c \
					parse_grid.c \
					parse_res_cols.c \
					parse_textures.c \
					mlx_start.c \
					init_rays.c \
					minimap.c \
					../lib/get_next_line/get_next_line.c \
					../lib/get_next_line/get_next_line_utils.c
CFILES          =   $(SRCS:%=src/%)
OFILES          =   $(CFILES:.c=.o)
CFLAGS          =   -Wall -Wextra -Werror -fPIC -DNOLIST -Wno-unused-parameter -Wno-unused-variable
INCLUDES        =   -Iminilibx-master\
                    -Ilib/libft\
                    -Ilib/liblist\
					-Ilib/get_next_line
EXT_LIBS        =   lib/libft/libft.a\
                    lib/liblist/liblist.a\
					minilibx-master/libmlx.a
LIBS 			= 	-lXext -lX11 -lm -lz -AppKit
# LIB LOCATIONS
MLX_LOC			= 	minilibx-master
LIBFT_LOC       =   lib/libft
LIBLIST_LOC     =   lib/liblist
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
	@echo "$(WHITE)/-----      Compiling libft     -----\\ $(RESET)"
	make bonus -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Compiling liblist   -----\\ $(RESET)"
	make -C $(LIBLIST_LOC)
	@echo "$(WHITE)/-----      Compiling cub3d    -----\\ $(RESET)"
	gcc $(CFLAGS) $(INCLUDES) $(OFILES) $(LIBS) $(EXT_LIBS) -o $(NAME)

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@ -g
	gcc -fPIC -I/usr/include -Iminilibx-master -O3 -c $< -o $@

clean:
	@echo "$(WHITE)/-----      Cleaning mlx        -----\\ $(RESET)"
	make clean -C $(MLX_LOC)
	@echo "$(WHITE)/-----      Cleaning libft      -----\\ $(RESET)"
	make clean -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Cleaning liblist    -----\\ $(RESET)"
	make clean -C $(LIBLIST_LOC)
	@echo "$(WHITE)/-----      Cleaning cub3d     -----\\ $(RESET)"
	rm -f $(OFILES)

fclean: clean
	@echo "$(WHITE)/-----      Fcleaning libft     -----\\ $(RESET)"
	make fclean -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Fcleaning liblist   -----\\ $(RESET)"
	make fclean -C $(LIBLIST_LOC)
	@echo "$(WHITE)/-----      Fcleaning cub3d    -----\\ $(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
