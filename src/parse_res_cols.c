/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_res_cols.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:09:27 by nkuipers       #+#    #+#                */
/*   Updated: 2020/02/06 09:59:04 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		info->details.resx = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == ' ' && ft_isdigit(line[i + 1]))
		{
			i++;
			info->details.resy = ft_atoi(&line[i]);
			return (0);
		}
	}
	return (errormessage("invalid resolution"));
}

int		parse_floor_color(const char *line, t_info *info)
{
	int	i;

	i = 2;
	if (ft_isdigit(line[i]))
	{
		info->details.floor.r = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == ',' && ft_isdigit(line[i + 1]))
		{
			i++;
			info->details.floor.g = ft_atoi(&line[i]);
			while (ft_isdigit(line[i]))
				i++;
			if (line[i] == ',' && ft_isdigit(line[i + 1]))
			{
				i++;
				info->details.floor.b = ft_atoi(&line[i]);
				info->details.floorcolor = trgb(info->details.floor.r,
					info->details.floor.g, info->details.floor.b);
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
		info->details.ceiling.r = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == ',' && ft_isdigit(line[i + 1]))
		{
			i++;
			info->details.ceiling.g = ft_atoi(&line[i]);
			while (ft_isdigit(line[i]))
				i++;
			if (line[i] == ',' && ft_isdigit(line[i + 1]))
			{
				i++;
				info->details.ceiling.b = ft_atoi(&line[i]);
				info->details.ceilingcolor = trgb(info->details.ceiling.r,
					info->details.ceiling.g, info->details.ceiling.b);
				return (0);
			}
		}
	}
	return (errormessage("invalid ceiling color"));
}
