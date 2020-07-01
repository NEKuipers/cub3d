/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   implement_movement.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 15:33:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/01 14:14:41 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

int		ft_keyrelease(int keycode, t_info *info)
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

int		ft_keypress(int keycode, t_info *info)
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

static void		redraw_img(t_info *info, int i)
{
	if (i == 0)
	{
		tracing(info, &info->data);
		mlx_put_image_to_window(info->mlx.mlx,
			info->mlx.win, info->data.img, 0, 0);
	}
	else if (i == 1)
	{
		tracing(info, &info->data2);
		mlx_put_image_to_window(info->mlx.mlx,
			info->mlx.win, info->data2.img, 0, 0);
	}
	info->mlx.msp = 0.075;
}

int		moving(t_info *info)
{
	if ((info->mlx.w + info->mlx.s + info->mlx.a + info->mlx.d) > 1)
		info->mlx.msp = 0.05;
	if (info->data.imgcount == 100000)
		info->data.imgcount = 0;
	if (info->mlx.l == 1)
		turn(info, 1);
	if (info->mlx.r == 1)
		turn(info, -1);
	if (info->mlx.w == 1)
		walkfb(info, 1);
	if (info->mlx.s == 1)
		walkfb(info, -1);
	if (info->mlx.a == 1)
		walklr(info, -1);
	if (info->mlx.d == 1)
		walklr(info, 1);
	if (info->data.imgcount % 2 == 0)
		redraw_img(info, 0);
	else
		redraw_img(info, 1);
	info->data.imgcount++;
	return (1);
}
