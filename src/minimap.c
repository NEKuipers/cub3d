/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 17:10:09 by nkuipers       #+#    #+#                */
/*   Updated: 2020/03/04 15:01:12 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

static void		draw_wallblock(t_data *data2, t_info *info, int mapx, int mapy)
{
	int x;
	int y;

	x = mapx * (info->details.resx / info->grid.width) + 1;
	while (x < info->details.resx / info->grid.width *
		(mapx + 1) && x < info->details.resx)
	{
		y = mapy * (info->details.resy / info->grid.height) + 1;
		while (y < info->details.resy / info->grid.height *
			(mapy + 1) && y < info->details.resy)
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

	x = mapx * (info->details.resx / info->grid.width) + 1;
	while (x < info->details.resx / info->grid.width *
		(mapx + 1) && x < info->details.resx)
	{
		y = mapy * (info->details.resy / info->grid.height) + 1;
		while (y < info->details.resy / info->grid.height *
			(mapy + 1) && y < info->details.resy)
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

	x = info->details.resx / info->grid.width;
	while (x <= info->details.resx - (info->details.resx / info->grid.width))
	{
		y = 0;
		while (y < info->details.resy)
		{
			my_mlx_pixel_put(data2, x, y, info->details.ceilingcolor);
			y++;
		}
		x += (info->details.resx / info->grid.width);
	}
	y = info->details.resy / info->grid.height;
	while (y < info->details.resy)
	{
		x = 0;
		while (x < info->details.resx)
		{
			my_mlx_pixel_put(data2, x, y, info->details.ceilingcolor);
			x++;
		}
		y += (info->details.resy / info->grid.height);
	}
}

static void	draw_scope(t_data *data2, t_info *info)
{
	// int x;
	// int y;
	my_mlx_pixel_put(data2, info->rays.posx * info->grid.ppgx, info->rays.posy * info->grid.ppgy, 65280);
 }

void		draw_map(t_data *data2, t_info *info)
{
	draw_grid(data2, info);
	draw_walls(data2, info);
	draw_scope(data2, info);
}
