/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 11:08:52 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/15 11:50:06 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			make_sprites(t_info *info, t_data *data)
{
	double	invdet;

	sort_sprites(info, info->sprites);
	for(int i = 0; i < info->spi.amount; i++)
	{
		info->spi.spx = info->sprites[i].x - info->rays.posx;
		info->spi.spy = info->sprites[i].y - info->rays.posy;
		invdet = 1.0 / (info->rays.plx * info->rays.diry - info->rays.dirx * info->rays.ply);
		info->spi.tfx = invdet * (info->rays.diry * info->spi.spx - info->rays.dirx * info->spi.spy);
		info->spi.tfy = invdet * (-info->rays.ply * info->spi.spx + info->rays.plx * info->spi.spy);
		info->spi.ssx = (int)((info->det.resx / 2) * (1 + info->spi.tfx / info->spi.tfy));
		info->spi.sprh = abs((int)(info->det.resy / (info->spi.tfy)));
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
		for(int x = info->spi.drsx; x < info->spi.drex; x++)
		{
			info->spi.texx = (int)(256 * (x - (-info->spi.sprw / 2 + info->spi.ssx)) * 64 / info->spi.sprw) / 256;
			if (info->spi.tfy > 0 && x > 0 && x < info->det.resx && info->spi.tfy < info->spi.zbuf[x])
			{
				for(int y = info->spi.drsy; y < info->spi.drey; y++)
				{
					info->spi.d = y * 256 - info->det.resy * 128 + info->spi.sprh * 128;
					info->spi.texy = ((info->spi.d * info->texsp.texh) / info->spi.sprh) / 256;
					info->texsp.color = *(unsigned int*)(info->texsp.addr + ((info->spi.texy * info->texsp.lln) + info->spi.texx * info->texsp.bbp / 8));
					if (info->texsp.color != 0)
					 	my_mlx_pixel_put(data, x, y, info->texsp.color);
				}
			}
		}
	}
}
