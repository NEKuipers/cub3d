/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_movement.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 13:05:52 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/18 16:05:21 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	turnright(t_info *info)
{
	double olddirx;
	double oldplx;

	olddirx = info->rays.dirx;
	oldplx = info->rays.plx;
	info->rays.dirx = info->rays.dirx * cos(-info->mlx.rsp)
		- info->rays.diry * sin(-info->mlx.rsp);
	info->rays.diry = olddirx * sin(-info->mlx.rsp)
		+ info->rays.diry * cos(-info->mlx.rsp);
	info->rays.plx = info->rays.plx * cos(-info->mlx.rsp)
		- info->rays.ply * sin(-info->mlx.rsp);
	info->rays.ply = oldplx * sin(-info->mlx.rsp)
		+ info->rays.ply * cos(-info->mlx.rsp);
}

void	turnleft(t_info *info)
{
	double olddirx;
	double oldplx;

	olddirx = info->rays.dirx;
	oldplx = info->rays.plx;
	info->rays.dirx = info->rays.dirx * cos(info->mlx.rsp)
		- info->rays.diry * sin(info->mlx.rsp);
	info->rays.diry = olddirx * sin(info->mlx.rsp)
		+ info->rays.diry * cos(info->mlx.rsp);
	info->rays.plx = info->rays.plx * cos(info->mlx.rsp)
		- info->rays.ply * sin(info->mlx.rsp);
	info->rays.ply = oldplx * sin(info->mlx.rsp)
		+ info->rays.ply * cos(info->mlx.rsp);
}

void	walkfb(t_info *info, int x)
{
	if (x == 1)
	{
		if (info->grid.gmap[(int)(info->rays.posx +
			info->rays.dirx * info->mlx.msp)][(int)info->rays.posy] != '1')
			info->rays.posx += info->rays.dirx * info->mlx.msp;
		if (info->grid.gmap[(int)info->rays.posx][(int)(info->rays.posy
			+ info->rays.diry * info->mlx.msp)] != '1')
			info->rays.posy += info->rays.diry * info->mlx.msp;
	}
	if (x == 0)
	{
		if (info->grid.gmap[(int)(info->rays.posx -
			info->rays.dirx * info->mlx.msp)][(int)info->rays.posy] != '1')
			info->rays.posx -= info->rays.dirx * info->mlx.msp;
		if (info->grid.gmap[(int)info->rays.posx][(int)(info->rays.posy
			- info->rays.diry * info->mlx.msp)] != '1')
			info->rays.posy -= info->rays.diry * info->mlx.msp;
	}
}

void	walklr2(t_info *info, int x)
{
	if (x == 0)
	{
		if (info->grid.gmap[(int)(info->rays.posx +
			info->rays.dirx * info->mlx.msp)][(int)info->rays.posy] != '1')
			info->rays.posx += info->rays.diry * info->mlx.msp;
		if (info->grid.gmap[(int)info->rays.posx][(int)(info->rays.posy
			+ info->rays.diry * info->mlx.msp)] != '1')
			info->rays.posy += info->rays.dirx * info->mlx.msp;
	}
	if (x == 1)
	{
		if (info->grid.gmap[(int)(info->rays.posx -
			info->rays.dirx * info->mlx.msp)][(int)info->rays.posy] != '1')
			info->rays.posx -= info->rays.diry * info->mlx.msp;
		if (info->grid.gmap[(int)info->rays.posx][(int)(info->rays.posy
			- info->rays.diry * info->mlx.msp)] != '1')
			info->rays.posy -= info->rays.dirx * info->mlx.msp;
	}
}

void	walklr(t_info *info, int x)
{
	if (fabs(info->rays.diry) > fabs(info->rays.dirx))
	{
		if (x == 1)
		{
			if (info->grid.gmap[(int)(info->rays.posx +
				info->rays.dirx * info->mlx.msp)][(int)info->rays.posy] != '1')
				info->rays.posx += info->rays.diry * info->mlx.msp;
			if (info->grid.gmap[(int)info->rays.posx][(int)(info->rays.posy
				+ info->rays.diry * info->mlx.msp)] != '1')
				info->rays.posy += info->rays.dirx * info->mlx.msp;
		}
		if (x == 0)
		{
			if (info->grid.gmap[(int)(info->rays.posx -
				info->rays.dirx * info->mlx.msp)][(int)info->rays.posy] != '1')
				info->rays.posx -= info->rays.diry * info->mlx.msp;
			if (info->grid.gmap[(int)info->rays.posx][(int)(info->rays.posy
				- info->rays.diry * info->mlx.msp)] != '1')
				info->rays.posy -= info->rays.dirx * info->mlx.msp;
		}
	}
	else
		walklr2(info, x);
}
