/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:37:30 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/17 14:07:51 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdint.h>
#include <stdio.h>

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void		floor_n_ceiling(t_data *data, t_info *info)
{
	int x;
	int y;

	x = 0;
	while (x <= info->det.resx)
	{
		y = 0;
		while (y <= info->det.resy / 2)
		{
			my_mlx_pixel_put(data, x, y, info->det.fcol);
			y++;
		}
		x++;
	}
	x = 0;
	while (x <= info->det.resx)
	{
		y = info->det.resy / 2;
		while (y <= info->det.resy)
		{
			my_mlx_pixel_put(data, x, y, info->det.ccol);
			y++;
		}
		x++;
	}
}

int		close_window(t_info *info)
{
	mlx_destroy_image(info->mlx.mlx, info->data.img);
	mlx_destroy_image(info->mlx.mlx, info->data2.img);
	mlx_destroy_window(info->mlx.mlx, info->mlx.win);
	exit(1);
	return (0);
}

void			mlx_start(t_info *info, char *str)
{
	t_data	data2;

	info->mlx.mlx = mlx_init();
	info->mlx.mlx2 = mlx_init();
	info->mlx.win = mlx_new_window(info->mlx.mlx, info->det.resx,
		info->det.resy, "3D");
	info->mlx.win2 = mlx_new_window(info->mlx.mlx2, info->det.resx,
		info->det.resy, "2D");
	info->data.img = mlx_new_image(info->mlx.mlx,
		info->det.resx, info->det.resy);
	info->data2.img = mlx_new_image(info->mlx.mlx,
		info->det.resx, info->det.resy);
	data2.img = mlx_new_image(info->mlx.mlx2,
		info->det.resx, info->det.resy);
	info->data.addr = mlx_get_data_addr(info->data.img, &info->data.bpp,
		&info->data.line_length, &info->data.endian);
	info->data2.addr = mlx_get_data_addr(info->data2.img, &info->data2.bpp,
		&info->data2.line_length, &info->data2.endian);
	data2.addr = mlx_get_data_addr(data2.img, &data2.bpp,
		&data2.line_length, &data2.endian);
	floor_n_ceiling(&info->data, info);
	set_vector(info);
	draw_map(&data2, info);
	tracing(info, &info->data);
	mlx_put_image_to_window(info->mlx.mlx, info->mlx.win, info->data.img, 0, 0);
	mlx_put_image_to_window(info->mlx.mlx2, info->mlx.win2, data2.img, 0, 0);
	info->mlx.rsp = 0.03;
	info->mlx.msp = 0.075;
	mlx_hook(info->mlx.win, 2, 1L << 0, &ft_keypress, info);
	mlx_hook(info->mlx.win, 3, 1L << 1, &ft_keyrelease, info);
	mlx_hook(info->mlx.win, 17, 1L << 17, &close_window, info);
	mlx_loop_hook(info->mlx.mlx, moving, info);
	mlx_loop(info->mlx.mlx);
}
