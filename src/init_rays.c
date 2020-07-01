/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 11:45:05 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/01 14:26:26 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

static void		set_direction(t_info *info, char c)
{
	if (c == 'N')
	{
		info->rays.dirx = -1;
		info->rays.ply = 0.66667;
	}
	if (c == 'S')
	{
		info->rays.dirx = 1;
		info->rays.ply = -0.66667;
	}
	if (c == 'E')
	{
		info->rays.diry = 1;
		info->rays.plx = 0.66667;
	}
	if (c == 'W')
	{
		info->rays.diry = -1;
		info->rays.plx = -0.66667;
	}
}

void			set_vector(t_info *info)
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
			if (ft_strchr("NESW", info->grid.gmap[y][x]))
				break ;
			x++;
		}
		if (info->grid.gmap[y][x] == 'N' || info->grid.gmap[y][x] == 'E' ||
			info->grid.gmap[y][x] == 'W' || info->grid.gmap[y][x] == 'S')
			break ;
		y++;
	}
	printf("y is %i, x is %i", y, x);
	set_direction(info, info->grid.gmap[y][x]);
	info->rays.posx = y + 0.5;
	info->rays.posy = x + 0.5;
}
