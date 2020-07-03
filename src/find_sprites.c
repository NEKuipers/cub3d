/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 14:45:28 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/03 15:33:39 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		bubble_sort(t_info *info, t_spr *sprites)
{
	int		i;
	t_spr	temp;

	i = 0;
	while (i < info->spi.amount)
	{
		if (sprites[i].dist < sprites[i + 1].dist)
		{
			temp = sprites[i];
			sprites[i] = sprites[i + 1];
			sprites[i + 1] = temp;
		}
		i++;
	}
}

static void		sort_sprites(t_info *info, t_spr *sprites)
{
	int		i;

	i = 0;
	while (i < info->spi.amount)
	{
		// info->spi.order[i] = i;
		sprites[i].dist = ((info->rays.posx - sprites[i].x) * (info->rays.posx -
			sprites[i].x) + (info->rays.posy - sprites[i].y) *
			(info->rays.posy - sprites[i].y));
		i++;
	}
	i = 0;
	while (i < info->spi.amount)
	{
		if (sprites[i].dist < sprites[i + 1].dist)
		{
			bubble_sort(info, sprites);
			i = 0;
		}
		else
			i++;
	}
}

static int		check_double_sprites(t_spr *sprites, int x, int y, int a)
{
	int 	i;

	i = 0;
	while (i <= a)
	{
		if (sprites[i].x == x && sprites[i].y == y)
			return (0);
		i++;
	}
	return (1);
}

static void		find_sprites_2(t_info *info, t_spr *sprites, int i)
{
	int 	x;
	int 	y;

	y = 0;
	while (info->grid.gmap[y])
	{
		x = 0;
		while (info->grid.gmap[y][x])
		{
			if (info->grid.gmap[y][x] == '2')
			{
				if (check_double_sprites(sprites, x, y, info->spi.amount))
				{
					sprites[i].y = y + 0.5;
					sprites[i].x = x + 0.5;
					return ;
				}
			}
			x++;
		}
		y++;
	}
}

void			find_sprites(t_info *info, t_spr *sprites)
{
	int		i;

	i = 0;
	while (i < info->spi.amount)
	{
		find_sprites_2(info, sprites, i);
		i++;
	}
	sort_sprites(info, sprites);
}
