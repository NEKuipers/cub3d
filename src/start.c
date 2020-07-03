/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 14:21:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/01 15:31:16 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <fcntl.h>

int			parse_line(const char *line, t_info *info)
{
	int	i;

	i = 0;
	if (line[i] == '\n' || ft_strncmp(line, "", 1) == 0)
		return (0);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		return (parse_resolution(line, info));
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (parse_texture(line, info, 0));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (parse_texture(line, info, 1));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (parse_texture(line, info, 2));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (parse_texture(line, info, 3));
	else if (line[i] == 'S' && line[i + 1] == ' ')
		return (parse_texture(line, info, 4));
	else if (line[i] == 'F' && line[i + 1] == ' ')
		return (parse_fc_color(line, &info->det.floor));
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (parse_fc_color(line, &info->det.ceil));
	else if (line[i] == '1' || line[i] == ' ')
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
	info->grid.gmap = ft_split(info->grid.map, '\n');
	free(info->grid.map);
	return (0);
}

int			main(int ac, char **av)
{
	t_info	info;

	ft_bzero(&info, (sizeof(t_info)));
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
