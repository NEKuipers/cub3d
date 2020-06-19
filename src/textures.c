/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:13:29 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/19 14:25:30 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

void	load_textures(t_info *info)
{
	info->texno.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.nopath, &info->texno.texw, &info->texno.texh);
	info->texno.addr = mlx_get_data_addr(info->texno.tex,
		&info->texno.bbp, &info->texno.line_len, &info->texno.endian);
	info->texso.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.sopath, &info->texso.texw, &info->texso.texh);
	info->texso.addr = mlx_get_data_addr(info->texso.tex,
		&info->texso.bbp, &info->texso.line_len, &info->texso.endian);
	info->texwe.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.wepath, &info->texwe.texw, &info->texwe.texh);
	info->texwe.addr = mlx_get_data_addr(info->texwe.tex,
		&info->texwe.bbp, &info->texwe.line_len, &info->texwe.endian);
	info->texea.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.eapath, &info->texea.texw, &info->texea.texh);
	info->texea.addr = mlx_get_data_addr(info->texea.tex,
		&info->texea.bbp, &info->texea.line_len, &info->texea.endian);
}

void	draw_north_texture(t_info *info, t_data *data, int x, int y)
{
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

void	draw_south_texture(t_info *info, t_data *data, int x, int y)
{
	if (info->rays.side == 0)
		info->texso.wallx = info->rays.posy + info->rays.pwd * info->rays.rdy;
	else
		info->texso.wallx = info->rays.posx + info->rays.pwd * info->rays.rdx;
	info->texso.wallx -= floor(info->texso.wallx);
	info->texso.texx = (int)(info->texso.wallx * (double)(info->texso.texw));
	if (info->rays.side == 0 && info->rays.rdx > 0)
		info->texso.texx = info->texso.texw - info->texso.texx - 1;
	if (info->rays.side == 1 && info->rays.rdy < 0)
		info->texso.texx = info->texso.texw - info->texso.texx - 1;
	info->rays.step = 1.0 * info->texso.texh / info->rays.lnh;
	info->texso.texpos = (info->rays.drws - info->det.resy
		/ 2 + info->rays.lnh / 2) * info->rays.step;
	y = info->rays.drws;
	while (y < info->rays.drwe)
	{
		info->texso.texy = (int)info->texso.texpos & (info->texso.texh - 1);
		info->texso.texpos += info->rays.step;
		info->texso.color = *(unsigned int*)(info->texso.addr
			+ (info->texso.texy * info->texso.line_len +
			info->texso.texx * (info->texso.bbp / 8)));
		my_mlx_pixel_put(data, x, y, info->texso.color);
		y++;
	}
}

void	draw_east_texture(t_info *info, t_data *data, int x, int y)
{
	if (info->rays.side == 0)
		info->texea.wallx = info->rays.posy + info->rays.pwd * info->rays.rdy;
	else
		info->texea.wallx = info->rays.posx + info->rays.pwd * info->rays.rdx;
	info->texea.wallx -= floor(info->texea.wallx);
	info->texea.texx = (int)(info->texea.wallx * (double)(info->texea.texw));
	if (info->rays.side == 0 && info->rays.rdx > 0)
		info->texea.texx = info->texea.texw - info->texea.texx - 1;
	if (info->rays.side == 1 && info->rays.rdy < 0)
		info->texea.texx = info->texea.texw - info->texea.texx - 1;
	info->rays.step = 1.0 * info->texea.texh / info->rays.lnh;
	info->texea.texpos = (info->rays.drws - info->det.resy
		/ 2 + info->rays.lnh / 2) * info->rays.step;
	y = info->rays.drws;
	while (y < info->rays.drwe)
	{
		info->texea.texy = (int)info->texea.texpos & (info->texea.texh - 1);
		info->texea.texpos += info->rays.step;
		info->texea.color = *(unsigned int*)(info->texea.addr
			+ (info->texea.texy * info->texea.line_len +
			info->texea.texx * (info->texea.bbp / 8)));
		my_mlx_pixel_put(data, x, y, info->texea.color);
		y++;
	}
}

void	draw_west_texture(t_info *info, t_data *data, int x, int y)
{
	if (info->rays.side == 0)
		info->texwe.wallx = info->rays.posy + info->rays.pwd * info->rays.rdy;
	else
		info->texwe.wallx = info->rays.posx + info->rays.pwd * info->rays.rdx;
	info->texwe.wallx -= floor(info->texwe.wallx);
	info->texwe.texx = (int)(info->texwe.wallx * (double)(info->texwe.texw));
	if (info->rays.side == 0 && info->rays.rdx > 0)
		info->texwe.texx = info->texwe.texw - info->texwe.texx - 1;
	if (info->rays.side == 1 && info->rays.rdy < 0)
		info->texwe.texx = info->texwe.texw - info->texwe.texx - 1;
	info->rays.step = 1.0 * info->texwe.texh / info->rays.lnh;
	info->texwe.texpos = (info->rays.drws - info->det.resy
		/ 2 + info->rays.lnh / 2) * info->rays.step;
	y = info->rays.drws;
	while (y < info->rays.drwe)
	{
		info->texwe.texy = (int)info->texwe.texpos & (info->texwe.texh - 1);
		info->texwe.texpos += info->rays.step;
		info->texwe.color = *(unsigned int*)(info->texwe.addr
			+ (info->texwe.texy * info->texwe.line_len +
			info->texwe.texx * (info->texwe.bbp / 8)));
		my_mlx_pixel_put(data, x, y, info->texwe.color);
		y++;
	}
}