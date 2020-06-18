/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_res_cols.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:09:27 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/18 13:19:13 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	if (info->det.resx > 2560)
		info->det.resx = 2560;
	if (info->det.resy > 1400)
		info->det.resy = 1400;
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
				info->det.fcol = rgb(info->det.floor.r,
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
				info->det.ccol = rgb(info->det.ceiling.r,
					info->det.ceiling.g, info->det.ceiling.b);
				return (0);
			}
		}
	}
	return (errormessage("invalid ceiling color"));
}
