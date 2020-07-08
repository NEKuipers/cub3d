/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_details.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:09:27 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/08 10:11:48 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		parse_resolution(const char *line, t_info *info)
{
	int	i;
	int	x;
	int	y;

	i = 2;
	mlx_get_screen_size(info->mlx.mlx, &x, &y);
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
	{
		info->det.resx = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		info->det.resy = ft_atoi(&line[i]);
		if (info->det.resx > x)
			info->det.resx = x;
		if (info->det.resy > y)
			info->det.resy = y;
		return (0);
	}
	return (errormessage("invalid resolution", info));
}

int		parse_fc_color(const char *line, t_col *color, t_info *info)
{
	int i;

	i = 2;
	color->r = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	if (line[i] == ',')
	{
		i++;
		color->g = ft_atoi(&line[i]);
		while (line[i] != ',')
			i++;
		if (line[i] == ',')
		{
			i++;
			color->b = ft_atoi(&line[i]);
			color->col = rgb(color->r, color->g, color->b);
			return (0);
		}
	}
	return (errormessage("invalid floor/ceiling colors", info));
}

int		parse_texture(const char *line, t_info *info, int x)
{
	int i;

	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
	{
		if (x == 0)
			info->det.nopath = (ft_strdup(&line[i]));
		else if (x == 1)
			info->det.sopath = (ft_strdup(&line[i]));
		else if (x == 2)
			info->det.wepath = (ft_strdup(&line[i]));
		else if (x == 3)
			info->det.eapath = (ft_strdup(&line[i]));
		else if (x == 4)
			info->det.spath = (ft_strdup(&line[i]));
		return (0);
	}
	else
		return (errormessage("invalid texture path)", info));
}
