/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:50:00 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/03 17:31:39 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>
#include <stdio.h>

static void		calc_steps(t_info *info, t_data *data)
{
	if (info->rays.rdx < 0)
	{
		info->rays.step_x = -1;
		info->rays.sdx = (info->rays.posx - info->rays.mapx) * info->rays.ddx;
	}
	else
	{
		info->rays.step_x = 1;
		info->rays.sdx = (info->rays.mapx +
			1.0 - info->rays.posx) * info->rays.ddx;
	}
	if (info->rays.rdy < 0)
	{
		info->rays.step_y = -1;
		info->rays.sdy = (info->rays.posy - info->rays.mapy) * info->rays.ddy;
	}
	else
	{
		info->rays.step_y = 1;
		info->rays.sdy = (info->rays.mapy +
			1.0 - info->rays.posy) * info->rays.ddy;
	}
}

static void		find_walls(t_info *info, t_data *data)
{
	while (info->rays.hit == 0)
	{
		if (info->rays.sdx < info->rays.sdy)
		{
			info->rays.sdx += info->rays.ddx;
			info->rays.mapx += info->rays.step_x;
			info->rays.side = 0;
		}
		else
		{
			info->rays.sdy += info->rays.ddy;
			info->rays.mapy += info->rays.step_y;
			info->rays.side = 1;
		}
		if (info->grid.gmap[info->rays.mapx][info->rays.mapy] == '1')
			info->rays.hit = 1;
	}
	if (info->rays.side == 0)
		info->rays.pwd = (info->rays.mapx - info->rays.posx
			+ (1 - info->rays.step_x) / 2) / info->rays.rdx;
	else
		info->rays.pwd = (info->rays.mapy - info->rays.posy
			+ (1 - info->rays.step_y) / 2) / info->rays.rdy;
}

static void		draw_walls(t_info *info, t_data *data, int x)
{
	info->rays.lnh = (int)(info->det.resy / info->rays.pwd);
	info->rays.drws = -info->rays.lnh / 2 + info->det.resy / 2;
	if (info->rays.drws < 0)
		info->rays.drws = 0;
	info->rays.drwe = info->rays.lnh / 2 + info->det.resy / 2;
	if (info->rays.drwe >= info->det.resy)
		info->rays.drwe = info->det.resy - 1;
	if (info->rays.rdx > 0 && info->rays.side == 0)
		draw_wall_texture(info, &info->texno, data, x);
	else if (info->rays.rdy > 0 && info->rays.side == 1)
		draw_wall_texture(info, &info->texwe, data, x);
	else if (info->rays.rdy < 0 && info->rays.side == 1)
		draw_wall_texture(info, &info->texea, data, x);
	else
		draw_wall_texture(info, &info->texso, data, x);
}

void			tracing(t_info *info, t_data *data)
{
	int x;

	x = 0;
	floor_n_ceiling(data, info);
	while (x < info->det.resx)
	{
		info->rays.camerax = 2 * x / (double)info->det.resx - 1;
		info->rays.rdx = info->rays.dirx + info->rays.plx * info->rays.camerax;
		info->rays.rdy = info->rays.diry + info->rays.ply * info->rays.camerax;
		info->rays.mapx = (int)info->rays.posx;
		info->rays.mapy = (int)info->rays.posy;
		info->rays.ddx = sqrt(1 + pow(info->rays.rdy, 2)
			/ pow(info->rays.rdx, 2));
		info->rays.ddy = sqrt(1 + pow(info->rays.rdx, 2)
			/ pow(info->rays.rdy, 2));
		info->rays.hit = 0;
		calc_steps(info, data);
		find_walls(info, data);
		draw_walls(info, data, x);
		info->spi.zbuf[x] = info->rays.pwd;
		x++;
	}
	make_sprites(info, data);
}
