/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:13:29 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/08 12:13:54 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_texture_paths(t_info *info)
{
	int fd;

	if ((fd = open(info->det.nopath, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	if ((fd = open(info->det.sopath, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	if ((fd = open(info->det.wepath, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	if ((fd = open(info->det.eapath, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	if ((fd = open(info->det.spath, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	return (0);
}

void		load_textures(t_info *info)
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

int			input_control(t_info *info)
{
	if (check_texture_paths(info) == -1)
		return (errormessage("Invalid texture path detected", info));
	check_grid(info);
	load_textures(info);
	return (0);
}

void		draw_wall_texture(t_info *info, t_tex *tex, t_data *data, int x)
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
	while (y <= info->rays.drwe)
	{
		tex->texy = (int)tex->texpos & (tex->texh - 1);
		tex->texpos += info->rays.step;
		tex->color = *(unsigned int*)(tex->addr + (tex->texy *
			tex->lln + tex->texx * (tex->bbp / 8)));
		my_mlx_pixel_put(data, x, y, tex->color);
		y++;
	}
}
