/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 13:13:16 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/15 10:32:08 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_struct(t_info *info)
{
	int i;

	i = 0;
	if (info->grid.map)
		free(info->grid.map);
	if (info->grid.gmap)
	{
		while (info->grid.gmap[i])
		{
			free(info->grid.gmap[i]);
			i++;
		}
		free(info->grid.gmap);
	}
	if (info->det.nopath)
		free(info->det.nopath);
	if (info->det.sopath)
		free(info->det.sopath);
	if (info->det.eapath)
		free(info->det.eapath);
	if (info->det.wepath)
		free(info->det.wepath);
	if (info->det.spath)
		free(info->det.spath);
	if (info->sprites)
		free(info->sprites);
}

int		rgb(int r, int g, int b)
{
	int	fc_color;

	fc_color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	if (fc_color < 0)
		fc_color *= -1;
	return (fc_color);
}

int		errormessage(char *errormsg, t_info *info)
{
	free_struct(info);
	write(1, "Error: ", 7);
	ft_putstr_fd(errormsg, 1);
	write(1, "\n", 1);
	exit(1);
	return (-1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		check_input_file(char *filename, t_info *info)
{
	int i;

	i = 0;
	while (filename[i] != '.' && filename[i])
		i++;
	if (filename[i] != '.')
		return (errormessage("Invalid file. Please enter .cub file", info));
	if (ft_strncmp(&filename[i], ".cub", 4) != 0)
		return (errormessage("Invalid filetype. Please enter .cub file", info));
	while (filename[i] != 'b')
		i++;
	if (filename[i + 1] != '\0')
		return (errormessage("Invalid filetype. Please enter .cub file", info));
	return (1);
}
