/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_grid.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:40:59 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/03 13:38:23 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	int i;

	if (info->grid.map == 0)
		info->grid.map = ft_strdup(line);
	else
		info->grid.map = ft_strjoin_cub3d(info->grid.map, line);
	i = 0;
	info->spi.amount = 0;
	while (info->grid.map[i])
	{
		if (info->grid.map[i] == '2')
			info->spi.amount++;
		i++;
	}
	return (0);
}
