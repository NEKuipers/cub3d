/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 15:33:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/17 14:07:16 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

void		turnright(t_info *info)
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

void		turnleft(t_info *info)
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

static void		walkfb(t_info *info, int x)
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

static void		walklr2(t_info *info, int x)
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

static void		walklr(t_info *info, int x)
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

int			ft_keyrelease(int keycode, t_info *info)
{
	if (keycode == K_LEFT)
		info->mlx.l = 0;
	if (keycode == K_RIGHT)
		info->mlx.r = 0;
	if (keycode == K_A)
		info->mlx.a = 0;
	if (keycode == K_W || keycode == 126)
		info->mlx.w = 0;
	if (keycode == K_S || keycode == 125)
		info->mlx.s = 0;
	if (keycode == K_D)
		info->mlx.d = 0;
	return (0);
}

int			ft_keypress(int keycode, t_info *info)
{
	if (keycode == K_LEFT)
		info->mlx.l = 1;
	if (keycode == K_RIGHT)
		info->mlx.r = 1;
	if (keycode == K_A)
		info->mlx.a = 1;
	if (keycode == K_W)
		info->mlx.w = 1;
	if (keycode == K_S)
		info->mlx.s = 1;
	if (keycode == K_D)
		info->mlx.d = 1;
	if (keycode == K_ESC)
		close_window(info);
	return (0);
}

int			moving(t_info *info)
{
	if (info->data.imgcount == 100000)
		info->data.imgcount = 0;
	if (info->mlx.l == 1)
		turnleft(info);
	if (info->mlx.r == 1)
		turnright(info);
	if (info->mlx.w == 1)
		walkfb(info, 1);
	if (info->mlx.s == 1)
		walkfb(info, 0);
	if (info->mlx.a == 1)
		walklr(info, 0);
	if (info->mlx.d == 1)
		walklr(info, 1);
	if (info->data.imgcount % 2 == 0)
	{
		floor_n_ceiling(&info->data, info);
		tracing(info, &info->data);
		mlx_put_image_to_window(info->mlx.mlx, info->mlx.win, info->data.img, 0, 0);
		// mlx_destroy_image(info->mlx.mlx, info->data2.img);
	}
	else
	{
		floor_n_ceiling(&info->data2, info);
		tracing(info, &info->data2);
		mlx_put_image_to_window(info->mlx.mlx, info->mlx.win, info->data2.img, 0, 0);
		// mlx_destroy_image(info->mlx.mlx, info->data.img);
	}
	info->data.imgcount++;
	return (1);
}
