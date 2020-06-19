/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 12:29:12 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/19 12:06:52 by nkuipers      ########   odam.nl         */
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
# include <stdbool.h>
# define K_ESC          53
# define K_W            13
# define K_S            1
# define K_A            0
# define K_D            2
# define K_LEFT         123
# define K_RIGHT        124
# define TEXWIDTH		64
# define TEXHEIGHT		64

typedef struct	s_data
{
	void		*img;
	int			imgcount;
	char		*addr;
	int			x;
	int			bpp;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_tex
{
	void		*tex;
	double		wallx;
	int			texx;
	int			texy;
	double		texpos;
	double		step;
	int			color;
	int			texw;
	int			texh;
	char		*addr;
	int			bbp;
	int			line_len;
	int			endian;
}				t_tex;

typedef struct	s_rays
{
	float		posx;
	float		posy;
	float		dirx;
	float		diry;
	double		plx;
	double		ply;
	double		time;
	double		otime;
	double		ddx;
	double		ddy;
	double		rdx;
	double		rdy;
	double		sdx;
	double		sdy;
	int			mapx;
	int			mapy;
	double		camerax;
	double		pwd;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		step;
	int			lnh;
	int			drws;
	int			drwe;
}				t_rays;

typedef	struct	s_rbg
{
	int			r;
	int			g;
	int			b;
}				t_rbg;

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

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*mlx2;
	void		*win2;
	int			*scresx;
	int			*scresy;
	double		msp;
	double		rsp;
	bool		w;
	bool		a;
	bool		s;
	bool		d;
	bool		l;
	bool		r;
}				t_mlx;

typedef struct	s_det
{
	int			resx;
	int			resy;
	char		*nopath;
	char		*sopath;
	char		*wepath;
	char		*eapath;
	char		*spath;
	t_rbg		floor;
	int			fcol;
	t_rbg		ceiling;
	int			ccol;
}				t_det;

typedef struct	s_info
{
	t_det		det;
	t_grid		grid;
	t_mlx		mlx;
	t_rays		rays;
	t_data		data;
	t_data		data2;
	t_tex		tex;
}				t_info;

int				main(int ac, char **av);

int				read_input(char **av, t_info *info);
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

void			set_vector(t_info *info);
void			mlx_start(t_info *info, char *str);
void			init_minimap(t_info *info);
int				make_map(t_info *info);
void			tracing(t_info *info, t_data *data);
void			floor_n_ceiling(t_data *data, t_info *info);

int				ft_keypress(int keycode, t_info *info);
int				ft_keyrelease(int keycode, t_info *info);
int				close_window(t_info *info);
int				moving(t_info *info);
void			turnleft(t_info *info);
void			turnright(t_info *info);
void			walkfb(t_info *info, int x);
void			walklr(t_info *info, int x);
void			walklr2(t_info *info, int x);

void			load_textures(t_info *info);

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				rgb(int r, int g, int b);
int				errormessage(char *errormsg);

#endif
