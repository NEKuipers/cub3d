/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_details.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:09:27 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/22 14:15:09 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			parse_resolution(char *line, t_info *info)
{
	int	i;

	i = 2;
	mlx_get_screen_size(info->mlx.mlx, &info->det.screenx, &info->det.screeny);
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
	{
		info->det.resx = ft_atoi(&line[i]);
		info->det.sshx = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		info->det.resy = ft_atoi(&line[i]);
		info->det.sshy = ft_atoi(&line[i]);
		if (info->det.resx > info->det.screenx || info->det.resx < 0)
			info->det.resx = info->det.screenx;
		if (info->det.resy > info->det.screeny || info->det.resy < 0)
			info->det.resy = info->det.screeny;
		if (info->det.resx != 0 && info->det.resy != 0)
			return (0);
	}
	return (errormessage("invalid resolution", info));
}

int			parse_fc_color(char *line, t_col *color, t_info *info)
{
	int i;

	i = 2;
	color->r = ft_atoi(&line[i]);
	while (line[i] && (ft_isdigit(line[i]) || line[i] == ' '))
		i++;
	if (line[i] == ',')
	{
		i++;
		color->g = ft_atoi(&line[i]);
		while (line[i] && (ft_isdigit(line[i]) || line[i] == ' '))
			i++;
		if (line[i] == ',')
		{
			i++;
			color->b = ft_atoi(&line[i]);
			if (color->r < 256 && color->r >= 0 && color->b < 256 &&
				color->b >= 0 && color->g < 256 && color->g >= 0)
			{
				color->col = rgb(color->r, color->g, color->b);
				return (0);
			}
		}
	}
	return (errormessage("invalid floor/ceiling colors", info));
}

static int	parse_texture_2(char *line, t_info *info, int x, int i)
{
	if (x == 0)
		if (info->det.nopath == NULL)
			info->det.nopath = (ft_strdup(&line[i]));
		else
			return (errormessage("duplicate north wall texture.", info));
	else if (x == 1)
		if (info->det.sopath == NULL)
			info->det.sopath = (ft_strdup(&line[i]));
		else
			return (errormessage("duplicate south wall texture.", info));
	else if (x == 2)
		if (info->det.wepath == NULL)
			info->det.wepath = (ft_strdup(&line[i]));
		else
			return (errormessage("duplicate west wall texture.", info));
	else if (x == 3)
	{
		if (info->det.eapath == NULL)
			info->det.eapath = (ft_strdup(&line[i]));
		else
			return (errormessage("duplicate east wall texture.", info));
	}
	return (0);
}

int			parse_texture(char *line, t_info *info, int x)
{
	int i;

	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
	{
		if (x == 0 || x == 1 || x == 2 || x == 3)
			parse_texture_2(line, info, x, i);
		else if (x == 4)
		{
			if (info->det.spath == NULL)
				info->det.spath = (ft_strdup(&line[i]));
			else
				return (errormessage("duplicate sprite texture.", info));
		}
		return (0);
	}
	else
		return (errormessage("invalid texture path.", info));
}
