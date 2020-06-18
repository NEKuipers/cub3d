/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 14:21:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/18 16:03:45 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <fcntl.h>

int			parse_line(const char *line, t_info *info)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (0);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		return (parse_resolution(line, info));
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (parse_north_texture(line, info));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (parse_south_texture(line, info));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (parse_west_texture(line, info));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (parse_east_texture(line, info));
	else if (line[i] == 'S' && line[i + 1] == ' ')
		return (parse_sprite_texture(line, info));
	else if (line[i] == 'F' && line[i + 1] == ' ')
		return (parse_floor_color(line, info));
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (parse_ceiling_color(line, info));
	else if (line[i] == '1')
		return (parse_grid(line, info));
	else
		return (-1);
}

int			read_input(char **av, t_info *info)
{
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (parse_line(line, info) == -1)
			return (-1);
		if (line)
			free(line);
	}
	if (parse_line(line, info) == -1)
		return (-1);
	if (line)
		free(line);
	close(fd);
	clean_grid(info);
	info->grid.gmap = ft_split(info->grid.map, 'Z');
	return (0);
}

int			main(int ac, char **av)
{
	t_info	info;

	ft_bzero(&info, (sizeof(t_info)));
	info.grid.map = (char*)malloc(sizeof(char) * 1000);
	if (!info.grid.map)
		return (-1);
	if ((ac == 2) || (ac == 3 && ft_strncmp(av[2], "--save", 7) == 0))
	{
		if (read_input(av, &info) == -1)
			return (-1);
		mlx_start(&info, av[2]);
	}
	else if (ac == 3 && ft_strncmp(av[2], "--save", 7) != 0)
		errormessage("Invalid arguments. Did you mean '--save'?");
	else
		errormessage("invalid input");
	return (0);
}
