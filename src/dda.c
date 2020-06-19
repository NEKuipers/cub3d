/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:50:00 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/19 13:41:33 by nkuipers      ########   odam.nl         */
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
	int y;

	info->rays.lnh = (int)(info->det.resy / info->rays.pwd);
	info->rays.drws = -info->rays.lnh / 2 + info->det.resy / 2;
	if (info->rays.drws < 0)
		info->rays.drws = 0;
	info->rays.drwe = info->rays.lnh / 2 + info->det.resy / 2;
	if (info->rays.drwe >= info->det.resy)
		info->rays.drwe = info->det.resy - 1;
	if (info->rays.side == 0)
		info->texno.wallx = info->rays.posy + info->rays.pwd * info->rays.rdy;
	else
		info->texno.wallx = info->rays.posx + info->rays.pwd * info->rays.rdx;
	info->texno.wallx -= floor(info->texno.wallx);
	info->texno.texx = (int)(info->texno.wallx * (double)(info->texno.texw));
	if (info->rays.side == 0 && info->rays.rdx > 0)
		info->texno.texx = info->texno.texw - info->texno.texx - 1;
	if (info->rays.side == 1 && info->rays.rdy < 0)
		info->texno.texx = info->texno.texw - info->texno.texx - 1;
	info->rays.step = 1.0 * info->texno.texh / info->rays.lnh;
	info->texno.texpos = (info->rays.drws - info->det.resy
		/ 2 + info->rays.lnh / 2) * info->rays.step;
	y = info->rays.drws;
	while (y < info->rays.drwe)
	{
		info->texno.texy = (int)info->texno.texpos & (info->texno.texh - 1);
		info->texno.texpos += info->rays.step;
		info->texno.color = *(unsigned int*)(info->texno.addr
			+ (info->texno.texy * info->texno.line_len +
			info->texno.texx * (info->texno.bbp / 8)));
		my_mlx_pixel_put(data, x, y, info->texno.color);
		y++;
	}
}

void			tracing(t_info *info, t_data *data)
{
	int x;

	x = 0;
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
		x++;
	}
}
