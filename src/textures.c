/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:13:29 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/08/06 15:43:35 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_texture_paths(t_info *info)
{
	int fd;

	fd = open(info->det.nopath, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open(info->det.sopath, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open(info->det.wepath, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open(info->det.eapath, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open(info->det.spath, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

static void	load_texture_addresses(t_info *info)
{
	info->texno.addr = mlx_get_data_addr(info->texno.tex,
		&info->texno.bbp, &info->texno.lln, &info->texno.endian);
	info->texso.addr = mlx_get_data_addr(info->texso.tex,
		&info->texso.bbp, &info->texso.lln, &info->texso.endian);
	info->texwe.addr = mlx_get_data_addr(info->texwe.tex,
		&info->texwe.bbp, &info->texwe.lln, &info->texwe.endian);
	info->texea.addr = mlx_get_data_addr(info->texea.tex,
		&info->texea.bbp, &info->texea.lln, &info->texea.endian);
	info->texsp.addr = mlx_get_data_addr(info->texsp.tex,
		&info->texsp.bbp, &info->texsp.lln, &info->texsp.endian);
}

int			load_textures(t_info *info)
{
	info->texno.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.nopath, &info->texno.texw, &info->texno.texh);
	info->texso.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.sopath, &info->texso.texw, &info->texso.texh);
	info->texwe.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.wepath, &info->texwe.texw, &info->texwe.texh);
	info->texea.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.eapath, &info->texea.texw, &info->texea.texh);
	info->texsp.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.spath, &info->texsp.texw, &info->texsp.texh);
	if (info->texno.tex == NULL)
		return (errormessage("Invalid north wall texture PNG entered.", info));
	if (info->texso.tex == NULL)
		return (errormessage("Invalid south wall texture PNG entered.", info));
	if (info->texwe.tex == NULL)
		return (errormessage("Invalid west wall texture PNG entered.", info));
	if (info->texea.tex == NULL)
		return (errormessage("Invalid east wall texture PNG entered.", info));
	if (info->texsp.tex == NULL)
		return (errormessage("Invalid sprite PNG entered.", info));
	load_texture_addresses(info);
	return (0);
}

int			input_control(t_info *info)
{
	if (check_texture_paths(info) == -1)
		return (errormessage("invalid texture paths.", info));
	if (info->rcf > 3)
		return (errormessage("duplicate input variable detected.", info));
	if (info->rcf < 3)
		return (errormessage("missing input variable.", info));
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
