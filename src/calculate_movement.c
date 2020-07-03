/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_movement.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 13:05:52 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/03 14:38:40 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	turn(t_info *info, int d)
{
	double olddirx;
	double oldplx;

	olddirx = info->rays.dirx;
	oldplx = info->rays.plx;
	info->rays.dirx = info->rays.dirx * cos(d * info->mlx.rsp)
		- info->rays.diry * sin(d * info->mlx.rsp);
	info->rays.diry = olddirx * sin(d * info->mlx.rsp)
		+ info->rays.diry * cos(d * info->mlx.rsp);
	info->rays.plx = info->rays.plx * cos(d * info->mlx.rsp)
		- info->rays.ply * sin(d * info->mlx.rsp);
	info->rays.ply = oldplx * sin(d * info->mlx.rsp)
		+ info->rays.ply * cos(d * info->mlx.rsp);
}

void	walkfb(t_info *info, int d)
{
	int new_x;
	int new_y;

	new_x = info->rays.posx + d * info->rays.dirx * info->mlx.msp;
	new_y = info->rays.posy + d * info->rays.diry * info->mlx.msp;
	if (info->grid.gmap[new_x][(int)info->rays.posy] != '1' &&
		info->grid.gmap[new_x][(int)info->rays.posy] != '2')
		info->rays.posx += d * info->rays.dirx * info->mlx.msp;
	if (info->grid.gmap[(int)info->rays.posx][new_y] != '1' &&
		info->grid.gmap[(int)info->rays.posx][new_y] != '2')
		info->rays.posy += d * info->rays.diry * info->mlx.msp;
}

void	walklr(t_info *info, int d)
{
	int new_x;
	int new_y;

	new_x = info->rays.posx + d * info->rays.plx * info->mlx.msp;
	new_y = info->rays.posy + d * info->rays.ply * info->mlx.msp;
	if (info->grid.gmap[new_x][(int)info->rays.posy] != '1' &&
		info->grid.gmap[new_x][(int)info->rays.posy] != '2')
		info->rays.posx += d * info->rays.plx * info->mlx.msp;
	if (info->grid.gmap[(int)info->rays.posx][new_y] != '1' &&
		info->grid.gmap[(int)info->rays.posx][new_y] != '2')
		info->rays.posy += d * info->rays.ply * info->mlx.msp;
}
