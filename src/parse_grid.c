/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_grid.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:40:59 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/24 15:03:37 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

static int	count_spaces(t_info *info)
{
	int		i;
	int		count;
	char	*temp;

	i = 0;
	count = 0;
	temp = info->grid.map;
	while (temp[i])
	{
		if (temp[i] == ' ')
			count++;
		i++;
	}
	return (count);
}

void		clean_grid(t_info *info)
{
	char	*temp;
	char	*temp2;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	temp = info->grid.map;
	len = ft_strlen(info->grid.map);
	temp2 = (char *)malloc(sizeof(char) * (len - count_spaces(info) + 1));
	if (!temp2)
		return ;
	temp2[(len - count_spaces(info))] = '\0';
	while (temp[i])
	{
		if (temp[i] != ' ')
		{
			temp2[j] = temp[i];
			j++;
		}
		i++;
	}
	free(temp);
	info->grid.map = temp2;
}

int			get_grid_len(const char *line)
{
	int len;
	int	i;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			len++;
		i++;
	}
	return (len);
}

int			parse_grid(const char *line, t_info *info)
{
	int		x;
	int		y;
	int		z;

	z = info->grid.height;
	if (info->grid.widthws == 0)
		info->grid.widthws = ft_strlen(line);
	if (info->grid.width == 0)
		info->grid.width = get_grid_len(line);
	x = 0;
	y = info->grid.height;
	while (line[x])
	{
		if (line[x] != '1' && line[x] != '2' && line[x] != '0' && line[x] != 'N'
			&& line[x] != 'S' && line[x] != 'W' && line[x] != 'E' &&
			line[x] != ' ' && line[x] != '\n' && line[x] != '\0')
			return (errormessage("Invalid map"));
		info->grid.map[(y * info->grid.widthws + x + z)] = line[x];
		x++;
	}
	info->grid.map[(y * info->grid.widthws + x + z)] = 'Z';
	info->grid.height++;
	return (0);
}
