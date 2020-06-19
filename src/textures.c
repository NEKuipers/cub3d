/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:13:29 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/19 13:34:24 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

void	load_textures(t_info *info)
{
	info->texno.tex = mlx_png_file_to_image(info->mlx.mlx,
		info->det.nopath, &info->texno.texw, &info->texno.texh);
	info->texno.addr = mlx_get_data_addr(info->texno.tex,
		&info->texno.bbp, &info->texno.line_len, &info->texno.endian);
	// ft_bzero(&info->texso, sizeof(t_tex));
	// printf("%s\n%s\n%s\n%s\n", info->det.nopath, info->det.sopath, info->det.wepath, info->det.eapath);
	// info->texso.tex = mlx_png_file_to_image(info->mlx.mlx,
	// 	info->det.sopath, &info->texso.texw, &info->texso.texh);
	// info->texso.addr = mlx_get_data_addr(info->texso.tex,
	// 	&info->texso.bbp, &info->texso.line_len, &info->texso.endian);
	// info->texwe.tex = mlx_png_file_to_image(info->mlx.mlx,
	// 	info->det.wepath, &info->texwe.texw, &info->texwe.texh);
	// info->texwe.addr = mlx_get_data_addr(info->texwe.tex,
	// 	&info->texwe.bbp, &info->texwe.line_len, &info->texwe.endian);
	// info->texea.tex = mlx_png_file_to_image(info->mlx.mlx,
	// 	info->det.eapath, &info->texea.texw, &info->texea.texh);
	// info->texea.addr = mlx_get_data_addr(info->texea.tex,
	// 	&info->texea.bbp, &info->texea.line_len, &info->texea.endian);
}
