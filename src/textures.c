/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:13:29 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/19 11:25:44 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

void	load_textures(t_info *info)
{
	info->tex.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.nopath, &info->tex.texw, &info->tex.texh);
	info->tex.addr = mlx_get_data_addr(info->tex.tex,
		&info->tex.bbp, &info->tex.line_len, &info->tex.endian);
}
