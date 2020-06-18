/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 12:47:10 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/18 16:03:59 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		parse_north_texture(const char *line, t_info *info)
{
	int	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
	{
		info->det.nopath = (ft_strdup(&line[i]));
		return (0);
	}
	else
		return (errormessage("invalid north texture path"));
}

int		parse_south_texture(const char *line, t_info *info)
{
	int	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
	{
		info->det.sopath = (ft_strdup(&line[i]));
		return (0);
	}
	else
		return (errormessage("invalid south texture path"));
}

int		parse_west_texture(const char *line, t_info *info)
{
	int	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
	{
		info->det.wepath = (ft_strdup(&line[i]));
		return (0);
	}
	else
		return (errormessage("invalid west texture path"));
}

int		parse_east_texture(const char *line, t_info *info)
{
	int	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
	{
		info->det.eapath = (ft_strdup(&line[i]));
		return (0);
	}
	else
		return (errormessage("invalid east texture path"));
}

int		parse_sprite_texture(const char *line, t_info *info)
{
	int	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
	{
		info->det.spath = (ft_strdup(&line[i]));
		return (0);
	}
	else
		return (errormessage("invalid sprite texture path)"));
}
