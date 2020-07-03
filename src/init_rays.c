/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 11:45:05 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/01 15:53:08 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_direction(t_info *info, char c)
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

int			set_vector(t_info *info)
{
	int x;
	int y;

	x = 0;
	while (info->grid.gmap[x])
	{
		y = 0;
		while (info->grid.gmap[x][y])
		{
			if (ft_strchr("NESW", info->grid.gmap[x][y]))
				break ;
			y++;
		}
		if (info->grid.gmap[x][y] != '\0')
			break ;
		x++;
	}
	if (!info->grid.gmap[x])
		return (errormessage("invalid map\nNo starting position :("));
	set_direction(info, info->grid.gmap[x][y]);
	info->rays.posx = x + 0.5;
	info->rays.posy = y + 0.5;
	return (0);
}
