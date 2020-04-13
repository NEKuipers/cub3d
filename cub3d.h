/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 12:29:12 by nkuipers       #+#    #+#                */
/*   Updated: 2020/03/04 13:03:24 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include "lib/get_next_line/get_next_line.h"
# include "lib/libft/libft.h"
# include <mlx.h>
# define K_ESC          53
# define K_W            13
# define K_S            1
# define K_A            0
# define K_D            2
# define K_LEFT         123
# define K_RIGHT        124
# define KEY_PRESS      (1L<<0)
# define KEY_RELEASE    (1L<<1)

typedef enum	e_obj
{
	EMPTY,
	WALL,
	OBJECT,
	PLAYER_N,
	PLAYER_S,
	PLAYER_W,
	PLAYER_E
}				t_obj;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_rays
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		time;
	double		oldtime;
	double		delta_dist_x;
	double		delta_dist_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	int			mapx;
	int			mapy;
	double		camerax;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
}				t_rays;

typedef	struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_grid
{
	int			height;
	int			widthws;
	int			width;
	int			ppgx;
	int			ppgy;
	char		*map;
	char		**gmap;
}				t_grid;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	void		*mlx2;
	void		*win2;
}				t_vars;

typedef struct	s_details
{
	int			resx;
	int			resy;
	char		*nopath;
	char		*sopath;
	char		*wepath;
	char		*eapath;
	char		*spath;
	t_color		floor;
	int			floorcolor;
	t_color		ceiling;
	int			ceilingcolor;
}				t_details;

typedef struct	s_info
{
	t_details	details;
	t_grid		grid;
	t_vars		vars;
	t_rays		rays;
}				t_info;

int				parse_line(const char *line, t_info *info);
int				parse_resolution(const char *line, t_info *info);
int				parse_north_texture(const char *line, t_info *info);
int				parse_south_texture(const char *line, t_info *info);
int				parse_west_texture(const char *line, t_info *info);
int				parse_east_texture(const char *line, t_info *info);
int				parse_sprite_texture(const char *line, t_info *info);
int				parse_floor_color(const char *line, t_info *info);
int				parse_ceiling_color(const char *line, t_info *info);
int				parse_grid(const char *line, t_info *info);
void			clean_grid(t_info *info);
int				make_map(t_info *info);

void			mlx_start(t_info *info, char *str);
void			draw_map(t_data *data2, t_info *info);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

void			set_vector(t_info *info);

int				trgb(int r, int g, int b);
int				errormessage(char *errormsg);
int				read_input(char **av, t_info *info);
int				main(int ac, char **av);

#endif
