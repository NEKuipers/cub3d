/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:13:29 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/24 12:42:49 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_info *info)
{
	info->texno.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.nopath, &info->texno.texw, &info->texno.texh);
	info->texno.addr = mlx_get_data_addr(info->texno.tex,
		&info->texno.bbp, &info->texno.lln, &info->texno.endian);
	info->texso.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.sopath, &info->texso.texw, &info->texso.texh);
	info->texso.addr = mlx_get_data_addr(info->texso.tex,
		&info->texso.bbp, &info->texso.lln, &info->texso.endian);
	info->texwe.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.wepath, &info->texwe.texw, &info->texwe.texh);
	info->texwe.addr = mlx_get_data_addr(info->texwe.tex,
		&info->texwe.bbp, &info->texwe.lln, &info->texwe.endian);
	info->texea.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.eapath, &info->texea.texw, &info->texea.texh);
	info->texea.addr = mlx_get_data_addr(info->texea.tex,
		&info->texea.bbp, &info->texea.lln, &info->texea.endian);
	info->texsp.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.spath, &info->texsp.texw, &info->texsp.texh);
	info->texsp.addr = mlx_get_data_addr(info->texsp.tex,
		&info->texsp.bbp, &info->texsp.lln, &info->texsp.endian);
}

void	draw_wall_texture(t_info *info, t_tex *tex, t_data *data, int x)
{
	int y;

	if (info->rays.side == 0)
		tex->wallx = info->rays.posy + info->rays.pwd * info->rays.rdy;
	else
		tex->wallx = info->rays.posx + info->rays.pwd * info->rays.rdx;
	tex->wallx -= floor(tex->wallx);
	tex->texx = (int)(tex->wallx * (double)(tex->texw));
	if (info->rays.side == 0 && info->rays.rdx > 0)
		tex->texx = tex->texw - tex->texx - 1;
	if (info->rays.side == 1 && info->rays.rdy < 0)
		tex->texx = tex->texw - tex->texx - 1;
	info->rays.step = 1.0 * tex->texh / info->rays.lnh;
	tex->texpos = (info->rays.drws - info->det.resy
		/ 2 + info->rays.lnh / 2) * info->rays.step;
	y = info->rays.drws;
	while (y < info->rays.drwe)
	{
		tex->texy = (int)tex->texpos & (tex->texh - 1);
		tex->texpos += info->rays.step;
		tex->color = *(unsigned int*)(tex->addr + (tex->texy *
			tex->lln + tex->texx * (tex->bbp / 8)));
		my_mlx_pixel_put(data, x, y, tex->color);
		y++;
	}
}
