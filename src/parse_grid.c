/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_grid.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:40:59 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/08 13:18:24 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_grid(char **grid)
{
	int i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static void	floodfill(t_info *info, char **grid, int x, int y)
{
	if (grid[y][x] == '1' || grid[y][x] == '3' || grid[y][x] == '4')
		return ;
	if (!(y == (int)info->rays.posx && x == (int)info->rays.posy))
		if ((x == 0 || y == 0 || x == info->grid.max_x
			|| y == info->grid.max_y) || !(ft_strchr("012", grid[y][x])))
		{
			free_grid(grid);
			errormessage("Invalid map!", info);
		}
	if (grid[y][x] == '0')
		grid[y][x] = '3';
	if (grid[y][x] == '2')
		grid[y][x] = '4';
	floodfill(info, grid, x + 1, y);
	floodfill(info, grid, x, y + 1);
	floodfill(info, grid, x - 1, y);
	floodfill(info, grid, x, y - 1);
	floodfill(info, grid, x + 1, y + 1);
	floodfill(info, grid, x - 1, y + 1);
	floodfill(info, grid, x + 1, y - 1);
	floodfill(info, grid, x - 1, y - 1);
}

int			check_grid(t_info *info)
{
	char	**temp;
	int		x;
	int		y;
	int		i;

	i = 0;
	temp = ft_split(info->grid.map, '\n');
	while (temp[info->grid.max_y + 1] != NULL)
		info->grid.max_y++;
	while (temp[i + 1])
	{
		while (temp[i][info->grid.max_x + 1] != '\0')
			info->grid.max_x++;
		i++;
	}
	y = info->rays.posx;
	x = info->rays.posy;
	floodfill(info, temp, x, y);
	free_grid(temp);
	return (1);
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
