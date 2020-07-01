/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_grid.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:40:59 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/01 14:09:47 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

int			count_spaces(t_info *info)
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

char		*ft_strjoin_cub3d(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\n';
	i++;
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

int			parse_grid(const char *line, t_info *info)
{
	if (info->grid.map == 0)
		info->grid.map = ft_strdup(line);
	else
		info->grid.map = ft_strjoin_cub3d(info->grid.map, line);
	return (0);
}
