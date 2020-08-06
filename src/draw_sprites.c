/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 11:08:52 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/08/06 12:44:20 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				res_check(char *line, int i)
{
	while (line[i] != '\0')
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ' && line[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

static void		draw_sprites(t_info *info, t_data *data, int x, double *zbuf)
{
	int y;

	y = info->spi.drsy;
	info->spi.texx = (int)(256 * (x - (-info->spi.sprw / 2 +
		info->spi.ssx)) * 64 / info->spi.sprw) / 256;
	if (info->spi.tfy > 0 && x > 0 && x < info->det.resx &&
		info->spi.tfy < zbuf[x])
		while (y < info->spi.drey)
		{
			info->spi.d = y * 256 - info->det.resy * 128 + info->spi.sprh * 128;
			info->spi.texy = ((info->spi.d * info->texsp.texh)
				/ info->spi.sprh) / 256;
			info->texsp.color = *(unsigned int*)(info->texsp.addr +
				((info->spi.texy * info->texsp.lln) + info->spi.texx *
				info->texsp.bbp / 8));
			if (info->texsp.color != 0)
				my_mlx_pixel_put(data, x, y, info->texsp.color);
			y++;
		}
}

static void		calc_sprites(t_info *info, t_data *data, double *zbuf)
{
	int x;

	info->spi.drsy = -info->spi.sprh / 2 + info->det.resy / 2;
	if (info->spi.drsy < 0)
		info->spi.drsy = 0;
	info->spi.drey = info->spi.sprh / 2 + info->det.resy / 2;
	if (info->spi.drey >= info->det.resy)
		info->spi.drey = info->det.resy - 1;
	info->spi.sprw = abs((int)(info->det.resx / (info->spi.tfy)));
	info->spi.drsx = -info->spi.sprw / 2 + info->spi.ssx;
	if (info->spi.drsx < 0)
		info->spi.drsx = 0;
	info->spi.drex = info->spi.sprw / 2 + info->spi.ssx;
	if (info->spi.drex > info->det.resx)
		info->spi.drex = info->det.resx - 1;
	info->spi.vms = (int)(0.0 / info->spi.tfy);
	x = info->spi.drsx;
	while (x < info->spi.drex)
	{
		draw_sprites(info, data, x, zbuf);
		x++;
	}
}

void			make_sprites(t_info *info, t_data *data, double *zbuf)
{
	int i;

	i = 0;
	sort_sprites(info);
	while (i < info->spi.amount)
	{
		info->spi.spx = info->sprites[i].x - info->rays.posx;
		info->spi.spy = info->sprites[i].y - info->rays.posy;
		info->spi.invdet = 1.0 / (info->rays.plx * info->rays.diry
			- info->rays.dirx * info->rays.ply);
		info->spi.tfx = info->spi.invdet * (info->rays.diry *
			info->spi.spx - info->rays.dirx * info->spi.spy);
		info->spi.tfy = info->spi.invdet * (-info->rays.ply *
			info->spi.spx + info->rays.plx * info->spi.spy);
		info->spi.ssx = (int)((info->det.resx / 2) *
			(1 + info->spi.tfx / info->spi.tfy));
		info->spi.sprh = abs((int)(info->det.resy / (info->spi.tfy)));
		calc_sprites(info, data, zbuf);
		i++;
	}
}
