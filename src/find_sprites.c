/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 14:45:28 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/16 13:24:40 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		bubble_sort(t_info *info)
{
	int		i;
	t_spr	temp;

	i = 0;
	while (i < info->spi.amount - 1)
	{
		if (info->sprites[i].dist < info->sprites[i + 1].dist)
		{
			temp = info->sprites[i];
			info->sprites[i] = info->sprites[i + 1];
			info->sprites[i + 1] = temp;
		}
		i++;
	}
}

void			sort_sprites(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->spi.amount)
	{
		info->sprites[i].dist = ((info->rays.posx - info->sprites[i].x) *
			(info->rays.posx - info->sprites[i].x) + (info->rays.posy -
			info->sprites[i].y) * (info->rays.posy - info->sprites[i].y));
		i++;
	}
	i = 0;
	while (i < info->spi.amount - 1)
	{
		if (info->sprites[i].dist < info->sprites[i + 1].dist)
		{
			bubble_sort(info);
			i = 0;
		}
		else
			i++;
	}
}

static int		check_double_sprites(t_info *info, int x, int y)
{
	int		i;

	i = 0;
	while (i < info->spi.amount)
	{
		if (info->sprites[i].x == x + 0.5 && info->sprites[i].y == y + 0.5)
			return (0);
		i++;
	}
	return (1);
}

static void		find_sprite(t_info *info, int i)
{
	int		x;
	int		y;

	x = 0;
	while (info->grid.gmap[x])
	{
		y = 0;
		while (info->grid.gmap[x][y])
		{
			if (info->grid.gmap[x][y] == '2')
				if (check_double_sprites(info, x, y) == 1)
				{
					info->sprites[i].y = y + 0.5;
					info->sprites[i].x = x + 0.5;
					return ;
				}
			y++;
		}
		x++;
	}
}

void			find_sprites(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->spi.amount)
	{
		find_sprite(info, i);
		i++;
	}
}
