/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:37:30 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/16 13:54:18 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	floor_n_ceiling(t_data *data, t_info *info)
{
	int x;
	int y;

	x = 0;
	while (x <= info->det.resx)
	{
		y = 0;
		while (y <= info->det.resy / 2)
		{
			my_mlx_pixel_put(data, x, y, info->det.ceil.col);
			y++;
		}
		x++;
	}
	x = 0;
	while (x <= info->det.resx)
	{
		y = info->det.resy / 2;
		while (y < info->det.resy)
		{
			my_mlx_pixel_put(data, x, y, info->det.floor.col);
			y++;
		}
		x++;
	}
}

int		close_window(t_info *info)
{
	mlx_destroy_image(info->mlx.mlx, info->data.img);
	mlx_destroy_image(info->mlx.mlx, info->data2.img);
	mlx_destroy_window(info->mlx.mlx, info->mlx.win);
	free_struct(info);
	exit(1);
	return (0);
}

void	mlx_loop_station(t_info *info)
{
	mlx_hook(info->mlx.win, 2, 1L << 0, &ft_keypress, info);
	mlx_hook(info->mlx.win, 3, 1L << 1, &ft_keyrelease, info);
	mlx_hook(info->mlx.win, 17, 1L << 17, &close_window, info);
	mlx_loop_hook(info->mlx.mlx, moving, info);
	mlx_loop(info->mlx.mlx);
}

void	mlx_start(t_info *info)
{
	ft_screenshot(info);
	info->mlx.mlx = mlx_init();
	set_vector(info);
	input_control(info);
	info->sprites = ft_calloc(info->spi.amount, sizeof(t_spr));
	if (info->sprites == NULL)
		errormessage("malloc error", info);
	ft_bzero(info->sprites, sizeof(t_spr));
	find_sprites(info);
	info->mlx.win = mlx_new_window(info->mlx.mlx, info->det.resx,
		info->det.resy, "CUB3D");
	info->data.img = mlx_new_image(info->mlx.mlx,
		info->det.resx, info->det.resy);
	info->data2.img = mlx_new_image(info->mlx.mlx,
		info->det.resx, info->det.resy);
	info->data.addr = mlx_get_data_addr(info->data.img, &info->data.bpp,
		&info->data.line_length, &info->data.endian);
	info->data2.addr = mlx_get_data_addr(info->data2.img, &info->data2.bpp,
		&info->data2.line_length, &info->data2.endian);
	tracing(info, &info->data);
	mlx_put_image_to_window(info->mlx.mlx, info->mlx.win, info->data.img, 0, 0);
	info->mlx.rsp = 0.05;
	info->mlx.msp = 0.1;
	mlx_loop_station(info);
}
