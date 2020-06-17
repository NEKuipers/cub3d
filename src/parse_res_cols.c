/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_res_cols.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:09:27 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/12 15:53:29 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

int		trgb(int r, int g, int b)
{
	int	fc_color;

	fc_color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	if (fc_color < 0)
		fc_color *= -1;
	return (fc_color);
}

int		parse_resolution(const char *line, t_info *info)
{
	int	i;

	i = 2;
	if (ft_isdigit(line[i]))
	{
		info->det.resx = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == ' ' && ft_isdigit(line[i + 1]))
		{
			i++;
			info->det.resy = ft_atoi(&line[i]);
			return (0);
		}
	}
	mlx_get_screen_size(info->mlx.mlx, info->mlx.scresx, info->mlx.scresy);
	if (info->det.resx > *info->mlx.scresx)
		info->det.resx = *info->mlx.scresx;
	if (info->det.resy > *info->mlx.scresy)
		info->det.resy = *info->mlx.scresy;
	return (errormessage("invalid resolution"));
}

int		parse_floor_color(const char *line, t_info *info)
{
	int	i;

	i = 2;
	if (ft_isdigit(line[i]))
	{
		info->det.floor.r = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == ',' && ft_isdigit(line[i + 1]))
		{
			i++;
			info->det.floor.g = ft_atoi(&line[i]);
			while (ft_isdigit(line[i]))
				i++;
			if (line[i] == ',' && ft_isdigit(line[i + 1]))
			{
				i++;
				info->det.floor.b = ft_atoi(&line[i]);
				info->det.fcol = trgb(info->det.floor.r,
					info->det.floor.g, info->det.floor.b);
				return (0);
			}
		}
	}
	return (errormessage("invalid floor color"));
}

int		parse_ceiling_color(const char *line, t_info *info)
{
	int	i;

	i = 2;
	if (ft_isdigit(line[i]))
	{
		info->det.ceiling.r = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == ',' && ft_isdigit(line[i + 1]))
		{
			i++;
			info->det.ceiling.g = ft_atoi(&line[i]);
			while (ft_isdigit(line[i]))
				i++;
			if (line[i] == ',' && ft_isdigit(line[i + 1]))
			{
				i++;
				info->det.ceiling.b = ft_atoi(&line[i]);
				info->det.ccol = trgb(info->det.ceiling.r,
					info->det.ceiling.g, info->det.ceiling.b);
				return (0);
			}
		}
	}
	return (errormessage("invalid ceiling color"));
}
