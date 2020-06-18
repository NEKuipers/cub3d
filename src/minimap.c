/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 17:10:09 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/18 13:29:15 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

static void		draw_wallblock(t_data *data2, t_info *info, int mapx, int mapy)
{
	int x;
	int y;

	x = mapx * (info->det.resx / 2 / info->grid.width) + 1;
	while (x < info->det.resx / 2 / info->grid.width *
		(mapx + 1) && x < info->det.resx / 2)
	{
		y = mapy * (info->det.resy / 2 / info->grid.height) + 1;
		while (y < info->det.resy / 2 / info->grid.height *
			(mapy + 1) && y < info->det.resy / 2)
		{
			my_mlx_pixel_put(data2, x, y, 11529966);
			y++;
		}
		x++;
	}
}

static void		draw_objblock(t_data *data2, t_info *info, int mapx, int mapy)
{
	int x;
	int y;

	x = mapx * (info->det.resx / 2 / info->grid.width) + 1;
	while (x < info->det.resx / 2 / info->grid.width *
		(mapx + 1) && x < info->det.resx / 2)
	{
		y = mapy * (info->det.resy / 2 / info->grid.height) + 1;
		while (y < info->det.resy / 2 / info->grid.height *
			(mapy + 1) && y < info->det.resy / 2)
		{
			my_mlx_pixel_put(data2, x, y, 16776960);
			y++;
		}
		x++;
	}
}

static void		draw_walls(t_data *data2, t_info *info)
{
	int mapx;
	int mapy;

	mapy = 0;
	while (mapy < info->grid.height)
	{
		mapx = 0;
		while (mapx < info->grid.width)
		{
			if (info->grid.gmap[mapy][mapx] == '1')
				draw_wallblock(data2, info, mapx, mapy);
			else if (info->grid.gmap[mapy][mapx] == '2')
				draw_objblock(data2, info, mapx, mapy);
			mapx++;
		}
		mapy++;
	}
}

static void		draw_grid(t_data *data2, t_info *info)
{
	int x;
	int y;

	x = info->det.resx / 2 / info->grid.width;
	while (x <= info->det.resx / 2 - (info->det.resx / 2 / info->grid.width))
	{
		y = 0;
		while (y < info->det.resy / 2)
		{
			my_mlx_pixel_put(data2, x, y, info->det.ccol);
			y++;
		}
		x += (info->det.resx / 2 / info->grid.width);
	}
	y = info->det.resy / 2 / info->grid.height;
	while (y < info->det.resy / 2)
	{
		x = 0;
		while (x < info->det.resx / 2)
		{
			my_mlx_pixel_put(data2, x, y, info->det.ccol);
			x++;
		}
		y += (info->det.resy / 2 / info->grid.height);
	}
}

static void	draw_scope(t_data *data2, t_info *info)
{
	int x;
	int y;

	my_mlx_pixel_put(data2, info->rays.posx * info->grid.ppgx / 2,
		info->rays.posy * info->grid.ppgy / 2, 65280);
}

void	init_minimap(t_info *info)
{
	t_data	data2;

	info->mlx.mlx2 = mlx_init();
	info->mlx.win2 = mlx_new_window(info->mlx.mlx2, info->det.resx / 2,
		info->det.resy / 2, "2D");
	data2.img = mlx_new_image(info->mlx.mlx2,
		info->det.resx / 2, info->det.resy / 2);
	data2.addr = mlx_get_data_addr(data2.img, &data2.bpp,
		&data2.line_length, &data2.endian);
	draw_grid(&data2, info);
	draw_walls(&data2, info);
	draw_scope(&data2, info);
	mlx_put_image_to_window(info->mlx.mlx2, info->mlx.win2, data2.img, 0, 0);
}
