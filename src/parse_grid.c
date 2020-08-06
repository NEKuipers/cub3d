/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_grid.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:40:59 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/08/06 13:52:46 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		free_grid(char **grid)
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

static void	check_start_pos(t_info *info, char **grid, int x, int y)
{
	if (x == 0 || y == 0 || x == info->grid.max_x || y == info->grid.max_y)
	{
		free_grid(grid);
		errormessage("Invalid map!", info);
	}
	else
		grid[y][x] = '0';
}

static void	floodfill(t_info *info, char **grid, int x, int y)
{
	if (grid[y][x] == '1' || grid[y][x] == '3' || grid[y][x] == '4')
		return ;
	if (y == info->rays.posx - 0.5 && x == info->rays.posy - 0.5)
		check_start_pos(info, grid, x, y);
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
	while (temp[info->grid.max_y] != NULL)
		info->grid.max_y++;
	while (temp[i])
	{
		if (info->grid.max_x < (int)ft_strlen(temp[i]))
			info->grid.max_x = ft_strlen(temp[i]);
		i++;
	}
	info->grid.max_x--;
	info->grid.max_y--;
	y = info->rays.posx;
	x = info->rays.posy;
	floodfill(info, temp, x, y);
	free_grid(temp);
	return (1);
}

int			parse_grid(char *line, t_info *info)
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
