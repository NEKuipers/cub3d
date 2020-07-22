/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 14:21:44 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/22 10:20:57 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_line_tex(const char *line, t_info *info)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (parse_texture(line, info, 0));
	else if (line[0] == 'S' && line[1] == 'O')
		return (parse_texture(line, info, 1));
	else if (line[0] == 'W' && line[1] == 'E')
		return (parse_texture(line, info, 2));
	else if (line[0] == 'E' && line[1] == 'A')
		return (parse_texture(line, info, 3));
	else if (line[0] == 'S' && line[1] == ' ')
		return (parse_texture(line, info, 4));
	else
		return (-1);
}

int			parse_line(const char *line, t_info *info)
{
	if (info->grid.mapval == 1 && (line[0] == '1' ||
		line[0] == '0' || line[0] == ' ' || line[0] == '\t'))
		return (errormessage("empty lines detected in map.", info));
	if (info->grid.mapval == 1 && (ft_isalpha(line[0])))
		return (errormessage("wrong input order.", info));
	if (info->grid.map && !ft_strncmp(line, "", 2))
		info->grid.mapval = 1;
	if (line[0] == '\n' || ft_strncmp(line, "", 2) == 0)
		return (0);
	else if (line[0] == 'R' && line[1] == ' ')
		return (parse_resolution(line, info));
	else if (ft_strchr("NEWS", line[0]))
		return (parse_line_tex(line, info));
	else if (line[0] == 'F' && line[1] == ' ')
		return (parse_fc_color(line, &info->det.floor, info));
	else if (line[0] == 'C' && line[1] == ' ')
		return (parse_fc_color(line, &info->det.ceil, info));
	else if (ft_strchr("10 \t", line[0]))
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
	if (info->grid.map == 0)
		errormessage("No map found", info);
	info->grid.gmap = ft_split(info->grid.map, '\n');
	return (0);
}

int			main(int ac, char **av)
{
	t_info	info;

	ft_bzero(&info, (sizeof(t_info)));
	if (av[1])
		if (check_input_file(av[1], &info) != 1)
			return (0);
	if ((ac == 2) || (ac == 3 && ft_strncmp(av[2], "--save", 7) == 0))
	{
		if (ac == 3 && ft_strncmp(av[2], "--save", 7) == 0)
			info.scrshot = 1;
		if (read_input(av, &info) == -1)
			return (errormessage("Something's wrong with your input.", &info));
		mlx_start(&info);
	}
	else if (ac == 3 && ft_strncmp(av[2], "--save", 7) != 0)
		errormessage("Invalid arguments. Did you mean '--save'?", &info);
	else
		errormessage("Invalid input.", &info);
	return (0);
}
