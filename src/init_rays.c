/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 11:45:05 by nkuipers       #+#    #+#                */
/*   Updated: 2020/03/04 15:15:59 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

// static void	set_direction(t_info *info, int i)
// {
// 	if (info->grid.map[i] == 'N')
// 	{
// 		info->rays.dirx = 0;
// 		info->rays.diry = -1;
// 	}
// 	if (info->grid.map[i] == 'S')
// 	{
// 		info->rays.dirx = 0;
// 		info->rays.diry = 1;
// 	}
// 	if (info->grid.map[i] == 'E')
// 	{
// 		info->rays.dirx = 1;
// 		info->rays.diry = 0;
// 	}
// 	if (info->grid.map[i] == 'W')
// 	{
// 		info->rays.dirx = -1;
// 		info->rays.diry = 0;
// 	}
// }

void		set_vector(t_info *info)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (info->grid.gmap[y])
	{
		x = 0;
		while (info->grid.gmap[y][x])
		{
			if (info->grid.gmap[y][x] == 'N' || info->grid.gmap[y][x] == 'E' ||
				info->grid.gmap[y][x] == 'W' || info->grid.gmap[y][x] == 'S')
				break ;
			x++;
		}
		if (info->grid.gmap[y][x] == 'N' || info->grid.gmap[y][x] == 'E' ||
			info->grid.gmap[y][x] == 'W' || info->grid.gmap[y][x] == 'S')
			break ;
		y++;
	}
	info->grid.ppgx = info->details.resx / info->grid.width;
	info->grid.ppgy = info->details.resy / info->grid.height;
	info->rays.posx = x + 0.5;
	info->rays.posy = y + 0.5;
	info->rays.planey = 0.66667;
}
