/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:37:30 by nkuipers       #+#    #+#                */
/*   Updated: 2020/03/04 15:47:23 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdint.h>

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void		create_shapes(t_data *data, t_info *info)
{
	int x;
	int y;

	x = 0;
	while (x <= info->details.resx)
	{
		y = 0;
		while (y <= info->details.resy * 2 / 9)
		{
			my_mlx_pixel_put(data, x, y, info->details.ceilingcolor);
			y++;
		}
		x++;
	}
	x = 0;
	while (x <= info->details.resx)
	{
		y = info->details.resy * 7 / 9;
		while (y <= info->details.resy)
		{
			my_mlx_pixel_put(data, x, y, info->details.floorcolor);
			y++;
		}
		x++;
	}
}

static int		ft_keys(int keycode, t_vars *vars)
{
	if (keycode == K_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

// static void			tracing(t_info *info, t_data *data)
// {
// 	for(int x = 0; x < info->details.resx; x++)
//     {
//       //calculate ray position and direction
//     	info->rays.camerax = 2 * x / (double)info->details.resx - 1; //x-coordinate in camera space
//      	info->rays.ray_dir_x = info->rays.dirx + info->rays.planex * info->rays.camerax;
//     	info->rays.ray_dir_y = info->rays.diry + info->rays.planey * info->rays.camerax;
//       //which box of the map we're in
//     	info->rays.mapx = (int)info->rays.posx;
//     	info->rays.mapy = (int)info->rays.posy;
//        //length of ray from one x or y-side to next x or y-side
//     	info->rays.delta_dist_x = sqrt(1 + pow(info->rays.ray_dir_y, 2) / pow(info->rays.ray_dir_x, 2));
//     	info->rays.delta_dist_y = sqrt(1 + pow(info->rays.ray_dir_x, 2) / pow(info->rays.ray_dir_y, 2));

//       //calculate step and initial sideDist
//     	if(info->rays.ray_dir_x < 0)
//      	{
//         	info->rays.step_x = -1;
//        	 info->rays.side_dist_x = (info->rays.posx - info->rays.mapx) * info->rays.delta_dist_x;
//     	}
//     	else
//     	{
//     		info->rays.step_x = 1;
//     		info->rays.side_dist_x = (info->rays.mapx + 1.0 - info->rays.posx) * info->rays.delta_dist_x;
// 		}
//     	if(info->rays.ray_dir_y < 0)
//     	{
//     		info->rays.step_y = -1;
//     		info->rays.side_dist_y = (info->rays.posy - info->rays.mapy) * info->rays.delta_dist_y;
//     	}
//     	else
//     	{
//     	info->rays.step_y = 1;
//         info->rays.side_dist_y = (info->rays.mapy + 1.0 - info->rays.posy) * info->rays.delta_dist_y;
//       	}
//       //perform DDA
//       	while (info->rays.hit == 0)
//     	{
//         //jump to next map square, OR in x-direction, OR in y-direction
//     		if(info->rays.side_dist_x < info->rays.side_dist_y)
//         	{
//         		info->rays.side_dist_x += info->rays.delta_dist_x;
//         		info->rays.mapx += info->rays.step_x;
//         		info->rays.side = 0;
//         	}
//         	else
//         	{
//         		info->rays.side_dist_y += info->rays.delta_dist_y;
//         		info->rays.mapy += info->rays.step_y;
//         		info->rays.side = 1;
//     		}
//         //Check if ray has hit a wall
//     		if(info->grid.gmap[info->rays.mapx][info->rays.mapy] > 0) info->rays.hit = 1;
//     	}
// 		if (info->rays.side == 0)
// 			info->rays.perp_wall_dist = (info->rays.mapx - info->rays.posx + (1 - info->rays.step_x) / 2) / info->rays.ray_dir_x;
//     	else
// 			info->rays.perp_wall_dist = (info->rays.mapy - info->rays.posy + (1 - info->rays.step_y) / 2) / info->rays.ray_dir_y;
// 		info->rays.lineheight = (int)(info->details.resy / info->rays.perp_wall_dist);
// 		info->rays.drawstart = -info->rays.lineheight / (2 + info->details.resy) / 2;
// 		if (info->rays.drawstart)
// 			info->rays.drawstart = 0;
// 		info->rays.drawend = info->rays.lineheight / (2 + info->details.resy) / 2;
// 		if (info->rays.drawend >= info->details.resy)
// 			info->rays.drawend = info->details.resy - 1;
// 		my_mlx_pixel_put(data, info->rays.drawstart, info->rays.drawend, info->details.ceilingcolor);
// 	}
// }

void			mlx_start(t_info *info, char *str)
{
	t_data	data;
	t_data	data2;

	info->vars.mlx = mlx_init();
	info->vars.mlx2 = mlx_init();
	info->vars.win = mlx_new_window(info->vars.mlx, info->details.resx,
		info->details.resy, "3D");
	info->vars.win2 = mlx_new_window(info->vars.mlx2, info->details.resx,
		info->details.resy, "2D");
	data.img = mlx_new_image(info->vars.mlx,
		info->details.resx, info->details.resy);
	data2.img = mlx_new_image(info->vars.mlx2,
		info->details.resx, info->details.resy);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
		&data.line_length, &data.endian);
	data2.addr = mlx_get_data_addr(data2.img, &data2.bits_per_pixel,
		&data2.line_length, &data2.endian);
	create_shapes(&data, info);
	set_vector(info);
	draw_map(&data2, info);
	// // tracing(info, &data);
	mlx_put_image_to_window(info->vars.mlx, info->vars.win, data.img, 0, 0);
	mlx_put_image_to_window(info->vars.mlx2, info->vars.win2, data2.img, 0, 0);
	mlx_key_hook(info->vars.win, ft_keys, &info->vars);
	mlx_loop(info->vars.mlx);
}
